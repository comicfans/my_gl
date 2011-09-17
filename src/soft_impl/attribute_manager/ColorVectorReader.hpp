/*
 * =====================================================================================
 *
 *       Filename:  ColorVectorReader.hpp
 *
 *    Description:  read color vector as normalized/unnormalized values
 *
 *        Version:  1.0
 *        Created:  2011-9-17 12:30:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef COLOR_VECTOR_READER_HPP

#define COLOR_VECTOR_READER_HPP

#include "AlignedValueVectorReader.hpp"

namespace my_gl {
     class ColorVectorReader :public AlignedValueVectorReader{
     public:
     	ColorVectorReader (const UntypedCowArray& array, 
		  DataType dataType, int componentNumber,
		  size_t offset,size_t stride);

     protected:

	virtual float const * nextImpl()noexcept;


     };
	
} /* my_gl */


#endif /* end of include guard: COLOR_VECTOR_READER_HPP */
