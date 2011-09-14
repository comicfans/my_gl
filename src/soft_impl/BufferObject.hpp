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

#include "Enum.hpp"
#include "common/UntypedCowArray.hpp"

namespace my_gl {
     class BufferObject {
     public:

	  BufferObject(BufferTarget target,size_t size,void *data) noexcept;

	  void subData(ptrdiff_t offset,size_t size,void *data) noexcept;
     
     private:
	       BufferTarget _target;
	       UntypedCowArray _data;
     };
	
} /* my */

#endif /* end of include guard: BUFFER_OBJECT_HPP */
