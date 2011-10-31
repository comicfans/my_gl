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

     struct WinCoord;

     struct LineInfo {

	  enum class DimAxis{Y,X};

	  LineInfo(const WinCoord& coord1,
		    const WinCoord& coord2);

	  LineInfo(int deltaYSet,int deltaXSet,DimAxis majorDimSet);

	  LineInfo(const LineInfo& rhs);

	  /** 
	   * @brief makes point1->point2 point2->point1,
	   * can adjust majorDelta sign
	   * 
	   * @return 
	   */
	  LineInfo revert()const;

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
