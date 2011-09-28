/*
 * =====================================================================================
 *
 *       Filename:  BufferObjectVec4Provider.cpp
 *
 *    Description:  implementation of BufferObjectVec4Provider
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

#include "BufferObjectVec4Provider.hpp"
#include "object/BufferObject.hpp"

namespace my_gl {

     BufferObjectVec4Provider::BufferObjectVec4Provider 
	  (const BufferObject& bufferObject,
		  size_t offset,int componentNumber,DataType dataType,
		  size_t stride,bool normalize)
	  :ArrayVec4Provider(componentNumber,dataType,stride,normalize),
	  _bufferObject(bufferObject),_currentOffset(offset)
	  {}
     Vec4 BufferObjectVec4Provider::value()
     {
	  return castRead(_bufferObject.getBufferPointer());
     }

     void BufferObjectVec4Provider::next(size_t steps)
     {
	  _currentOffset+=_blockSize*steps;
     }

} /* my_gl */
