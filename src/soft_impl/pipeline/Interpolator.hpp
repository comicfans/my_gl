/*
 * =====================================================================================
 *
 *       Filename:  Interpolator.hpp
 *
 *    Description:  interpolate between values 
 *
 *        Version:  1.0
 *        Created:  2011-10-9 17:07:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef INTERPOLATOR_HPP

#define INTERPOLATOR_HPP

#include "common/Vec4.hpp"

namespace my_gl {

     struct Interpolator {
     public:

	  static Vec4 calculate(const Vec4& source,const Vec4& destination,float persent);
     
     };
	
} /* my_gl */


#endif /* end of include guard: INTERPOLATOR_HPP */
