/*
 * =====================================================================================
 *
 *       Filename:  IndirectOrderIndexProvider.cpp
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

#include "IndirectOrderIndexProvider.hpp"

#include "common/TypeTraits.hpp"

#include <cassert>

namespace my_gl {
	
     IndirectOrderIndexProvider::IndirectOrderIndexProvider
	  (DataType dataType,const void *indices)
	  :_dataType(dataType),
	  _indices(indices)
	  {
	       assert(dataType==DataType::UNSIGNED_BYTE || 
			 dataType==DataType::UNSIGNED_SHORT);
	  }

	size_t IndirectOrderIndexProvider::getIndex(size_t index)const
	{
	     if (_dataType==DataType::UNSIGNED_BYTE)
	     {
		  return castRead<DataType::UNSIGNED_BYTE>(index);
	     }
	     else
	     {
		  return castRead<DataType::UNSIGNED_SHORT>(index);
	     }
	}

	template<DataType dataType>
	     size_t IndirectOrderIndexProvider::castRead(size_t index) const
	     {
		  const uint8_t * pointer=
		       static_cast<const uint8_t*>(_indices);

		  auto *thisValuePointer=pointer+
		       DataTypeTraits<dataType>::size*index;

		       
		  typedef typename DataTypeTraits<dataType>::underlineType
		       underlineType;

		  const underlineType *p=static_cast<const underlineType*>(
			    (const void*)thisValuePointer);

		  return *p;
	     }
} /* my_gl */
