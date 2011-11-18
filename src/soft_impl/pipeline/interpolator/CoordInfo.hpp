/*
 * =====================================================================================
 *
 *       Filename:  CoordInfo.hpp
 *
 *    Description:  class to store coordinates related information
 *
 *        Version:  1.0
 *        Created:  2011-10-21 14:36:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COORD_INFO_HPP

#define COORD_INFO_HPP

#include "common/Vec.hpp"

#include "pipeline/rasterizer/WinCoord.hpp"


namespace my_gl {

     /** 
      * @brief group WinCoord HomogenousCoord
      * and NormalizedCoord together , 
      * when Interpolating,interpolator decide
      * which coord is used to calculate
      */
     struct CoordInfo {

	  /** 
	   * @brief construct CoordInfo from homogenousCoord
	   * 
	   * @param initValue
	   */
	  CoordInfo(const Vec4& initValue);

	  /** 
	   * @brief coord comes from vertex shader
	   * just transformed by modelViewProjection
	   * (projection*modelView*Vec4)
	   */
	  const Vec4& homogenousCoord;

	  /** 
	   * @brief homogenousCoord divides w()
	   * every component should in range [0~1]
	   * comes from homogenousCoord int value
	   */
	  Vec4 normalizedCoord;

	  //undefined value,need manual init
	  //WinCoord calculation need ViewportParameter 
	  //so can not make this value inited
	  WinCoord windowCoord;

     };
	
} /* my_gl */

#endif /* end of include guard: COORD_INFO_HPP */
