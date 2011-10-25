/*
 * =====================================================================================
 *
 *       Filename:  BufferObjectVec4Provider.hpp
 *
 *    Description:  read vector from buffer object
 *    GL spec said: when client array is enabled
 *    and a none-zero buffer object is binded to GL_ARRAY_BUFFER
 *    call gl*Pointer function will copy current GL_ARRAY_BUFFER
 *    bind to correspond bind ,as intel gl impl,this means a 
 *    "object shadow copy",
 *    shadow copy means:
 *    1)if call gl*Pointer first,than call glBindBuffer with
 *    GL_ARRAY_BUFFER,new bind will not affect pointer data
 *    2)call gl*Pointer first,than call glBufferData to change
 *    GL_ARRAY_BUFFER data,pointer data will also change 
 *
 *    so BufferObjectVec4Provider must reference a BufferObject
 *    to do such trace
 *
 *        Version:  1.0
 *        Created:  2011-9-19 15:22:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BUFFER_OBJECT_VEC4_PROVIDER_HPP

#define BUFFER_OBJECT_VEC4_PROVIDER_HPP

#include "ArrayVec4Provider.hpp"

namespace my_gl {

     class BufferObject ;

     class BufferObjectVec4Provider :public ArrayVec4Provider{
     public:
     	BufferObjectVec4Provider (const BufferObject& bufferObject,
		  size_t offset,int componentNumber,DataType dataType,
		  size_t stride,bool normalize=false);

	virtual Vec4 getValue(size_t index);

     private:
	const BufferObject& _bufferObject;
	size_t _offset;
     };
	
} /* my_gl */


#endif /* end of include guard: BUFFER_OBJECT_VEC4_PROVIDER_HPP */

