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
#include "common/CheckEnum.hpp"
#include "common/PointerFunction.hpp"

namespace my_gl {

     ArrayIndexProvider::ArrayIndexProvider
	  (GLenum dataType,const void* indices)
	  :_dataType(dataType),_indices(indices)
	  {}

     ArrayIndexProvider::~ArrayIndexProvider()
     {}


     /** 
      * @brief cast raw array data to specified data type
      * 
      * @param index index of integer in -DataType- format
      * 
      * @return 
      */
     template<GLenum dataType>
	  
	  size_t ArrayIndexProvider::castRead
	  (size_t index)const
	  {

	       checkDataType(dataType);

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
	  if (_dataType==GL_UNSIGNED_BYTE)
	  {
	       return castRead<GL_UNSIGNED_BYTE>
		    (index);
	  }
	  else if(_dataType==GL_UNSIGNED_SHORT)
	  {
	       return castRead<GL_UNSIGNED_SHORT>
		    (index);
	  }
	  assert(false||"gles only support UNSIGNED_BYTE and UNSIGNED_SHORT");
     }
} /* my_gl */
