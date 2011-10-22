/*
 * =====================================================================================
 *
 *       Filename:  ArrayIndexProvider.hpp
 *
 *    Description:  read index value from a predefined index
 *
 *        Version:  1.0
 *        Created:  2011-10-10 16:47:31
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

	  ArrayIndexProvider(DataType dataType);

	  virtual ~ArrayIndexProvider ();

     protected:

	size_t getIndex(const void *pointer,size_t index)const;

	const DataType _dataType;

	template<DataType dataType>
	     static size_t castRead(const void *pointer,size_t index);
     };
	
} /* my_gl */


#endif /* end of include guard: ARRAY_INDEX_PROVIDER_HPP */
