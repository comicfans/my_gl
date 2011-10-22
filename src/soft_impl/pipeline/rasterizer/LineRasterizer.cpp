/*
 * =====================================================================================
 *
 *       Filename:  LineRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-20 21:19:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LineRasterizer.hpp"

#include <functional>

#include "PointRasterizer.hpp"

#include "pipeline/interpolator/Interpolator.hpp"
#include "pipeline/interpolator/CoordInfo.hpp"
#include "shader/FragmentAttributeBuffer.hpp"
#include "LineInfo.hpp"
#include "WindowCoordinates.hpp"




namespace my_gl {

     using std::bind;
     using std::placeholders::_1;

     LineRasterizer::LineRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer)
	       :Rasterizer
		(viewportParameter,interpolator,fragmentAttributeBuffer){}




	template<>
	void LineRasterizer::groupAction<false>
	       (ConstAttributeGroupRef* attributeGroupRefs,
		const CoordInfo& coord1,const CoordInfo& coord2,
		const LineInfo& lineInfo,
		const WindowCoordinates& winCoord,
		StepCallback /* ignored */)
	       {
		    auto attributeGroupRef=
			 _fragmentAttributeBuffer(winCoord);

		    float percent=_interpolator.getPercent
			 (coord1, coord2,  lineInfo,winCoord);

		    Interpolator::interpolateAttributeGroup
			 (attributeGroupRefs[0], attributeGroupRefs[1], 
			  percent, attributeGroupRef);

		    auto& fragCoord=getVertex(attributeGroupRef);

		    fragCoord/=fragCoord.w();

		    viewportCorrect(fragCoord,winCoord);
	       }

	template<>
	     void LineRasterizer::groupAction<true>
	       (ConstAttributeGroupRef* attributeGroupRefs,
		const CoordInfo& coord1,const CoordInfo& coord2,
		const LineInfo& lineInfo,
		const WindowCoordinates& winCoord,
		StepCallback stepCallback)
	     {
		  groupAction<false>(attributeGroupRefs,
			    coord1,coord2,
			    lineInfo,winCoord);
		  stepCallback(winCoord);
	     }

	/** 
	 * @brief rasterize horizontal or vertical line
	 */
	static void rasterizeSpecialImpl(
		  const WindowCoordinates& coord1,
		  const WindowCoordinates& coord2,
		  const LineInfo& lineInfo, 
		  LineRasterizer::StepCallback stepCallback)
	
	{
		    //draw special line
			 
		    WindowCoordinates thisCoord;

		    int majorIndex=int(lineInfo.majorDim),
			nonMajorIndex=int(lineInfo.nonMajorDim);

		    thisCoord[nonMajorIndex]=coord1[nonMajorIndex];


		    for(int majorValue=coord1[majorIndex];
			      majorValue<coord2[majorIndex];
			      ++majorValue)
		    {
			 thisCoord[majorIndex]=majorValue;
			 stepCallback(thisCoord);
		    }
	}


	template<bool hasCallback>
	     void LineRasterizer::rasterizeImpl
	     (ConstAttributeGroupRef* attributeGroupRefs,
	      StepCallback stepCallback)
	     {
	       auto 
		    homogenousCoord1=getVertex(attributeGroupRefs[0]),
		  homogenousCoord2=getVertex(attributeGroupRefs[1]);


	       CoordInfo coord1(homogenousCoord1),
			 coord2(homogenousCoord2);

	       coord1.windowCoord=toWindowCoordinates
		    (coord1.normalizedCoord);

	       coord2.windowCoord=toWindowCoordinates
		    (coord2.normalizedCoord);


	       //begin point need no interpolate;
	       PointRasterizer::rasterizePoint
			 (attributeGroupRefs[0],
			  _fragmentAttributeBuffer,
			  coord1.windowCoord);
	
	       LineInfo lineInfo(coord1.windowCoord,coord2.windowCoord);

	       auto wrappedCallback=bind(
			 &LineRasterizer::groupAction<hasCallback>,this,
			 attributeGroupRefs,coord1,coord2,lineInfo,_1,stepCallback);

	       if (lineInfo.isOnlyPoint())
	       {
		    //too small
		    //just point, or a segment length less_equal than 1 
		    //gl spec said that 
		    //line segment use half-open draw 
		    //approach,draw beginPoint only
		    //
	           return;
	       }

	       if (lineInfo.parallelToAxis())
	       {
		    //horizontal or vertical
		    rasterizeSpecialImpl
			 (coord1.windowCoord,coord2.windowCoord,
			  lineInfo,wrappedCallback);
		    return;
	       }

	       rasterize
		    (coord1.windowCoord,coord2.windowCoord,
		     lineInfo,
		     wrappedCallback);
	
	     }
		
	void LineRasterizer::rasterizeSpecial
	     (ConstAttributeGroupRef* attributeGroupRefs,
	      const WindowCoordinates& winCoord1,
	      const WindowCoordinates& winCoord2,
	      const LineInfo& lineInfo)
	{

	     auto 
		    homogenousCoord1=getVertex(attributeGroupRefs[0]),
		  homogenousCoord2=getVertex(attributeGroupRefs[1]);


	       CoordInfo coordInfo1(homogenousCoord1),
			 coordInfo2(homogenousCoord2);

	       coordInfo1.windowCoord=winCoord1;
	       coordInfo2.windowCoord=winCoord2;

	     StepCallback stepCallback=bind(
		       &LineRasterizer::groupAction<false>,this,
		       attributeGroupRefs,
		       coordInfo1,coordInfo2,lineInfo,
		       _1,StepCallback());

	     rasterizeSpecialImpl(winCoord1,winCoord2,lineInfo,stepCallback);
	}

	
     void LineRasterizer::elementRasterize
	  (ConstAttributeGroupRef* attributeGroupRefs)
	  {
	       rasterizeImpl<false>(attributeGroupRefs);
	  }

     void LineRasterizer::rasterizeWithCallback(
		    ConstAttributeGroupRef* attributeGroupRefs,
		    StepCallback stepCallback)
     {
	  rasterizeImpl<true>(attributeGroupRefs,stepCallback);
     }




     LineRasterizer::~LineRasterizer (){}

} /* my_gl */
