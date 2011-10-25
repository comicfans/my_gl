/*
 * =====================================================================================
 *
 *       Filename:  ElementIndexManager.cpp
 *
 *    Description:  implementation of ElementIndexManager
 *
 *        Version:  1.0
 *        Created:  2011-10-10 12:46:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ElementIndexManager.hpp"

#include <cstdint>

#include "pipeline/index_provider/ArrayIndexProvider.hpp"
#include "object/ArrayBufferObject.hpp"
#include "common/PointerFunction.hpp"

namespace my_gl {

	
     void ElementIndexManager::bindArrayBufferObject
	  (const ArrayBufferObject& toBind)
     {
	  _bindedArrayBufferObjectPtr=&toBind;
     }
	  const ArrayIndexProvider& ElementIndexManager::
	       elements(PrimitiveMode primitiveMode,
		    size_t count,DataType dataType,const void * indices,
		    size_t actualVertexNumber)
     {

	  const void *actualIndices=indices;
	  if (_bindedArrayBufferObjectPtr)
	  {
	       //if none zero array buffer object is binded to
	       //ELEMENT_ARRAY_BUFFER, indices is treated as 
	       //offset of buffer object in machine units
	       actualIndices=add(
			 _bindedArrayBufferObjectPtr->getBufferPointer(),
			 toInt(indices));
	  }

	  _indexProviderPtr.reset(new 
		    ArrayIndexProvider( 
			 dataType,actualIndices));

	  return *_indexProviderPtr;
     }

} /* my_gl */
