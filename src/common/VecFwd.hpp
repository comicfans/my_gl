/*
 * =====================================================================================
 *
 *       Filename:  VecFwd.hpp
 *
 *    Description:  forward declare of Vec4 Vec3
 *
 *        Version:  1.0
 *        Created:  2011-11-3 0:01:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VEC_FWD_HPP

#define VEC_FWD_HPP

#include <cstddef>

namespace my_gl {

     template<size_t L>
	  struct VecBase;

     typedef VecBase<4> Vec4;
     typedef VecBase<3> Vec3;
     typedef VecBase<2> Vec2;
	
} /* my_gl */


#endif /* end of include guard: VEC_FWD_HPP */
