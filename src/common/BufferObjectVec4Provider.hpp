/*
 * =====================================================================================
 *
 *       Filename:  BufferObjectVec4Provider.hpp
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

#ifndef BUFFER_OBJECT_VEC4_PROVIDER_HPP

#define BUFFER_OBJECT_VEC4_PROVIDER_HPP

#include "common/ArrayVec4Provider.hpp"

namespace my_gl {

     class BufferObject ;

     class BufferObjectVec4Provider :public ArrayVec4Provider{
     public:
     	BufferObjectVec4Provider (const BufferObject& bufferObject,
		  size_t offset,int componentNumber,DataType dataType,
		  size_t stride,bool normalize=false);

	virtual Vec4 value();

	virtual void next(size_t steps=1);
     
     private:
	const BufferObject& _bufferObject;
	size_t _currentOffset;
     };
	
} /* my_gl */


#endif /* end of include guard: BUFFER_OBJECT_VEC4_PROVIDER_HPP */

