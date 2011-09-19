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
	  (const void* pointer,DataType dataType, 
	   int componentNumber,size_t stride,size_t offset,bool normalize)
	  :ArrayVectorProvider(dataType,componentNumber,stride),
	   _normalize(normalize)
	  {
	       _currentPointer=static_cast<const int8_t*>(pointer)+offset;
	  }

     Vector ClientArrayVectorProvider::vector()noexcept
     {
	  Vector ret=castRead(_currentPointer,_normalize);
	  _currentPointer+=_blockSize;
	  return ret;
     }

} /* my_gl */
