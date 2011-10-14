/*
 * =====================================================================================
 *
 *       Filename:  LineClipper.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-11 11:28:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LineClipper.hpp"

#include <limits>
#include <algorithm>

#include "pipeline/ClippedPrimitiveGroup.hpp"
#include "pipeline/Interpolator.hpp"
#include "PointClipper.hpp"

using std::max;
using std::min;


namespace my_gl {


     LineClipper::~LineClipper(){}

     void LineClipper::interpolateAttributeGroup(
	       const ConstAttributeGroupRef& attributeGroupSource, 
	       const ConstAttributeGroupRef& attributeGroupDestination,
	       float percent,AttributeGroupRef& attributeGroupResult
	       )
     {
	  for (int i=0; i<attributeGroupSource.size(); ++i)
	  {
		    
	       Interpolator::calculate(attributeGroupSource[i], 
			 attributeGroupDestination[i], percent, 
			 attributeGroupResult[i]);
	  }
     }

     ClipPercent LineClipper::clipInHomogenousCoordinates
	  (const Vec4& point1,const Vec4& point2)
	  {

	  }

     void LineClipper::elementClip
	  (const ConstAttributeGroupRef* originalAttributeGroups,
	   const size_t *vertexIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {
	       auto &point1=getVertex(originalAttributeGroups[0]);
	       auto &point2=getVertex(originalAttributeGroups[1]);

	       bool point1Infinit=
		    PointClipper::isInfinit(point1),
		    point2Infinit=
			 PointClipper::isInfinit(point2);

	       if(point1Infinit && point2Infinit)
	       {
		    //if two point is infinit,
		    //two points lies on z plane ,and far>=near>0
		    //so these two points is out of clip volume
		    return;
	       }

	       ClipPercent clipResult;

	       if(point1Infinit || point2Infinit)
	       {
		    //use clip in homogeonous coordinates
	       }
	       else
	       {
		    clipResult=
			 clipLiangBarsky(point1, point2);
	       }


	       if(outOfClipVolume(clipResult))
	       {
		    //discard this line
		    return;
	       }

	       if(clipResult.first==0)
	       {
		    clippedPrimitiveGroup.insertOriginalIndex(vertexIndex[0]);
	       }
	       else
	       {
		    auto newData=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();

		    interpolateAttributeGroup(
			      originalAttributeGroups[0],
			      originalAttributeGroups[1],
			      clipResult.first,newData);
	       }


	       if (clipResult.second==1.0)
	       {
		    clippedPrimitiveGroup.insertOriginalIndex(vertexIndex[1]);
	       }
	       else
	       {

		    auto newData=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();

		    interpolateAttributeGroup(
			      originalAttributeGroups[0],
			      originalAttributeGroups[1],
			      clipResult.second,newData);
	       }

	  }

     enum class ClipPlane{X,Y,Z};

     bool LineClipper::outOfClipVolume
	  (const ClipPercent& clipResult)
	  {
	       return clipResult.first>clipResult.second;
	  }



     static ClipPercent parallelPlaneClip
	  (const Vec4& point1,const Vec4& point2,
	   ClipPlane crossPlane)
	  {
	       const int valueIndex=int(crossPlane);

	       const float value=point1[valueIndex];

	       ClipPercent result;

	       // deltaX deltaY or deltaZ
	       const float deltaPosition
		    =point1[valueIndex];

	       const float 
		    qMinSide=value-(-1.0),
		    qMaxSide=1.0-value;

	       if (deltaPosition==0)
	       {
		    //parallel to clip plane
		    if (qMinSide>=0 && qMaxSide>=0)
		    {
			 //just between min and max clip plane
			 return {0,1};
		    }
		    else
		    {
			 //out of this plane 
			 //(less than min or more than max)
			 return {1,0};
		    }
	       }
	       else{
		    return 
		    {qMinSide/deltaPosition,
			 qMaxSide/deltaPosition};
	       }
    }


     ClipPercent LineClipper::clipLiangBarsky
	  (const Vec4 &point1, 
	       const Vec4 &point2)
	  {

	       ClipPercent currentResult={0,1};

	       for(int i=0;i<3;++i)
	       {

		    ClipPercent thisClipResult=parallelPlaneClip
			 (point1, point2, ClipPlane(i));

		    if(thisClipResult.first>thisClipResult.second)
		    {
			 return {1,0};
		    }

		    //apply other plane clip result
		    currentResult.first=max(currentResult.first,
			      max(0.0f,thisClipResult.first));

		    currentResult.second=min(currentResult.second,
			      min(1.0f,thisClipResult.second));
	       }

	       return currentResult;

	  }

} /* my_gl */
