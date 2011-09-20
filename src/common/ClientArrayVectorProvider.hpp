/*
 * =====================================================================================
 *
 *       Filename:  ClientArrayVectorProvider.hpp
 *
 *    Description:  read vector from client memory
 *
 *        Version:  1.0
 *        Created:  2011-9-19 13:25:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CLIENT_ARRAY_VECTOR_PROVIDER_HPP

#define CLIENT_ARRAY_VECTOR_PROVIDER_HPP

#include "ArrayVectorProvider.hpp"

namespace my_gl {
	
     class ClientArrayVectorProvider :public ArrayVectorProvider{
     public:
     	ClientArrayVectorProvider (const void* pointer,
		  int componentNumber,DataType dataType,
		  size_t stride,bool normalize=false)noexcept;

	virtual Vector value()noexcept;

	virtual void next(size_t steps=1)noexcept;
     
     private:
	const int8_t *_currentPointer;
     };
} /* my_gl */



#endif /* end of include guard: CLIENT_ARRAY_VECTOR_PROVIDER_HPP */
