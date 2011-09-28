/*
 * =====================================================================================
 *
 *       Filename:  ClientArrayVec4Provider.cpp
 *
 *    Description:  implementation of ClientArrayVec4Provider
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
#include "ClientArrayVec4Provider.hpp"

namespace my_gl {
     ClientArrayVec4Provider::ClientArrayVec4Provider 
	  (const void* pointer,int componentNumber,DataType dataType, 
	   size_t stride,bool normalize)
	  :ArrayVec4Provider(componentNumber,dataType,stride,normalize),
	   _currentPointer(static_cast<const int8_t*>(pointer))
	  {
	  }

     Vec4 ClientArrayVec4Provider::value()
     {
	  return castRead(_currentPointer);
     }

     void ClientArrayVec4Provider::next(size_t steps)
     {
	  _currentPointer+=_blockSize*steps;
     }

} /* my_gl */
