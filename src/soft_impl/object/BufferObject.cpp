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


     BufferObject::BufferObject(Name name)
	  noexcept :_name(name)
     {}

     void BufferObject::bindData(size_t size,const void *data)
     {
	  _dataPointer.reset(new UntypedCowArray(size,data));
     }

     UntypedCowArray BufferObject::copyArray()const noexcept
     {
	  return *_dataPointer;
     }

     void BufferObject::subData(ptrdiff_t offset,  size_t size,const void *data)
	  noexcept
     {
	  auto& _data=*_dataPointer;
	  assert(offset>=0);
	  assert(offset<_data.size());
	  assert(size>=0);
	  assert(offset+size<_data.size());

	  _data.replace(offset, size, data);
     }

     Name BufferObject::name()const noexcept
     {return _name;}
	
} /* my_gl */
