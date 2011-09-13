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

namespace my_gl {

     class UntypedScopedArray {
     public:
	  explicit UntypedScopedArray(void *p)noexcept;

	  template<typename T>
	       T & operator[](size_t idx)const noexcept
	       {
	       return static_cast<T*>(_pointer)[idx];
	       }
	  template<typename T>
	       T * get()const noexcept
	       {
		    return static_cast<T*>(_pointer);
	       }

	  ~UntypedScopedArray() noexcept;
     private:
	  void * _pointer;
     };
	
} /* my */

#endif /* end of include guard: UNTYPED_SCOPED_ARRAY_HPP */
