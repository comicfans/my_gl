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
#include <memory>

#include <boost/noncopyable.hpp>

namespace my_gl {

     using std::unique_ptr;
     using boost::noncopyable;

     class UntypedArray:boost::noncopyable{
     public:
	  explicit UntypedArray(size_t size,const void *p);

	  void replace(ptrdiff_t offset,size_t size,
		    const void *data);

	  size_t size()const ;

	  template<typename T>
	       T const & operator[](size_t idx)const ;

	  template<typename T=int8_t>
	       T const * get()const ;

	  template<typename T=int8_t>
	       T * get() ;

     private:

	  const size_t _size;
	  unique_ptr<int8_t[]> _array;

     };

	
} /* my_gl */

#endif /* end of include guard: UNTYPED_ARRAY_HPP */
