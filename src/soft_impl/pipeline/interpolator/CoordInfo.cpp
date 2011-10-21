/*
 * =====================================================================================
 *
 *       Filename:  CoordInfo.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-21 14:38:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "CoordInfo.hpp"

namespace my_gl {

	
	CoordInfo::CoordInfo
	     (const Vec4& initValue)
	     :homogenousCoord(initValue),
	     normalizedCoord(initValue/initValue.w())
	{
	}
} /* my_gl */
