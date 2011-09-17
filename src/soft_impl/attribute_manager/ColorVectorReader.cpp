/*
 * =====================================================================================
 *
 *       Filename:  ColorVectorReader.cpp
 *
 *    Description:  implementation of ColorVectorReader
 *
 *        Version:  1.0
 *        Created:  2011-9-17 12:57:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "ColorVectorReader.hpp"
namespace my_gl{

     ColorVectorReader::ColorVectorReader (const UntypedCowArray& array, 
		  DataType dataType, int componentNumber,
		  size_t offset,size_t stride)
	  :AlignedValueVectorReader(array,dataType,componentNumber,offset,stride)
     {}


	float const * ColorVectorReader::nextImpl()noexcept
	{
	     AlignedValueVectorReader::nextImpl();

	     if (_dataType!=DataType::FLOAT)
	     {
		  for (int i=0; i<_componentNumber; ++i)
		  {
		       _internalBuffer[i]/=255;
		  }
	     }
	     
	     return _internalBuffer;
	}
	
} /* my_gl */

