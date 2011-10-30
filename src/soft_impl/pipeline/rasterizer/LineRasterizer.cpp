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
	       (const ConstAttributeGroupRefList& attributeGroupRefs,
		const CoordInfo& coord1,const CoordInfo& coord2,
		const LineInfo& lineInfo,
		const WindowCoordinates& winCoord,
		StepCallback /* ignored */)
	       {
		    auto attributeGroupRef=_fragmentAttributeBuffer
			 .writeNewFragment(winCoord);

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
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
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


		    for(int majorValue=coord1[majorIndex]+1;
			      majorValue<coord2[majorIndex];
			      ++majorValue)
		    {
			 thisCoord[majorIndex]=majorValue;
			 stepCallback(thisCoord);
		    }
	}


	template<bool hasCallback>
	     void LineRasterizer::rasterizeImpl
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
	      StepCallback stepCallback)
	     {
	       auto 
		    homogenousCoord1=getVertex(attributeGroupRefs[0]),
		  homogenousCoord2=getVertex(attributeGroupRefs[1]);


	       CoordInfo rawCoord1(homogenousCoord1),
			 rawCoord2(homogenousCoord2);

	       rawCoord1.windowCoord=toWindowCoordinates
		    (rawCoord1.normalizedCoord);

	       rawCoord2.windowCoord=toWindowCoordinates
		    (rawCoord2.normalizedCoord);


	       //begin point need no interpolate;
	       PointRasterizer::rasterizePoint
			 (attributeGroupRefs[0],
			  _fragmentAttributeBuffer,
			  rawCoord1.windowCoord);
	
	       LineInfo rawLineInfo(rawCoord1.windowCoord,rawCoord2.windowCoord),
			revert(rawLineInfo.revert());

	       auto pCoord1=&rawCoord1,
			 pCoord2=&rawCoord2;
	       auto pLineInfo=&rawLineInfo;

	       //adjust point order,make lineInfo.getMajorDelta always >0 
	       //this makes following rasterize simpler

	       if (rawLineInfo.getMajorDelta()<0)
	       {
		    pLineInfo=&revert;
		    pCoord1=&rawCoord2;
		    pCoord2=&rawCoord1;
	       }

	       auto wrappedCallback=bind(
			 &LineRasterizer::groupAction<hasCallback>,
			 this,attributeGroupRefs,
			 *pCoord1,*pCoord2,*pLineInfo,
			 _1,stepCallback);

	       if (rawLineInfo.isOnlyPoint())
	       {
		    //too small
		    //just point, or a segment length less_equal than 1 
		    //gl spec said that 
		    //line segment use half-open draw 
		    //approach,draw beginPoint only
		    //
	           return;
	       }

	       if (rawLineInfo.parallelToAxis())
	       {
		    //horizontal or vertical
		    rasterizeSpecialImpl
			 (pCoord1->windowCoord,pCoord2->windowCoord,
			  *pLineInfo,wrappedCallback);
		    return;
	       }

	       rasterize
		    (pCoord1->windowCoord,pCoord2->windowCoord,
		     *pLineInfo,
		     wrappedCallback);
	
	     }
		
	void LineRasterizer::rasterizeSpecial
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
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
	  (const ConstAttributeGroupRefList& attributeGroupRefs)
	  {
	       rasterizeImpl<false>(attributeGroupRefs);
	  }

     void LineRasterizer::rasterizeWithCallback
	     (const ConstAttributeGroupRefList& attributeGroupRefs,
		    StepCallback stepCallback)
     {
	  rasterizeImpl<true>(attributeGroupRefs,stepCallback);
     }




     LineRasterizer::~LineRasterizer (){}

} /* my_gl */
