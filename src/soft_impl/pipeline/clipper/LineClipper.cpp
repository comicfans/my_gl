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

     void LineClipper::interpolateAttributeGroup(
	       const ConstAttributeGroupRef& attributeGroupSource, 
	       const ConstAttributeGroupRef& attributeGroupDestination,
	       float percent,AttributeGroupRef& attributeGroupResult,
	       bool hasInfinit)
     {
	  for (int i=0; i<attributeGroupSource.size(); ++i)
	  {
		    
	       Interpolator::calculate(attributeGroupSource[i], 
			 attributeGroupDestination[i], percent, 
			 attributeGroupResult[i]);
	  }

	  if (hasInfinit)
	  {
	       perspectiveDivision(
			 VertexAttributeBuffer::
			 getVertex(attributeGroupResult));
	  }

     }
     static ClipPercent parallelPlaneClipInHomogenousCoordinates
	  (const Vec4& point1,const Vec4& point2,
	   LineClipper::ClipPlane clipPlane)
	  {
	       //should not be the same(0)
	       assert(point1.w()!=point2.w());

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


	/** 
	 * @brief clip in homogenous coordinates,work 
	 * in all situation
	 * 
	 * @param point1
	 * @param point2
	 * 
	 * @return 
	 */
     static ClipPercent clipInHomogenousCoordinates
	  (const Vec4& point1,const Vec4& point2)
	  {

	       ClipPercent result={0,1};

	       for (int i=0; i<3; ++i)
	       {
		    ClipPercent thisClipResult=
			 parallelPlaneClipInHomogenousCoordinates(
			      point1,point2,
			      LineClipper::ClipPlane(i));
		    result.first=max(result.first,
			      thisClipResult.first);
		    result.second=min(result.second,
			      thisClipResult.second);
	       }

	       return result;  
	  }

     ClipPercent parallelPlaneClip
	  (const Vec4& point1,const Vec4& point2,
	   LineClipper::ClipPlane crossPlane)
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



     PackedResult LineClipper::commonClip
	  (const Vec4& point1,const Vec4& point2,ClipPlane clipPlane)
	  {
	
	       bool point1Infinit=isInfinit(point1),
		    point2Infinit=isInfinit(point2);

	       if(point1Infinit && point2Infinit)
	       {
		    return {true,OUT_CLIP_PERCENT};
	       }

	       if(point1Infinit || point2Infinit)
	       {
		    //use clip in homogeonous coordinates
		    auto clipResult=
			parallelPlaneClipInHomogenousCoordinates 
			 (point1,point2,clipPlane);
		    return {true,clipResult};
	       }
	       else
	       {
	        auto clipResult=
			 parallelPlaneClip(point1, point2,clipPlane);

	       return {false,clipResult};
	       }

	  }

	/** 
	 * @brief Liang-Barsky clip algorithm work only with in 
	 * normalized device coordinates [-1,1]
	 * 
	 * @param first firs point
	 * @param second second point 
	 * @param crossPlane which plane to get intersect
	 * 
	 * @return a parameterize percent pair, should first<=second
	 * if first>second ,this line lies totally out of clip volume
	 */
     static ClipPercent clipLiangBarsky
	  (const Vec4 &point1, 
	       const Vec4 &point2)
	  {

	       ClipPercent currentResult={0,1};

	       for(int i=0;i<3;++i)
	       {

		    ClipPercent thisClipResult=parallelPlaneClip
			 (point1, point2, LineClipper::ClipPlane(i));

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


     static PackedResult commonClip(
	       const Vec4& point1,const Vec4& point2)
     {

	       bool point1Infinit=isInfinit(point1),
		    point2Infinit=isInfinit(point2);

	       if(point1Infinit && point2Infinit)
	       {
		    return {true,OUT_CLIP_PERCENT};
	       }


	       if(point1Infinit || point2Infinit)
	       {
		    //use clip in homogeonous coordinates
		    auto clipResult=
			 clipInHomogenousCoordinates
			 (point1,point2);
		    return {true,clipResult};
	       }
	       else
	       {
	        auto clipResult=
			 clipLiangBarsky(point1, point2);

	       return {false,clipResult};
	       }

     }

     bool LineClipper::onlyPoint(const ClipPercent& clipResult)
     {
	  return clipResult.first==clipResult.second;
     }

     size_t LineClipper::insertInterpolatedAttributes
	     (const ConstAttributeGroupRef& point1Attributes,
	      size_t point1Index,
	      const ConstAttributeGroupRef& point2Attributes,
	      size_t point2Index,
	      float percent,
	      ClippedPrimitiveGroup& clippedPrimitiveGroup,
	      bool hasInfinit)
	     {
		  if (percent==0)
		  {
		       clippedPrimitiveGroup.
			    insertOriginalIndex(point1Index);
		       return point1Index;
		  }
		  else if (percent==1)
		  {
		       clippedPrimitiveGroup.
			    insertOriginalIndex(point2Index);
		       return point2Index;
		  }
		  else
		  {
		       auto newData=clippedPrimitiveGroup.
			    writeClipGeneratedAttribute();

		       interpolateAttributeGroup
			    (point1Attributes, point2Attributes, 
			     percent, newData.second,hasInfinit);

		       return newData.first;
		  }
	     }


     void LineClipper::elementClip
	  (const ConstAttributeGroupRef* originalAttributeGroups,
	   const size_t *vertexIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {
	       auto &point1=VertexAttributeBuffer
		    ::getVertex(originalAttributeGroups[0]);

	       auto &point2=VertexAttributeBuffer
		    ::getVertex(originalAttributeGroups[1]);

	       PackedResult packedResult=
		    my_gl::commonClip(point1,point2);

	       if(outOfClipVolume(packedResult.second))
	       {
		    //discard this line
		    return;
	       }


	       bool hasInfinit=packedResult.first;
	       ClipPercent clipResult=packedResult.second;

	       size_t point1Index=vertexIndex[0];
	       size_t point2Index=vertexIndex[1];

	       insertInterpolatedAttributes(
			 originalAttributeGroups[point1Index],
			 point1Index,
			 originalAttributeGroups[point2Index],
			 point2Index,clipResult.first,
			 clippedPrimitiveGroup,hasInfinit);

	       insertInterpolatedAttributes(
			 originalAttributeGroups[point1Index],
			 point1Index,
			 originalAttributeGroups[point2Index],
			 point2Index,clipResult.second,
			 clippedPrimitiveGroup,hasInfinit);



	  }


     bool LineClipper::outOfClipVolume
	  (const ClipPercent& clipResult)
	  {
	       return clipResult.first>clipResult.second;
	  }



     
} /* my_gl */
