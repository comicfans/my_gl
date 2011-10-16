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

     static const ClipPercent OUT_CLIP_PERCENT={1,0};

     LineClipper::~LineClipper(){}

     template<>
     void LineClipper::interpolateAttributeGroup<false>(
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

     template<>
	  void LineClipper::interpolateAttributeGroup<true>
	       (const ConstAttributeGroupRef& attributeGroupSource, 
	       const ConstAttributeGroupRef& attributeGroupDestination,
	       float percent,AttributeGroupRef& attributeGroupResult)
	  {
	       interpolateAttributeGroup<false>
		    (attributeGroupSource,
		     attributeGroupDestination,
		     percent,attributeGroupResult);

	       perspectiveDivision(getVertex
			 (attributeGroupResult));
	  }

     enum class ClipPlane{X,Y,Z};

     PackedResult LineClipper::commonClip(
	       Vec4 point1,Vec4 point2)
     {

	       bool point1Infinit=isInfinit(point1),
		    point2Infinit=isInfinit(point2);

	       if(point1Infinit && point2Infinit)
	       {
		    return {true,OUT_CLIP_PERCENT};
	       }

	       ClipPercent clipResult;

	       if(point1Infinit || point2Infinit)
	       {
		    //use clip in homogeonous coordinates
		    clipResult=
			 clipInHomogenousCoordinates
			 (point1,point2);
		    if (outOfClipVolume(clipResult))
		    {
			 return {true,OUT_CLIP_PERCENT};
		    }

	       }

	       //perspectiveDivision first
	       perspectiveDivision(point1);
	       perspectiveDivision(point2);

	       clipResult=
			 clipLiangBarsky(point1, point2);

	       return {false,clipResult};

     }

     static ClipPercent parallelPlaneClipInHomogenousCoordinates
	  (const Vec4& point1,const Vec4& point2,ClipPlane clipPlane)
	  {
	       //x for example
	       //(x-x1)/(x2-x1)=(w-w1)/(w2-w1)
	       //make deltaX = x2-x1
	       //     deltaW = w2-w1
	       // clip plane 
	       // x+w=0 ->x=-1 (normalized) minClipPlane
	       // x-w=0 ->x=1  (normalized) maxClipPlane
	       //   |deltaW, -deltaX |     |x| |deltaW*x1-deltaX*w1|
	       //   |		     |	x  | |=| 		   |
	       //   |  1   ,  +/- 1  |     |w| |      0            |
	       
	       int dIndex=int(clipPlane);

	       float w1=point1.w(),
		     d1=point1[dIndex];

	       float deltaW= point2.w()-w1,
		    deltaD= point2[dIndex]-d1;

	       float rowColumnValueMin=deltaW+deltaD,
		     rowColumnValueMax=-deltaW+deltaD;

	       float dMin=(deltaW*d1-deltaD*w1)/rowColumnValueMin,
		     dMax=(-deltaW*d1-deltaD*w1)/rowColumnValueMax;

	       float wMin=-dMin,
		     wMax=dMax;

	       return {(wMin-w1)/deltaW,(wMax-w1)/deltaW};
	
	  }

     ClipPercent LineClipper::clipInHomogenousCoordinates
	  (const Vec4& point1,const Vec4& point2)
	  {
	       assert(point1.w()!=point2.w());
	       //should not be the same(0)

	       ClipPercent result={0,1};

	       for (int i=0; i<3; ++i)
	       {
		    ClipPercent thisClipResult=
			 parallelPlaneClipInHomogenousCoordinates(
			      point1,point2,ClipPlane(i));
		    result.first=max(result.first,
			      thisClipResult.first);
		    result.second=min(result.second,
			      thisClipResult.second);
	       }

	       return result;  
	  }

     void LineClipper::elementClip
	  (const ConstAttributeGroupRef* originalAttributeGroups,
	   const size_t *vertexIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {
	       auto &point1=getVertex(originalAttributeGroups[0]);
	       auto &point2=getVertex(originalAttributeGroups[1]);

	       PackedResult packedResult=commonClip(point1,point2);

	       bool hasInfinit=packedResult.first;
	       ClipPercent clippResult=packedResult.second;

	       if(hasInfinit)
	       {
		    auto newData1=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();
			      
		    interpolateAttributeGroup<true>(
			      originalAttributeGroups[0],
			      originalAttributeGroups[1],
			      clipResult.first,newData1);

		    auto newData2=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();

		    interpolateAttributeGroup<true>(
			      originalAttributeGroups[0],
			      originalAttributeGroups[1],
			      clipResult.second,newData2);
		    return;
	       }



		    
	       //perspectiveDivision first
	       perspectiveDivision(point1);
	       perspectiveDivision(point2);
	       clipResult=
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
		    auto newData=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();

		    interpolateAttributeGroup<false>(
			      originalAttributeGroups[0],
			      originalAttributeGroups[1],
			      clipResult.first,newData);
	       }


	       if (clipResult.second==1.0)
	       {
		    clippedPrimitiveGroup.
			 insertOriginalIndex(vertexIndex[1]);
	       }
	       else
	       {

		    auto newData=clippedPrimitiveGroup.
			 writeClipGeneratedAttribute();

		    interpolateAttributeGroup<false>(
			      originalAttributeGroups[0],
			      originalAttributeGroups[1],
			      clipResult.second,newData);
	       }

	  }


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
