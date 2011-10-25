/*
 * =====================================================================================
 *
 *       Filename:  ArrayIndexProvider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-22 21:04:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ArrayIndexProvider.hpp"

#include <cassert>

#include "common/TypeTraits.hpp"
#include "common/PointerFunction.hpp"

namespace my_gl {

     ArrayIndexProvider::ArrayIndexProvider
	  (DataType dataType,const void* indices)
	  :_dataType(dataType),_indices(indices)
	  {}

     ArrayIndexProvider::~ArrayIndexProvider()
     {}

     template<DataType dataType>
	  size_t ArrayIndexProvider::castRead
	  (size_t index)const
	  {

	       auto *thisValuePointer=
		    add(_indices,DataTypeTraits<dataType>::size*index);

	       typedef typename DataTypeTraits<dataType>::underlineType
		    underlineType;

	       const underlineType *p=static_cast<const underlineType*>
		    ((const void*)thisValuePointer);

	       return *p;
	  }

     size_t ArrayIndexProvider::getIndex(size_t index)const
     {
	  //gles only support UNSIGNED_BYTE and UNSIGNED_SHORT
	  if (_dataType==DataType::UNSIGNED_BYTE)
	  {
	       return castRead<DataType::UNSIGNED_BYTE>
		    (index);
	  }
	  else if(_dataType==DataType::UNSIGNED_SHORT)
	  {
	       return castRead<DataType::UNSIGNED_SHORT>
		    (index);
	  }
	  assert(false);
     }
} /* my_gl */
