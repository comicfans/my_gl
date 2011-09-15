/*
 * =====================================================================================
 *
 *       Filename:  ArrayBufferObject.cpp
 *
 *    Description:  implementation of ArrayBufferObject
 *
 *        Version:  1.0
 *        Created:  2011-9-15 13:29:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ArrayBufferObject.hpp"
namespace my_gl {
     
     ArrayBufferObject::ArrayBufferObject 
	  (Name name,BufferTarget target,size_t size,const void * data)
	  :BufferObject(name,size,data),_target(target)
	  {}
	
} /* my_gl */
