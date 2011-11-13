/*
 * =====================================================================================
 *
 *       Filename:  ArrayVec4Provider.cpp
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

#include "ArrayVec4Provider.hpp"

#include <cassert>

#include "PointerFunction.hpp"

namespace my_gl {

     static size_t calcBlockSize(DataType type,int componentNumber,
	       size_t stride)
     {
	  return stride? stride :
	  DATA_TYPE_UNDERLINE_SIZE[int(type)]*componentNumber;
     }

     ArrayVec4Provider::ArrayVec4Provider
	  (int componentNumber,DataType type,size_t stride,bool normalize)
	  :_dataType(type),_componentNumber(componentNumber),
	  _blockSize(calcBlockSize(type,componentNumber,stride)),
	  _normalize(normalize)
     {}

	  template<DataType dataType>
	       Vec4 ArrayVec4Provider::copyToFloats(const void* p)
	       const 
	       {
		    typedef typename 
			 DataTypeTraits<dataType>::underlineType type;
		    type const *tp=static_cast<type const*>(p);
		    Vec4 ret;
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



     Vec4 ArrayVec4Provider::castRead
	  (const void* pointer,size_t index)const 
	  {
	       const void* actualPointer=
		    add(pointer,index*_blockSize);

	       switch(_dataType)
	       {
		    case DataType::BYTE:
			 {return this->copyToFloats<DataType::BYTE>
			      (actualPointer);}
		    case DataType::UNSIGNED_BYTE:
			      {return copyToFloats<DataType::UNSIGNED_BYTE>
			      (actualPointer);}
		    case DataType::SHORT:
			 {return copyToFloats<DataType::SHORT>
			      (actualPointer);}
		    case DataType::UNSIGNED_SHORT:
			 {return copyToFloats<DataType::UNSIGNED_SHORT>
			      (actualPointer);}
		    case DataType::FIXED:
			 {return copyToFloats<DataType::FIXED>
			      (actualPointer);}
		    case DataType::FLOAT:
			      {return copyToFloats<DataType::FLOAT>
				   (actualPointer);}
		    default:
				   //SHOULD NOT here
				   {assert(false);}

	       }
	  }

} /* my_gl */
