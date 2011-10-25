/*
 * =====================================================================================
 *
 *       Filename:  ArrayIndexProvider.hpp
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

#ifndef ARRAY_INDEX_PROVIDER_HPP

#define ARRAY_INDEX_PROVIDER_HPP

#include "IndexProvider.hpp"


namespace my_gl {

     class ArrayIndexProvider :public IndexProvider{
     public:

	  ArrayIndexProvider
	       (DataType dataType,const void* indices);

	  virtual ~ArrayIndexProvider ();

	  virtual size_t getIndex(size_t index)const;
     private:

	  template<DataType dataType>
	       size_t castRead(size_t index)const;
	
	  const DataType _dataType;

	  const void *_indices;


     };
	
} /* my_gl */


#endif /* end of include guard: ARRAY_INDEX_PROVIDER_HPP */
