/*
 * =====================================================================================
 *
 *       Filename:  ClientArrayVectorProvider.cpp
 *
 *    Description:  implementation of ClientArrayVectorProvider
 *
 *        Version:  1.0
 *        Created:  2011-9-19 13:51:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "ClientArrayVectorProvider.hpp"

namespace my_gl {
     ClientArrayVectorProvider::ClientArrayVectorProvider 
	  (const void* pointer,int componentNumber,DataType dataType, 
	   size_t stride,bool normalize)noexcept
	  :ArrayVectorProvider(componentNumber,dataType,stride,normalize),
	   _currentPointer(static_cast<const int8_t*>(pointer))
	  {
	  }

     Vector ClientArrayVectorProvider::value()noexcept
     {
	  return castRead(_currentPointer);
     }

     void ClientArrayVectorProvider::next(size_t steps)noexcept
     {
	  _currentPointer+=_blockSize*steps;
     }

} /* my_gl */
