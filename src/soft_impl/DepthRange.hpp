/*
 * =====================================================================================
 *
 *       Filename:  DepthRange.hpp
 *
 *    Description:  depth range value of glDepthRange
 *
 *        Version:  1.0
 *        Created:  2011-11-1 11:45:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef DEPTH_RANGE_HPP

#define DEPTH_RANGE_HPP
namespace my_gl {

     struct DepthRange {
	  double nearValue;
	  double farValue;
	  /** 
	   * @brief diff=far-near;
	   */
	  double diff;

	  /** 
	   * @brief should be called after value change
	   * TODO need refactor
	   */
	  void update();

	  DepthRange(double nearSet=0,double farSet=1);
     } /* optional variable list */;
	
} /* my_gl */



#endif /* end of include guard: DEPTH_RANGE_HPP */
