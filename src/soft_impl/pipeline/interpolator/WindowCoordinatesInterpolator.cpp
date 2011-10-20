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
	       (const Vec4& homogenousCoord1,const Vec4& homogenousCoord2,
		const Vec4& normalizedCoord1,const Vec4& normalizedCoord2,
		const WindowCoordinates& winCoord1,
		int majorDelta,
		const WindowCoordinates& toInterpolate,MajorDim majorDim)const
	       {
		    int index=int(majorDim);

		    return float(toInterpolate[index]-winCoord1[index])
			 /majorDelta;
	       }
     
} /* my_gl */
