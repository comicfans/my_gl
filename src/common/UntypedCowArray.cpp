/*
 * =====================================================================================
 *
 *       Filename:  UntypedCowArray.cpp
 *
 *    Description:  implementation of UntypedCowArray
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

#include "UntypedCowArray.hpp"

#include <algorithm>
#include <utility>

using std::copy_n;
using std::move;

namespace my_gl {

     UntypedCowArray::UntypedCowArray
	  (size_t size,const void *p) 
	  :_size(size),_cowArray(new int8_t[size])
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

	       copy_n(temp, _size, _cowArray.get() );
	  }

     size_t UntypedCowArray::size()const noexcept
     {
	  return _size;
     }

     void UntypedCowArray::replace
	  (ptrdiff_t offset,  size_t size, const void *data)noexcept
	  {
	       //cow 
	       assert(offset>0);
	       assert(offset+size<=_size);

	       shared_array<int8_t> deepCopy(new int8_t[_size]);

	       copy_n(_cowArray.get(),_size,deepCopy.get() );

	       _cowArray.swap(deepCopy);	
	  }

     
} /* my_gl */
