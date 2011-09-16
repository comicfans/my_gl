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

#include <boost/noncopyable.hpp>

#include "Typedef.hpp"
#include "common/UntypedCowArray.hpp"

namespace my_gl {

     using std::unique_ptr;
     using std::vector;

     using boost::noncopyable;

     class BufferObject : noncopyable {
     public:

	  BufferObject(Name name) noexcept;

	  void bindData(size_t size,const void *data);

	  void subData(ptrdiff_t offset,size_t size,const void *data) noexcept;

	  UntypedCowArray copyArray()const noexcept;

	  Name name()const noexcept;

     private:

	  const Name _name;
	  unique_ptr<UntypedCowArray> _dataPointer;
     };
	
} /* my */

#endif /* end of include guard: BUFFER_OBJECT_HPP */
