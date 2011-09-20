/*
 * =====================================================================================
 *
 *       Filename:  ArrayBufferObject.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-17 15:46:18
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

namespace my_gl {

     class ArrayBufferObject : public BufferObject{
     public:

	  ArrayBufferObject(Name name) noexcept;

	  void bindData(size_t size,const void *data);

	  void subData(ptrdiff_t offset,size_t size,const void *data) noexcept;


     };
	
} /* my_gl */




#endif /* end of include guard: ARRAY_BUFFER_OBJECT_HPP */
