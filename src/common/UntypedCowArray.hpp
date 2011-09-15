/*
 * =====================================================================================
 *
 *       Filename:  UntypedCowArray.hpp
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

#ifndef UNTYPED_COW_ARRAY_HPP

#define UNTYPED_COW_ARRAY_HPP 

#include <cstddef>
#include <cassert>
#include <cstdint>

#include <boost/shared_array.hpp>

namespace my_gl {

     using std::int8_t;
     using boost::shared_array;

     class UntypedCowArray{
     public:
	  explicit UntypedCowArray(size_t size,const void *p);

	  void replace(ptrdiff_t offset,size_t size,
		    const void *data)noexcept;

	  size_t size()const noexcept;

	  template<typename T>
	       T const & operator[](size_t idx)const noexcept
	       {
		    assert(idx<_size/sizeof(T));
		    return static_cast<T*>(_cowArray.get())[idx];
	       }
	  template<typename T=int8_t>
	       T const * get()const noexcept
	       {
		    return static_cast<T*>(_cowArray.get());
	       }

     private:

	  const size_t _size;
	  shared_array<int8_t> _cowArray;

     };
	
} /* my */

#endif /* end of include guard: UNTYPED_COW_ARRAY_HPP */
