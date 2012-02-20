/*
 * =====================================================================================
 *
 *       Filename:  LineInfo.hpp
 *
 *    Description:  information of a line segment
 *    test if this is a point ,is parallel to Axis
 *    store which Dim is major Dim
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

#ifndef LINE_INFO_HPP

#define LINE_INFO_HPP

namespace my_gl {

     struct WinCoord;

     /** 
	   * @brief which delta of Dim is bigger,
	   * bigger Dim makes percent calculation 
	   * more precision
	   */
     struct LineInfo {

	  enum DimAxis{X,Y};

	  /** 
	   * @brief construct LineInfo from two coord
	   *
	   * 
	   * @param coord1
	   * @param coord2
	   */
	  LineInfo(const WinCoord& coord1,
		    const WinCoord& coord2);

	  /** 
	   * @brief construct LineInfo from known data
	   * but this call will do a check to
	   * determind whether these data are correct
	   * 
	   * @param deltaXSet
	   * @param deltaYSet
	   * @param majorDimSet
	   */
	  LineInfo(int deltaXSet,int deltaYSet,DimAxis majorDimSet);

	  LineInfo(const LineInfo& rhs);

	  /** 
	   * @brief makes point1->point2 point2->point1,
	   * can adjust majorDelta sign
	   * 
	   * @return 
	   */
	  LineInfo revert()const;

	  const int deltaX;
	  const int deltaY;

	  const DimAxis majorDim;
	  const DimAxis nonMajorDim;

	  int getMajorDelta()const;
	  int getNonMajorDelta()const;

	  bool isOnlyPoint()const;
	  bool parallelToAxis()const;

     } /* optional variable list */;
	
} /* my_gl */


#endif /* end of include guard: LINE_INFO_HPP*/
