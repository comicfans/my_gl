/*
 * =====================================================================================
 *
 *       Filename:  AlignedValueVectorReader.cpp
 *
 *    Description:  template instantiation of AlignedValueVectorReader
 *
 *        Version:  1.0
 *        Created:  2011-9-16 22:01:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "AlignedValueVectorReader.hpp"

#include <algorithm>

namespace my_gl {

     using std::copy_n;

     int DATA_TYPE_SIZE[]={1,2,4,4};

     AlignedValueVectorReader::AlignedValueVectorReader 
	  (const UntypedCowArray& array, DataType dataType,
	   int componentNumber,size_t offset,size_t stride):
	       AbstractVectorReader(array,offset,
			 DATA_TYPE_SIZE[int(dataType)]*componentNumber
			 ,stride),_dataType(dataType),
	       _componentNumber(componentNumber)
     {
	  nextImpl();
     }

     float const * AlignedValueVectorReader::values()noexcept
     {
	  return _internalBuffer;
     }

     float const * AlignedValueVectorReader::nextImpl()noexcept
     {
	  switch(_dataType)
	  {
	       case DataType::BYTE:
		    {copyToFloats<int8_t>(); break;}
	       case DataType::SHORT:
		    {copyToFloats<int16_t>();break;}
	       case DataType::FIXED:
		    {copyToFloats<int32_t>();break;}
	       case DataType::FLOAT:
		    {copyToFloats<float>();break;}
	  }
	  return _internalBuffer;
     }

} /* my_gl */
