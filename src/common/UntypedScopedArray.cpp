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

#include <algorithm>
using std::copy_n;

namespace my_gl {

     UntypedScopedArray::UntypedScopedArray
	  (void *p,size_t size) 
	  :_size(size)
	  {
	       _pointer=new int8_t[_size];
	       int8_t *temp=static_cast<int8_t*>(p);
	       copy_n(temp, _size, _pointer);
	  }
     UntypedScopedArray::~UntypedScopedArray() noexcept
     {
	       delete[] _pointer;
     }

     size_t UntypedScopedArray::size()const noexcept
     {
	  return _size;
     }

     void UntypedScopedArray::replace
	  (ptrdiff_t offset,  size_t size,  void *data)noexcept
	  {
	       assert(offset>0);
	       assert(offset+size<_size);
	       int8_t *temp=static_cast<int8_t*>(data);
	       copy_n(temp,size,_pointer+offset);
	  }
	
     
} /* my_gl */
