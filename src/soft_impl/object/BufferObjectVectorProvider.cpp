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
		  size_t offset,int componentNumber,DataType dataType,
		  size_t stride,bool normalize)
	  :ArrayVectorProvider(componentNumber,dataType,stride,normalize),
	  _bufferObject(bufferObject),_currentOffset(offset)
	  {}
     Vector BufferObjectVectorProvider::value()noexcept
     {
	  return castRead(_bufferObject.getBufferPointer());
     }

     void BufferObjectVectorProvider::next(size_t steps)noexcept
     {
	  _currentOffset+=_blockSize*steps;
     }

} /* my_gl */
