/*
 * =====================================================================================
 *
 *       Filename:  BufferObjectIndexProvider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-22 21:12:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include "BufferObjectIndexProvider.hpp"

#include "common/PointerFunction.hpp"

#include "object/ArrayBufferObject.hpp"
namespace my_gl {
     BufferObjectIndexProvider::BufferObjectIndexProvider
	  (DataType dataType,const ArrayBufferObject& bufferObject,const int offset)
	  :ArrayIndexProvider(dataType),
	  _bindedBufferObject(bufferObject),
	  _offset(offset)
	  {}

     BufferObjectIndexProvider::~BufferObjectIndexProvider (){}

     size_t BufferObjectIndexProvider::getIndex(size_t index)const
     {
	  return ArrayIndexProvider::getIndex(
			 add(_bindedBufferObject.getBufferPointer(),_offset),
			 index);
     }



} /* my_gl */
