/*
 * =====================================================================================
 *
 *       Filename:  AlignedValueVectorReader.hpp
 *
 *    Description:  fixed type vector reader
 *
 *        Version:  1.0
 *        Created:  2011-9-16 17:19:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ALIGNED_VALUE_VECTOR_READER_HPP

#define ALIGNED_VALUE_VECTOR_READER_HPP

#include <algorithm>

#include "AbstractVectorReader.hpp"

#include "Enum.hpp"

namespace my_gl {

     class AlignedValueVectorReader : public AbstractVectorReader {
     public:

     	AlignedValueVectorReader (const UntypedCowArray& array, 
		  DataType dataType, int componentNumber,
		  size_t offset,size_t stride);

	virtual float const * values()noexcept;

     protected:

	virtual float const *nextImpl()noexcept;


	template<typename T>
	  void copyToFloats()
	  {
	       void const *p=rawPointer();
	       T const *tp=static_cast<T const*>(p);
	       copy_n(tp,_componentNumber,_internalBuffer);
	  }

	const DataType _dataType;
	const int _componentNumber;
	float _internalBuffer[4];

     };

} /* my_gl */


#endif /* end of include guard: ALIGNED_VALUE_VECTOR_READER_HPP */
