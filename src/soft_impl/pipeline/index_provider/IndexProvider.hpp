/*
 * =====================================================================================
 *
 *       Filename:  IndexProvider.hpp
 *
 *    Description:  class to escape index fetching ,as "index array"
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
	  /** 
	   * @brief fetch a integer at offset index
	   * 
	   * @param index offset index
	   * 
	   * @return index integer at index of index(confused?)
	   */
	  virtual size_t getIndex(size_t index)const=0;
     
     };
	
} /* my_gl */

#endif /* end of include guard: INDEX_PROVIDER_HPP */
