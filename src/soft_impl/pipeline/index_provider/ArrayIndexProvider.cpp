/*
 * =====================================================================================
 *
 *       Filename:  ArrayIndexProvider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-10 16:54:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ArrayIndexProvider.hpp"

#include "common/TypeTraits.hpp"
#include "common/PointerFunction.hpp"

#include <cassert>

namespace my_gl {
	
     ArrayIndexProvider::~ArrayIndexProvider (){}

     ArrayIndexProvider::ArrayIndexProvider
	  (DataType dataType)
	  :_dataType(dataType)
	  {
	       assert(dataType==DataType::UNSIGNED_BYTE || 
			 dataType==DataType::UNSIGNED_SHORT);
	  }

	size_t ArrayIndexProvider::getIndex(const void* pointer,size_t index)const
	{
	     if (_dataType==DataType::UNSIGNED_BYTE)
	     {
		  return castRead<DataType::UNSIGNED_BYTE>(pointer,index);
	     }
	     else
	     {
		  return castRead<DataType::UNSIGNED_SHORT>(pointer,index);
	     }
	}

	template<DataType dataType>
	     size_t ArrayIndexProvider::castRead(const void* indices,size_t index)
	     {

		  auto *thisValuePointer=
		       add(indices,DataTypeTraits<dataType>::size*index);
		       
		  typedef typename DataTypeTraits<dataType>::underlineType
		       underlineType;

		  const underlineType *p=static_cast<const underlineType*>(
			    (const void*)thisValuePointer);

		  return *p;
	     }
} /* my_gl */
