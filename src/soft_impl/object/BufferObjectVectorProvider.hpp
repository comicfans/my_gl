/*
 * =====================================================================================
 *
 *       Filename:  BufferObjectVectorProvider.hpp
 *
 *    Description:  read vector from buffer object
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

#ifndef BUFFER_OBJECT_VECTOR_PROVIDER_HPP

#define BUFFER_OBJECT_VECTOR_PROVIDER_HPP

#include "common/ArrayVectorProvider.hpp"

namespace my_gl {

     class BufferObject ;

     class BufferObjectVectorProvider :public ArrayVectorProvider{
     public:
     	BufferObjectVectorProvider (const BufferObject& bufferObject,
		  size_t offset,int componentNumber,DataType dataType,
		  size_t stride,bool normalize=false);

	virtual Vector value()noexcept;

	virtual void next(size_t steps=1)noexcept;
     
     private:
	const BufferObject& _bufferObject;
	size_t _currentOffset;
     };
	
} /* my_gl */


#endif /* end of include guard: BUFFER_OBJECT_VECTOR_PROVIDER_HPP */

