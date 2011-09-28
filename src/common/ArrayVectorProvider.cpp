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
	  (int componentNumber,DataType type,size_t stride,bool normalize)
	  :_dataType(type),_componentNumber(componentNumber),
	  _blockSize(calcBlockSize(type,componentNumber,stride)),
	  _normalize(normalize)
     {}

	  template<DataType dataType>
	       Vector ArrayVectorProvider::copyToFloats(const void* p)
	       const noexcept
	       {
		    typedef typename 
			 DataTypeTraits<dataType>::underlineType type;
		    type const *tp=static_cast<type const*>(p);
		    Vector ret;
		    copy_n(tp,_componentNumber,ret.values());

		    if (_normalize)
		    {
			 for (int i=0; i<_componentNumber; ++i)
			 {
			      ret(i)=DataTypeTraits<dataType>::
				   normalize(ret(i));
			 }
		    }

		    return ret;
	       }



     Vector ArrayVectorProvider::castRead
	  (const void* pointer)const noexcept
	  {
	       switch(_dataType)
	       {
		    case DataType::BYTE:
			 {return this->copyToFloats<DataType::BYTE>
			      (pointer);}
		    case DataType::UNSIGNED_BYTE:
			      {return copyToFloats<DataType::UNSIGNED_BYTE>
			      (pointer);}
		    case DataType::SHORT:
			 {return copyToFloats<DataType::SHORT>
			      (pointer);}
		    case DataType::UNSIGNED_SHORT:
			 {return copyToFloats<DataType::UNSIGNED_SHORT>
			      (pointer);}
		    case DataType::FIXED:
			 {return copyToFloats<DataType::FIXED>
			      (pointer);}
		    case DataType::FLOAT:
			      {return copyToFloats<DataType::FLOAT>
				   (pointer);}
		    default:
				   {assert(false);}

	       }
	  }

} /* my_gl */
