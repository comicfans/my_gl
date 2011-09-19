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
	  (const void* pointer,size_t offset,size_t jumpBlocks,DataType dataType, 
	   int componentNumber,size_t stride,bool normalize)
	  :ArrayVectorProvider(dataType,componentNumber,stride,normalize)
	  {
	       _currentPointer=static_cast<const int8_t*>(pointer)+offset+_blockSize*jumpBlocks;
	  }

     Vector ClientArrayVectorProvider::vector()noexcept
     {
	  Vector ret=castRead(_currentPointer);
	  _currentPointer+=_blockSize;
	  return ret;
     }

} /* my_gl */
