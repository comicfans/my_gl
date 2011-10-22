/*
 * =====================================================================================
 *
 *       Filename:  IndexProvider.hpp
 *
 *    Description:  class to read Integer index from array
 *
 *        Version:  1.0
 *        Created:  2011-10-10 16:35:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef INDEX_PROVIDER_HPP

#define INDEX_PROVIDER_HPP

#include <cstddef>

#include "Enum.hpp"


namespace my_gl {

     class IndexProvider {
     public:

	  virtual ~IndexProvider();
	  virtual size_t getIndex(size_t index)const=0;
     
     };
	
} /* my_gl */

#endif /* end of include guard: INDEX_PROVIDER_HPP */
