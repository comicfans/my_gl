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

     struct CoordInfo {

	  CoordInfo(const Vec4& initValue);

	  const Vec4& homogenousCoord;

	  Vec4 normalizedCoord;

	  //undefined value,need manual init
	  WinCoord windowCoord;

     };
	
} /* my_gl */

#endif /* end of include guard: COORD_INFO_HPP */
