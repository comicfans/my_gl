/*
 * =====================================================================================
 *
 *       Filename:  BufferObject.cpp
 *
 *    Description:  implementation of BufferObject
 *
 *        Version:  1.0
 *        Created:  2011-9-13 20:31:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "BufferObject.hpp"

namespace my_gl {


     BufferObject::BufferObject(Target target,size_t size,void *data)
	  noexcept :_target(target),_size(size),_data(data)
     {}
	
} /* my_gl */
