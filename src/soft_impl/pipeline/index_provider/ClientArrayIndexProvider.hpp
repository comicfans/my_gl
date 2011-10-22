/*
 * =====================================================================================
 *
 *       Filename:  ClientArrayIndexProvider.hpp
 *
 *    Description:  provide index from client array
 *
 *        Version:  1.0
 *        Created:  2011-10-22 20:57:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CLIENT_ARRAY_INDEX_PROVIDER_HPP

#define CLIENT_ARRAY_INDEX_PROVIDER_HPP

#include "ArrayIndexProvider.hpp"

namespace my_gl {

     class ClientArrayIndexProvider :public ArrayIndexProvider{
     public:

	  ClientArrayIndexProvider
	       (DataType dataType,const void* indices);

	  virtual ~ClientArrayIndexProvider ();

	  virtual size_t getIndex(size_t index)const;
     private:
	  const void *_indices;

     };
	
} /* my_gl */


#endif /* end of include guard: CLIENT_ARRAY_INDEX_PROVIDER_HPP */
