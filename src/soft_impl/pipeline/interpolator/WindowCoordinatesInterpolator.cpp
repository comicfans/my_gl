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

#include "CoordInfo.hpp"

#include "pipeline/rasterizer/LineInfo.hpp"
#include "pipeline/rasterizer/WindowCoordinates.hpp"

namespace my_gl {

     WindowCoordinatesInterpolator::~WindowCoordinatesInterpolator(){}
	  float WindowCoordinatesInterpolator::getPercent(
		    const CoordInfo& coord1,const CoordInfo& coord2,
		    const LineInfo& lineInfo,
		    const WindowCoordinates& toInterpolate)const
	       {
		    int index=int(lineInfo.majorDim);

		    return float(toInterpolate[index]-
			      coord1.windowCoord[index])
			 /lineInfo.getMajorDelta();
	       }
     
} /* my_gl */
