/*
 * =====================================================================================
 *
 *       Filename:  AbstractVectorReader.cpp
 *
 *    Description:  implementation of AbstractVectorReader
 *
 *        Version:  1.0
 *        Created:  2011-9-16 23:39:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "AbstractVectorReader.hpp"
namespace my_gl {

     AbstractVectorReader::AbstractVectorReader
	  (const UntypedCowArray& array,size_t offset,
	       size_t blockBytes,size_t stride)
	  :_jumpBytes(blockBytes+stride),_array(array)
     {
	  _rawPointer=_array.get()+offset;
     }


     float const * AbstractVectorReader::next(size_t steps) noexcept
     {
	  _rawPointer+=_jumpBytes*steps;
	  return nextImpl();
     }


     int8_t const * AbstractVectorReader::rawPointer() const noexcept
     {
	  return _rawPointer;
     }

} /* my_gl */
