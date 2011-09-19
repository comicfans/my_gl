/*
 * =====================================================================================
 *
 *       Filename:  BufferObjectVectorProvider.cpp
 *
 *    Description:  implementation of BufferObjectVectorProvider
 *
 *        Version:  1.0
 *        Created:  2011-9-19 15:38:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "BufferObjectVectorProvider.hpp"
#include "object/BufferObject.hpp"

namespace my_gl {

     BufferObjectVectorProvider::BufferObjectVectorProvider 
	  (const BufferObject& bufferObject,
		  size_t offset,DataType dataType,int componentNumber,
		  size_t stride,bool normalize)
	  :ArrayVectorProvider(dataType,componentNumber,stride,normalize),
	  _bufferObject(bufferObject),_currentOffset(offset)
	  {}
     Vector BufferObjectVectorProvider::vector()noexcept
     {
	  Vector ret=castRead(_bufferObject.getBufferPointer());

	  _currentOffset+=_blockSize;

	  return ret;
     }
} /* my_gl */
