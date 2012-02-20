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
	  (const void* pointer,int componentNumber,GLenum dataType, 
	   size_t stride,bool normalize)
	  :ArrayVec4Provider(componentNumber,dataType,stride,normalize),
	   _pointer(pointer)
	  {
	  }

     Vec4 ClientArrayVec4Provider::getValue(size_t index)
     {
	  return castRead(_pointer,index);
     }


} /* my_gl */
