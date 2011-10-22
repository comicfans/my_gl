/*
 * =====================================================================================
 *
 *       Filename:  PointerFunction.hpp
 *
 *    Description:  make void* int* convert simple
 *
 *        Version:  1.0
 *        Created:  2011-10-22 21:36:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef POINTER_FUNCTION_HPP

#define POINTER_FUNCTION_HPP

#include <cstdint>

namespace my_gl {

     inline const int8_t* add(const void* p,int value)
     {
	  const int8_t* temp=static_cast<const int8_t*>(p);
	  return temp+value;
     }

     inline int toInt(const void* p)
     {
	  return reinterpret_cast<intptr_t>(p);
     }
	
} /* my_gl */


#endif /* end of include guard: POINTER_FUNCTION_HPP */
