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

using std::max;
using std::min;


namespace my_gl {

     LineClipper::~LineClipper(){}

     void LineClipper::interpolateAttributeGroup(
	       size_t attributeNumber, 
	       const Vec4 *attributeGroupsSource, 
	       const Vec4 *attributeGroupsDestination, 
	       Vec4 *attributeGroupsResult, 
	       float percent)
     {
	  for (int i=0; i<attributeNumber; ++i)
	  {
		    
	       Interpolator::calculate(attributeGroupsSource[i], 
			 attributeGroupsDestination[i], percent, 
			 attributeGroupsResult[i]);
	  }
     }

     void LineClipper::elementClip
	  (size_t attributeNumber,
	   const Vec4 ** attributeGroups,
	   const size_t *vertexIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {
	       auto &point1=getVertex(attributeGroups, 0);
	       auto &point2=getVertex(attributeGroups, 1);

	       if(isInfinit(point1) || isInfinit(point2))
	       {
		    //use clip in homogeonous coordinates
	       }
	       //TODO not complete

	       const ClipPercent& clipResult=
		    clipLiangBarsky(point1, point2);

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
		    Vec4 *newData=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();

		    interpolateAttributeGroup(attributeNumber,
			      attributeGroups[0],attributeGroups[1],
			      newData,clipResult.first);
	       }


	       if (clipResult.second==1.0)
	       {
		    clippedPrimitiveGroup.insertOriginalIndex(vertexIndex[1]);
	       }
	       else
	       {

		    Vec4 *newData=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();

		    interpolateAttributeGroup(attributeNumber,
			      attributeGroups[0],attributeGroups[1],
			      newData,clipResult.second);
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
