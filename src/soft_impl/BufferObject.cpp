/*
 * =====================================================================================
 *
 *       Filename:  BufferObject.cpp
 *
 *    Description:  implementation of BufferObject
 *
 *        Version:  1.0
 *        Created:  2011-9-13 20:31:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "BufferObject.hpp"


namespace my_gl {


     BufferObject::BufferObject(BufferTarget target,size_t size,void *data)
	  noexcept :_target(target),_data(size,data)
     {}

     void BufferObject::subData(ptrdiff_t offset,  size_t size,  void *data)
	  noexcept
     {
	  assert(offset>=0);
	  assert(offset<_data.size());
	  assert(size>=0);
	  assert(offset+size<_data.size());

	  _data.replace(offset, size, data);
     }
	
} /* my_gl */
