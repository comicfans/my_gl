/*
 * =====================================================================================
 *
 *       Filename:  ArrayVectorProvider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-19 13:18:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ArrayVectorProvider.hpp"

#include <cassert>

namespace my_gl {

     static size_t calcBlockSize(DataType type,int componentNumber,
	       size_t stride)
     {
	  return DATA_TYPE_UNDERLINE_SIZE[int(type)]*componentNumber+stride;
     }

     ArrayVectorProvider::ArrayVectorProvider
	  (DataType type,int componentNumber,size_t stride)
	  :_dataType(type),_componentNumber(componentNumber),
	  _blockSize(calcBlockSize(type,componentNumber,stride))
     {}



     Vector ArrayVectorProvider::castRead
	  (const void* pointer,bool normalize)const noexcept
	  {
	       switch(_dataType)
	       {
		    case DataType::BYTE:
			 {return this->copyToFloats<DataType::BYTE>
			      (pointer,normalize);}
		    case DataType::UNSIGNED_BYTE:
			      {return copyToFloats<DataType::UNSIGNED_BYTE>
			      (pointer,normalize);}
		    case DataType::SHORT:
			 {return copyToFloats<DataType::SHORT>
			      (pointer,normalize);}
		    case DataType::UNSIGNED_SHORT:
			 {return copyToFloats<DataType::UNSIGNED_SHORT>
			      (pointer,normalize);}
		    case DataType::FIXED:
			 {return copyToFloats<DataType::FIXED>
			      (pointer,normalize);}
		    case DataType::FLOAT:
			      {return copyToFloats<DataType::FLOAT>
				   (pointer,normalize);}
		    default:
				   {assert(false);}

	       }
	  }

} /* my_gl */
