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
	  deltaY(coord2.first-coord1.first),
	  deltaX(coord2.second-coord1.second),
	  majorDim(abs(deltaX)>abs(deltaY)?
		    DimAxis::X:
		    DimAxis::Y),
	  nonMajorDim(DimAxis(1-int(majorDim)))
	  {}

     LineInfo::LineInfo(int deltaYSet,int deltaXSet,DimAxis majorDimSet)
	  :deltaY(deltaYSet),deltaX(deltaXSet),
	  majorDim(majorDimSet),
	  nonMajorDim(DimAxis(1-int(majorDim)))
     {
	  assert(abs(deltaX)>abs(deltaY)?
		    (majorDim==DimAxis::X):
		    (majorDim==DimAxis::Y));
     }

	  
     LineInfo::LineInfo(const LineInfo& rhs)
	  :deltaY(rhs.deltaY),deltaX(rhs.deltaX),
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
	  return LineInfo(-deltaY,-deltaX,majorDim);
     }

     bool LineInfo::parallelToAxis()const
     {
	  return (deltaX==0)|| 
	       (deltaY==0);
     }
} /* my_gl */
