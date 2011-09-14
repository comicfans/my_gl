/*
 * =====================================================================================
 *
 *       Filename:  UntypedScopedArray.hpp
 *
 *    Description:  to impl void * array RAII
 *
 *        Version:  1.0
 *        Created:  2011-9-13 20:17:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef UNTYPED_SCOPED_ARRAY_HPP

#define UNTYPED_SCOPED_ARRAY_HPP

#include <cstddef>
#include <cassert>
#include <cstdint>

namespace my_gl {

     using std::int8_t;
     class UntypedScopedArray {
     public:
	  explicit UntypedScopedArray(void *p,size_t size);

	  void operator=(const UntypedScopedArray& rhs)=delete;

	  void replace(ptrdiff_t offset,size_t size,void *data)noexcept;

	  size_t size()const noexcept;

	  template<typename T>
	       T & operator[](size_t idx)const noexcept
	       {
		    assert(idx<_size/sizeof(T));
		    return static_cast<T*>(_pointer)[idx];
	       }
	  template<typename T>
	       T * get()const noexcept
	       {
		    return static_cast<T*>(_pointer);
	       }

	  ~UntypedScopedArray() noexcept;
     private:
	  int8_t *_pointer;
	  size_t _size;
     };
	
} /* my */

#endif /* end of include guard: UNTYPED_SCOPED_ARRAY_HPP */
