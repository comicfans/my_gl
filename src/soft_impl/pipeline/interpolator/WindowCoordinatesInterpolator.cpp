/*
 * =====================================================================================
 *
 *       Filename:  WindowCoordinatesInterpolator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-20 23:39:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "WindowCoordinatesInterpolator.hpp"

namespace my_gl {

	  float WindowCoordinatesInterpolator::getPercent
	       (const CoordInfo& coord1,
		const CoordInfo& coord2,
		const WindowCoordinates& toInterpolate,
		int majorDelta,
		MajorDim majorDim)const
	       {
		    int index=int(majorDim);

		    return float(toInterpolate[index]-
			      coord1.windowCoord[index])
			 /majorDelta;
	       }
     
} /* my_gl */
