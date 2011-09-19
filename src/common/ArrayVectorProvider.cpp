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
namespace my_gl {

     const int DATA_TYPE_SIZE={1,2,4,4};
     static size_t calcBlockSize(DataType type,int componentNumber,
	       size_t stride)
     {
	  return DATA_TYPE_SIZE[int(type)]*componentNumber+stride;
     }

     ArrayVectorProvider::ArrayVectorProvider
	  (DataType type,int componentNumber,size_t stride)
	  :_dataType(type),_componentNumber(componentNumber),
	  _stride(stride),
	  _blockSize(calcBlockSize(type,componentNumber,stride))
     {}

     template<typename T>
	  void copyToFloats(const void* p)
	  {
	       T const *tp=static_cast<T const*>(p);
	       copy_n(tp,_componentNumber,_internalBuffer);
	  }


     Vector ArrayVectorProvider::castRead
	  (const void* pointer)const noexcept
	  {
	       switch(_dataType)
	       {
		    case DataType::BYTE:
			 {copyToFloats<int8_t>(pointer); break;}
		    case DataType::SHORT:
			 {copyToFloats<int16_t>(pointer);break;}
		    case DataType::FIXED:
			 {copyToFloats<int32_t>(pointer);break;}
		    case DataType::FLOAT:
			 {copyToFloats<float>(pointer);break;}
	       }
	  }

} /* my_gl */
