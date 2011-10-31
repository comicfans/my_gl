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

#include "WinCoord.hpp"

namespace my_gl {


     using std::max;
     using std::abs;

     LineInfo::LineInfo(const WinCoord& coord1,
		    const WinCoord& coord2)
	  :
	  deltaX(coord2.x()-coord1.x()),
	  deltaY(coord2.y()-coord1.y()),
	  majorDim(abs(deltaX)>abs(deltaY)?
		    DimAxis::X:
		    DimAxis::Y),
	  nonMajorDim(DimAxis(1-int(majorDim)))
	  {}

     LineInfo::LineInfo(int deltaXSet,int deltaYSet,DimAxis majorDimSet)
	  :deltaX(deltaXSet),deltaY(deltaYSet),
	  majorDim(majorDimSet),
	  nonMajorDim(DimAxis(1-int(majorDim)))
     {
	  assert(abs(deltaX)>abs(deltaY)?
		    (majorDim==DimAxis::X):
		    (majorDim==DimAxis::Y));
     }

	  
     LineInfo::LineInfo(const LineInfo& rhs)
	  :deltaX(rhs.deltaX),deltaY(rhs.deltaY),
	  majorDim(rhs.majorDim),
	  nonMajorDim(DimAxis(1-int(majorDim))){}


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

     LineInfo LineInfo::revert()const
     {
	  return LineInfo(-deltaX,-deltaY,majorDim);
     }

     bool LineInfo::parallelToAxis()const
     {
	  return (deltaX==0)|| 
	       (deltaY==0);
     }
} /* my_gl */
