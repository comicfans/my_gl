/*
 * =====================================================================================
 *
 *       Filename:  ArrayVectorProvider.hpp
 *
 *    Description:  abstract class to read vector from pointer
 *
 *        Version:  1.0
 *        Created:  2011-9-19 13:10:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ARRAY_VECTOR_PROVIDER_HPP

#define ARRAY_VECTOR_PROVIDER_HPP

#include "VectorProvider.hpp"


namespace my_gl {
	
     class ArrayVectorProvider :public VectorProvider{
     public:
	  ArrayVectorProvider(DataType type,int componentNumber,
		    size_t stride=0);

     protected:

	  Vector castRead(const void* pointer)const noexcept;

	  const DataType _dataType;
	  const int _componentNumber;
	  const size_t _blockSize;
     };
} /* my_gl */

#endif /* end of include guard: ARRAY_VECTOR_PROVIDER_HPP */
