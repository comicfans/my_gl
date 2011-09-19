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
#include "common/UntypedArray.hpp"

namespace my_gl {


     BufferObject::BufferObject(Name name)
	  noexcept :_name(name)
     {}

     Name BufferObject::name()const noexcept
     {return _name;}

     const void* BufferObject::getBufferPointer()const noexcept
     {
	  return _dataPointer->get();
     }
	
} /* my_gl */
