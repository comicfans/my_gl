/*
 * =====================================================================================
 *
 *       Filename:  ArrayBufferObject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-17 15:53:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ArrayBufferObject.hpp"
#include "common/UntypedArray.hpp"

namespace my_gl {

     ArrayBufferObject::ArrayBufferObject(Name name)noexcept
	  :BufferObject(name){}
	
     void ArrayBufferObject::bindData(size_t size,const void *data)
     {
	  _dataPointer.reset(new UntypedArray(size,data));
     }

     void ArrayBufferObject::subData(ptrdiff_t offset,  size_t size,const void *data)
	  noexcept
     {
	  auto& _data=*_dataPointer;
	  assert(offset>=0);
	  assert(offset<_data.size());
	  assert(size>=0);
	  assert(offset+size<_data.size());

	  _data.replace(offset, size, data);
     }


} /* my_gl */
