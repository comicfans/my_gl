/*
 * =====================================================================================
 *
 *       Filename:  AbstractVectorReader.hpp
 *
 *    Description:  template class of VectorReader
 *
 *        Version:  1.0
 *        Created:  2011-9-16 16:09:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ABSTRACT_VECTOR_READER_HPP

#define ABSTRACT_VECTOR_READER_HPP

#include "UntypedCowArray.hpp"

namespace my_gl {

	  class AbstractVectorReader {
	       public:
		    AbstractVectorReader(const UntypedCowArray& array,size_t offset,
			      size_t blockBytes,size_t stride);

		    virtual float const* values() noexcept=0;

		    float const* next(size_t steps=1) noexcept;

	       protected:

		    virtual float const *nextImpl()noexcept=0;

		    int8_t const * rawPointer() const noexcept;

	       private:

		    const size_t _jumpBytes;

		    UntypedCowArray _array;

		    int8_t const *_rawPointer;

	  };

} /* my_gl */



#endif /* end of include guard: ABSTRACT_VECTOR_READER_HPP */
