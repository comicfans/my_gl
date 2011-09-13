/*
 * =====================================================================================
 *
 *       Filename:  BufferObject.hpp
 *
 *    Description:  data respect to glBufferData
 *
 *        Version:  1.0
 *        Created:  2011-9-13 20:11:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef BUFFER_OBJECT_HPP

#define BUFFER_OBJECT_HPP

#include <cstddef>

#include "common/UntypedScopedArray.hpp"


namespace my_gl {
     class BufferObject {
     public:

	  enum Target{ARRAY_BUFFER,ELEMENT_ARRAY_BUFFER};

	  BufferObject(Target target,size_t size,void *data) noexcept;
     
     private:
	       Target _target;
	       size_t _size;
	       UntypedScopedArray _data;
     };
	
} /* my */

#endif /* end of include guard: BUFFER_OBJECT_HPP */
