/*
 * =====================================================================================
 *
 *       Filename:  ArrayBufferObject.hpp
 *
 *    Description:  glBufferData array buffer object
 *
 *        Version:  1.0
 *        Created:  2011-9-15 13:27:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ARRAY_BUFFER_OBJECT_HPP

#define ARRAY_BUFFER_OBJECT_HPP

#include "BufferObject.hpp"
#include "Enum.hpp"

namespace my_gl {
     class ArrayBufferObject :public BufferObject{
     public:
     	ArrayBufferObject (Name name,BufferTarget target,
		  size_t size,void * data);
     
     private:
	BufferTarget _target;
     };
	
} /* my_gl */


#endif /* end of include guard: ARRAY_BUFFER_OBJECT_HPP */
