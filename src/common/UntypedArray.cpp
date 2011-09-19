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

     size_t UntypedArray::size()const noexcept
     {
	  return _size;
     }

     void UntypedArray::replace
	  (ptrdiff_t offset,  size_t size, const void *data)noexcept
	  {
	       //cow 
	       assert(offset>0);
	       assert(offset+size<=_size);

	       int8_t const *p=static_cast<int8_t const*>(data);

	       copy_n(p,size,_array.get());
	  }

     
} /* my_gl */
