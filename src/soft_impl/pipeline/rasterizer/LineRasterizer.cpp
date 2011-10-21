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

#include <cmath>

#include "PointRasterizer.hpp"

#include "pipeline/interpolator/Interpolator.hpp"
#include "pipeline/interpolator/CoordInfo.hpp"
#include "shader/FragmentAttributeBuffer.hpp"


using std::max;
using std::abs;

namespace my_gl {
	void LineRasterizer::groupAction
	       (const ConstAttributeGroupRef& attributeGroup1,
		const ConstAttributeGroupRef& attributeGroup2,
		const WindowCoordinates& winCoord,
		float percent,
		FragmentAttributeBuffer& fragmentAttributeBuffer)
	       {
		    auto attributeGroupRef=
			 fragmentAttributeBuffer(winCoord);

		    Interpolator::interpolateAttributeGroup
			 (attributeGroup1, attributeGroup2, 
			  percent, attributeGroupRef
			  );

		    auto& fragCoord=getVertex(attributeGroupRef);

		    fragCoord/=fragCoord.w();

		    viewportCorrect(fragCoord,winCoord);
	       }

	/** 
	 * @brief rasterize horizontal or vertical line
	 */
	static void rasterizeSpecial(
		  ConstAttributeGroupRef& attributeGroup1,
		  ConstAttributeGroupRef& attributeGroup2,
		  const CoordInfo& coord1,const CoordInfo& coord2,
		  int majorDelta,int majorIndex,int anotherIndex,
		  FragmentAttributeBuffer& fragmentAttributeBuffer,
		  const Interpolator& interpolator)
	{
			
		    const int fixedValue=coord1.windowCoord[anotherIndex];

		    //draw special line
			 
		    WindowCoordinates thisCoord;
		    thisCoord[anotherIndex]=fixedValue;

		    for(int majorValue=coord1.windowCoord[majorIndex];
			      majorValue<coord2.windowCoord[majorIndex];
			      ++majorValue)
		    {
			 thisCoord[majorIndex]=majorValue;

			 float percent=interpolator.getPercent
			      (coord1,coord2,
			       thisCoord,majorDelta,
			       Interpolator::MajorDim(majorIndex));

			 LineRasterizer::groupAction(attributeGroup1, attributeGroup2, 
				   thisCoord, percent, fragmentAttributeBuffer);
		    }
	}

     void LineRasterizer::elementRasterize
	  (ConstAttributeGroupRef* attributeGroupRefs,
	   FragmentAttributeBuffer& fragmentAttributeBuffer,
	   const Interpolator& interpolator)
	  {

	       auto 
		    attributeGroup1=attributeGroupRefs[0],
	       attributeGroup2=attributeGroupRefs[1];


	       CoordInfo coord1(getVertex(attributeGroup1)),
			 coord2(getVertex(attributeGroup2));

	       coord1.windowCoord=toWindowCoordinates
		    (coord1.normalizedCoord);
	       coord2.windowCoord=toWindowCoordinates
		    (coord2.normalizedCoord);


	       //begin point need no interpolate;
	       PointRasterizer::rasterizePoint
			 (attributeGroup1,fragmentAttributeBuffer,coord1.windowCoord);
	
	       int deltaXY[]={
		    coord2.windowCoord.first-coord1.windowCoord.first,
		    coord2.windowCoord.second-coord1.windowCoord.second};


	       if (max(abs(deltaXY[0]),abs(deltaXY[1]))<=1)
	       {
			    
		    //too small
		    //just point, or a segment length less_equal than 1 
		    //gl spec said that 
		    //line segment use half-open draw 
		    //approach,draw beginPoint only
		    //
	           return;
	       }
	       

	       int majorIndex=deltaXY[0]>deltaXY[1]?0:1;
	       int anotherIndex=1-majorIndex;

	       if (deltaXY[0]==0 || deltaXY[1]==0)
	       {
		    //horizontal or vertical
		    rasterizeSpecial
			 (attributeGroup1,attributeGroup2,
			      coord1,coord2,
			      deltaXY[majorIndex],majorIndex,anotherIndex,
			      fragmentAttributeBuffer,interpolator);
		    return;
	       }


	       rasterize
		    (attributeGroup1,attributeGroup2,
		     coord1,coord2,
		     deltaXY[majorIndex],majorIndex,
		     deltaXY[anotherIndex],anotherIndex,
		     fragmentAttributeBuffer,interpolator);
	  }

     LineRasterizer::~LineRasterizer (){}
} /* my_gl */
