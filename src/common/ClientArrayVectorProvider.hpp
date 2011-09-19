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
     	ClientArrayVectorProvider (const void* pointer,DataType dataType,
		  int componentNumber,size_t stride,size_t offset);

	virtual Vector vector()noexcept;
     
     private:
	const void *_currentPointer;
     };
} /* my_gl */



#endif /* end of include guard: CLIENT_ARRAY_VECTOR_PROVIDER_HPP */
