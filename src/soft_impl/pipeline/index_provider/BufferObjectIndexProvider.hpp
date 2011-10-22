/*
 * =====================================================================================
 *
 *       Filename:  BufferObjectIndexProvider.hpp
 *
 *    Description:  provide index from buffer object array
 *
 *        Version:  1.0
 *        Created:  2011-10-22 21:06:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BUFFER_OBJECT_INDEX_PROVIDER_HPP

#define BUFFER_OBJECT_INDEX_PROVIDER_HPP

#include "ArrayIndexProvider.hpp"

namespace my_gl {

     class ArrayBufferObject;
     class BufferObjectIndexProvider :public ArrayIndexProvider{
     public:

	  BufferObjectIndexProvider
	       (DataType dataType,const ArrayBufferObject& bufferObject,const int offset);

	  virtual size_t getIndex(size_t index)const;

	  virtual ~BufferObjectIndexProvider ();
     
     private:

	const ArrayBufferObject& _bindedBufferObject;

	const int _offset;

     };
	
} /* my_gl */


#endif /* end of include guard: BUFFER_OBJECT_INDEX_PROVIDER_HPP */
