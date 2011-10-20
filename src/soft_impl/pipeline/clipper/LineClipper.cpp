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
#include <cmath>

#include "pipeline/ClippedPrimitiveGroup.hpp"
#include "pipeline/interpolator/Interpolator.hpp"
#include "PointClipper.hpp"

using std::max;
using std::min;
using std::abs;


namespace my_gl {

     static const LineClipper::ClipPercent OUT_OF_PERCENT={1,0};

     LineClipper::~LineClipper(){}

     

	/** 
	 * @brief clip in homogenous coordinates,work 
	 * in all situation
	 * 
	 * @param point1
	 * @param point2
	 * 
	 * @return 
	 */
     float LineClipper::clipInHomogenousCoordinates
	  (const Vec4& point1,const Vec4& point2,
	   ClipDim clipDim,ClipSide clipSide)
	  {

	       
	       int dIndex=int(clipDim);

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
	       
	       float d1=point1[dIndex],
		     d2=point2[dIndex];

	       float deltaD=d2-d1;

	       float w1=point1.w();

	       float deltaW= point2.w()-w1;

	       float rowColumnValue=int(clipSide)*deltaW+deltaD;

	       if (rowColumnValue==0)
	       {
		    //parall in this direction

		    if (clipSide==ClipSide::MIN)
		    {
			 //if one in,another is in
			 //or two points is out
			 return abs(d1)<abs(w1)?0:2;
		    }
		    else
		    {
			 return abs(d1)<abs(w1)?1:-1;
		    }

	       }


	       float wValue=-int(clipSide)*
		    (deltaW*d1-deltaD*w1)/rowColumnValue;

	       return (wValue-point1.w())/deltaW;
	
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
	      ClippedPrimitiveGroup& clippedPrimitiveGroup)
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

		       Interpolator::interpolateAttributeGroup
			    (point1Attributes, point2Attributes, 
			     percent, newData.second);

		       return newData.first;
		  }
	     }

     LineClipper::ClipPercent LineClipper::parallelClip
	  (const Vec4& point1,const Vec4& point2,ClipDim clipDim)
	  {
		    float minClip=
			 clipInHomogenousCoordinates
			 (point1, point2,clipDim,ClipSide::MIN);

		    if (minClip>1)
		    {
			 //discade this line
			 return OUT_OF_PERCENT;
		    }
		    
		    float maxClip=
			 clipInHomogenousCoordinates
			 (point1,point2,clipDim,ClipSide::MAX);

		    if (maxClip<0)
		    {
			 //discade this line
			 return OUT_OF_PERCENT;
		    }

		    return {minClip,maxClip};
	  }

	
     bool LineClipper::outOfClipVolume(const ClipPercent& clipResult)
     {
	  return clipResult.first>clipResult.second;
     }


     LineClipper::ClipPercent LineClipper::mergePercent
	     (const ClipPercent& lhs,const ClipPercent& rhs)
	     {
		  return {max(lhs.first,rhs.first),
		       min(lhs.second,rhs.second)};

	     }

     void LineClipper::elementClip
	  (const ConstAttributeGroupRef* originalAttributeGroups,
	   const size_t *vertexIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {
	       auto &point1=getVertex(originalAttributeGroups[0]);

	       auto &point2=getVertex(originalAttributeGroups[1]);


	       ClipPercent result={0,1};

	       for (int i=0; i<3 ; ++i)
	       {
		    ClipPercent thisResult=
			 parallelClip(point1,point2,ClipDim(i));
		    if (outOfClipVolume(thisResult))
		    {
			 return;
		    }
		    result=mergePercent(thisResult,result);
	       }

	       size_t point1Index=vertexIndex[0];
	       size_t point2Index=vertexIndex[1];

	       insertInterpolatedAttributes(
			 originalAttributeGroups[point1Index],
			 point1Index,
			 originalAttributeGroups[point2Index],
			 point2Index,
			 result.first,clippedPrimitiveGroup);

	       insertInterpolatedAttributes(
			 originalAttributeGroups[point1Index],
			 point1Index,
			 originalAttributeGroups[point2Index],
			 point2Index,
			 result.second,clippedPrimitiveGroup);
	  }


     
} /* my_gl */
