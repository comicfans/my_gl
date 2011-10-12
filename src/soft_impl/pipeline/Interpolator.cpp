/*
 * =====================================================================================
 *
 *       Filename:  Interpolator.cpp
 *
 *    Description:  implementation of Interpolator
 *
 *        Version:  1.0
 *        Created:  2011-10-9 17:12:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Interpolator.hpp"

namespace my_gl {
	
	  
     void Interpolator::calculate(const Vec4& source,
	       const Vec4& destination,float persent,Vec4& result)
     {
	  result=source*(1-persent)+destination*persent;
     }
} /* my_gl */
