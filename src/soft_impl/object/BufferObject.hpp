/*
 * =====================================================================================
 *
 *       Filename:  BufferObject.hpp
 *
 *    Description:  data respect to glBufferData/glTexImage2D
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
#include <memory>
#include <vector>


#include "Typedef.hpp"
#include "common/UntypedArray.hpp"

namespace my_gl {

     using std::unique_ptr;
     using std::vector;


     class BufferObject : noncopyable {
     public:

	  BufferObject(Name name) noexcept;

	  const void * getBufferPointer()const noexcept;

	  Name name()const noexcept;

     protected:

	  const Name _name;
	  unique_ptr<UntypedArray> _dataPointer;
     };
	
} /* my */

#endif /* end of include guard: BUFFER_OBJECT_HPP */
