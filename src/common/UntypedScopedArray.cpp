/*
 * =====================================================================================
 *
 *       Filename:  UntypedScopedArray.cpp
 *
 *    Description:  implementation of UntypedScopedArray
 *
 *        Version:  1.0
 *        Created:  2011-9-13 20:23:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "UntypedScopedArray.hpp"
namespace my_gl {

     UntypedScopedArray::UntypedScopedArray(void *p) noexcept :
	  _pointer(p){}
     UntypedScopedArray::~UntypedScopedArray() noexcept
     {
	  delete[] _pointer;
     }
	
} /* my_gl */
