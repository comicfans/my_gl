/*
 * =====================================================================================
 *
 *       Filename:  UntypedArray.cpp
 *
 *    Description:  implementation of UntypedArray
 *
 *        Version:  1.0
 *        Created:  2011-9-13 20:23:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "UntypedArray.hpp"

#include <algorithm>
#include <utility>

using std::copy_n;
using std::move;

namespace my_gl {

     UntypedArray::UntypedArray
	  (size_t size,const void *p) 
	  :_size(size),_array(new int8_t[size])
	  {

	       const int8_t *temp=static_cast<const int8_t*>(p);

	       //see GL notes
	       //If data is NULL, a data store of the specified size 
	       //is still created, but its contents remain 
	       //uninitialized and thus undefined.
	       if (!p)
	       {
		    return;
	       }

	       copy_n(temp, _size, _array.get() );
	  }

     size_t UntypedArray::size()const 
     {
	  return _size;
     }

     void UntypedArray::replace
	  (ptrdiff_t offset,  size_t size, const void *data)
	  {
	       //cow 
	       assert(offset>0);
	       assert(offset+size<=_size);

	       int8_t const *p=static_cast<int8_t const*>(data);

	       copy_n(p,size,_array.get());
	  }

 	  template<typename T>
	       T const & UntypedArray::operator[](size_t idx)const 
	       {
		    assert(idx<_size/sizeof(T));

		    void  *p=_array.get();

		    return static_cast<T*>(p)[idx];
	       }

	  template<typename T>
	       T const * UntypedArray::get()const 
	       {
		    const void *p=_array.get();

		    return static_cast<const T*>(p);
	       }

	  template<typename T>
	       T * UntypedArray::get() 
	       { 
		    void *p=_array.get();
		    return static_cast<T*>(p);
	       }

	  template int8_t const& UntypedArray::
	       operator[]<int8_t>(size_t)const;
	  template int8_t const * UntypedArray::
	       get<int8_t>()const;
	  template int8_t * UntypedArray::
	       get<int8_t>();

    	  template uint8_t const& UntypedArray::
	       operator[]<uint8_t>(size_t)const;
	  template uint8_t const * UntypedArray::
	       get<uint8_t>()const;
	  template uint8_t * UntypedArray::
	       get<uint8_t>();
    
	  template int16_t const& UntypedArray::
	       operator[]<int16_t>(size_t)const;
	  template int16_t const * UntypedArray::
	       get<int16_t>()const;
	  template int16_t * UntypedArray::
	       get<int16_t>();

    	  template uint16_t const& UntypedArray::
	       operator[]<uint16_t>(size_t)const;
	  template uint16_t const * UntypedArray::
	       get<uint16_t>()const;
	  template uint16_t * UntypedArray::
	       get<uint16_t>();
    
	  template int32_t const& UntypedArray::
	       operator[]<int32_t>(size_t)const;
	  template int32_t const * UntypedArray::
	       get<int32_t>()const;
	  template int32_t * UntypedArray::
	       get<int32_t>();

    	  template uint32_t const& UntypedArray::
	       operator[]<uint32_t>(size_t)const;
	  template uint32_t const * UntypedArray::
	       get<uint32_t>()const;
	  template uint32_t * UntypedArray::
	       get<uint32_t>();
    
    	  template float const& UntypedArray::
	       operator[]<float>(size_t)const;
	  template float const * UntypedArray::
	       get<float>()const;
	  template float* UntypedArray::
	       get<float>();
 
} /* my_gl */
