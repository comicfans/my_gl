/*
 * =====================================================================================
 *
 *       Filename:  ClientArrayVec4Provider.hpp
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

#ifndef CLIENT_ARRAY_VEC4_PROVIDER_HPP

#define CLIENT_ARRAY_VEC4_PROVIDER_HPP

#include "ArrayVec4Provider.hpp"

namespace my_gl {
	
     class ClientArrayVec4Provider :public ArrayVec4Provider{
     public:
     	ClientArrayVec4Provider (const void* pointer,
		  int componentNumber,DataType dataType,
		  size_t stride,bool normalize=false);

	virtual Vec4 value();

	virtual void next(size_t steps=1);
     
     private:
	const int8_t *_currentPointer;
     };
} /* my_gl */



#endif /* end of include guard: CLIENT_ARRAY_VEC4_PROVIDER_HPP */
