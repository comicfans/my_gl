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

#include "pipeline/interpolator/Interpolator.hpp"
#include "shader/FragmentAttributeBuffer.hpp"

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


     void LineRasterizer::elementRasterize
	  (ConstAttributeGroupRef* attributeGroupRefs,
	   FragmentAttributeBuffer& fragmentAttributeBuffer,
	   const Interpolator& interpolator)
	  {

	       auto 
		    attributeGroup1=attributeGroupRefs[0],
	       attributeGroup2=attributeGroupRefs[1];

	       auto 
		    &point1=getVertex(attributeGroup1),
	       &point2=getVertex(attributeGroup2);

	       auto normalizedCoord1=point1/point1.w(),
		    normalizedCoord2=point2/point2.w();
		    
	       auto winCoord1=toWindowCoordinates
		         (normalizedCoord1),
		    winCoord2=toWindowCoordinates
			 (normalizedCoord2);

	       if (point1==point2)
	       {
		    //just point,gl spec said that 
		    //line segment use half-open draw 
		    //approach,draw beginPoint only
		    auto toWrite=
		    fragmentAttributeBuffer(winCoord1);

		    toWrite=attributeGroup1;
		    viewportCorrect(
			      toWrite[VertexAttributeBuffer::OutIndex::POSITION],
			      winCoord1);
		    return;
	       }

	       bool special=false;
	       Interpolator::MajorDim majorDim;

	       if (winCoord1.first==winCoord2.first)
	       {
		    //horizontal line
		    special=true;
		    majorDim=Interpolator::MajorDim::Y;
	       }
	       else if (winCoord1.second==winCoord2.second)
	       {
		    //vertical
		    special=true;
		    majorDim=Interpolator::MajorDim::X;
	       }

	       if (special)
	       {
		    int majorIndex=int(majorDim),
			anotherIndex=1-majorIndex;

		    const int majorDelta=
			 point2[majorIndex]-point1[majorIndex];
		    const int fixedValue=point1[anotherIndex];

		    //draw special line
			 
		    WindowCoordinates winCoord;
		    winCoord[anotherIndex]=fixedValue;

		    for(int majorValue=winCoord1[majorIndex];
			      majorValue<winCoord2[majorIndex];
			      ++majorValue)
		    {
			 winCoord[majorIndex]=majorValue;

			 float percent=interpolator.getPercent
			      (point1,point2,
			       normalizedCoord1,normalizedCoord2,
			       winCoord1,majorDelta,winCoord,majorDim);

			 groupAction(attributeGroup1, attributeGroup2, 
				   winCoord, percent, fragmentAttributeBuffer);
		    }

		    return;
	       }
	       
		    

	       rasterize
		    (attributeGroup1,attributeGroup2,
		     winCoord1,winCoord2,
		     fragmentAttributeBuffer,interpolator);
	  }

     LineRasterizer::~LineRasterizer (){}
} /* my_gl */
