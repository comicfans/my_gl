/*
 * =====================================================================================
 *
 *       Filename:  ClientArrayIndexProvider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-22 21:04:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ClientArrayIndexProvider.hpp"

namespace my_gl {

     ClientArrayIndexProvider::ClientArrayIndexProvider
	  (DataType dataType,const void* indices)
	       :ArrayIndexProvider(dataType),_indices(indices)
	  {}

	  size_t ClientArrayIndexProvider::getIndex(size_t index)const
	  {
	       return ArrayIndexProvider::getIndex(_indices,index);
	  }
} /* my_gl */
