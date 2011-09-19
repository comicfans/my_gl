/*
 * =====================================================================================
 *
 *       Filename:  UntypedArray.hpp
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

#ifndef UNTYPED_ARRAY_HPP

#define UNTYPED_ARRAY_HPP 

#include <cstddef>
#include <cassert>
#include <cstdint>

#include <boost/scoped_array.hpp>
#include <boost/noncopyable.hpp>

namespace my_gl {

     using std::int8_t;
     using boost::scoped_array;
     using boost::noncopyable;

     class UntypedArray:boost::noncopyable{
     public:
	  explicit UntypedArray(size_t size,const void *p);

	  void replace(ptrdiff_t offset,size_t size,
		    const void *data)noexcept;

	  size_t size()const noexcept;

	  template<typename T>
	       T const & operator[](size_t idx)const noexcept
	       {
		    assert(idx<_size/sizeof(T));
		    return static_cast<T*>(_array.get())[idx];
	       }
	  template<typename T=int8_t>
	       T const * get()const noexcept
	       {
		    void* p=_array.get();
		    return static_cast<T*>(p);
	       }
	  template<typename T=int8_t>
	       T * get() noexcept
	       { 
		    void *p=_array.get();
		    return static_cast<T*>(p);
	       }

     private:

	  const size_t _size;
	  scoped_array<int8_t> _array;

     };

	
} /* my_gl */

#endif /* end of include guard: UNTYPED_ARRAY_HPP */
