/*
 * =====================================================================================
 *
 *       Filename:  LineInfo.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-21 21:08:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LineInfo.hpp"

#include <algorithm>
#include <cmath>
#include <cassert>

#include "WindowCoordinates.hpp"

namespace my_gl {


     using std::max;
     using std::abs;

     LineInfo::LineInfo(const WindowCoordinates& coord1,
		    const WindowCoordinates& coord2)
	  :
	  deltaX(coord2.first-coord1.first),
	  deltaY(coord2.second-coord1.second),
	  majorDim(deltaX>deltaY?
		    DimAxis::X:
		    DimAxis::Y),
	  nonMajorDim(DimAxis(1-int(majorDim)))
	  {}

     LineInfo::LineInfo(int deltaXSet,int deltaYSet,DimAxis majorDimSet)
	  :deltaX(deltaXSet),deltaY(deltaYSet),
	  majorDim(majorDimSet),
	  nonMajorDim(DimAxis(1-int(majorDim)))
     {
	  assert(deltaX>deltaY?
		    (majorDim==DimAxis::X):
		    (majorDim==DimAxis::Y));
     }


     int LineInfo::getMajorDelta()const
     {
	  return majorDim==DimAxis::X?
	       deltaX:deltaY;
     }

	  
     int LineInfo::getNonMajorDelta()const
     {
	  return majorDim==DimAxis::X?
	       deltaY:deltaX;
     }


     bool LineInfo::isOnlyPoint()const
     {

	  return max(abs(deltaX),
		    abs(deltaY))<=1;

     }

     bool LineInfo::parallelToAxis()const
     {
	  return (deltaX==0)|| 
	       (deltaY==0);
     }
} /* my_gl */