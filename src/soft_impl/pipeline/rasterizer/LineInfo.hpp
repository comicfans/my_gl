/*
 * =====================================================================================
 *
 *       Filename:  LineInfo.hpp
 *
 *    Description:  information of a line segment
 *
 *        Version:  1.0
 *        Created:  2011-10-21 20:39:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LINE_INFO_H

#define LINE_INFO_H

namespace my_gl {

     struct WindowCoordinates;

     struct LineInfo {

	  enum class DimAxis{Y,X};

	  LineInfo(const WindowCoordinates& coord1,
		    const WindowCoordinates& coord2);

	  LineInfo(int deltaYSet,int deltaXSet,DimAxis majorDimSet);

	  const int deltaY;
	  const int deltaX;

	  const DimAxis majorDim;
	  const DimAxis nonMajorDim;

	  int getMajorDelta()const;
	  int getNonMajorDelta()const;

	  bool isOnlyPoint()const;
	  bool parallelToAxis()const;

     } /* optional variable list */;
	
} /* my_gl */


#endif /* end of include guard: LINE_INFO_H*/
