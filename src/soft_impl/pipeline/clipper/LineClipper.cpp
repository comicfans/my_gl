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
using std::minmax;


namespace my_gl {

     static const LineClipper::ClipPercent OUT_OF_PERCENT={2,-2};
     static const LineClipper::ClipPercent ALL_IN_PERCENT={0,1};

     LineClipper::~LineClipper(){}

     
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

     inline static bool oneDimIn(const Vec4& point,LineClipper::ClipDim clipDim)
     {
	  return abs(point[int(clipDim)])<=abs(point.w());
     }

     LineClipper::ClipPercent LineClipper::parallelClip
	  (const Vec4& point1,const Vec4& point2,ClipDim clipDim)
	  {

	       bool point1In=oneDimIn(point1,clipDim),
		    point2In=oneDimIn(point2,clipDim);

	       if (point1In&&point2In)
	       {
		    return {0,1};
	       }
	       
		     
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
	       //              ~~~^~~~ factor
	       //
	       //  since float number error makes final abs(x) >=  abs(w) 
	       //  clipResult may makes x and w out of clip volume a little
	       
	       double d1=point1[dIndex],
		      d2=point2[dIndex];

	       double deltaD=d2-d1;

	       double w1=point1.w();

	       double deltaW= point2.w()-w1;

	       double rowColumnMax=-deltaW+deltaD,
		     //cross point of min
		     rowColumnMin=deltaW+deltaD;

	       if (rowColumnMax==0 || rowColumnMin==0)
	       {
		    //parallel to this plane
		    if (abs(point1(dIndex))<=abs(point1.w()))
		    {
			 //all in
			 return ALL_IN_PERCENT; 
		    }
		    else
		    {
			 return OUT_OF_PERCENT;
		    }
	       }
	       
	       //two cross point
	       double wMax=-(deltaW*d1-deltaD*w1)/rowColumnMax,
		     wMin=-(deltaW*d1-deltaD*w1)/rowColumnMin;

	       double percentMax=(wMax-point1.w())/deltaW,
		     percentMin=(wMin-point1.w())/deltaW;
	
	       auto minMax=minmax(percentMin,percentMax);

	       if (minMax.first>=0 && minMax.second<=1)
	       {
		    return minMax;
	       }
	       else
	       {
		    //two cross point at same side
		    if ((minMax.second<=0 || minMax.first>=1)
			      //two cross point at different side
			      ||(minMax.first <=0 && minMax.second >=1))
		    {
			 //check one point in state,if in,all in
			 //if out ,all out
			 if (point1In)
			 { return ALL_IN_PERCENT;}
			 else
			 { return OUT_OF_PERCENT; }
		    }
		    else 
		    {
			 //one point between [0,1],but another
			 //point outside [0,1]
			 float between=minMax.first>=0?
			      minMax.first:minMax.second;
			 if (point1In)
			 {
			      return {0,between};
			 }
			 else
			 {
			      return {between,1};
			 }
		    }
	       }
	       

    
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
	  (ConstAttributeGroupRefList& originalAttributeGroups,
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
