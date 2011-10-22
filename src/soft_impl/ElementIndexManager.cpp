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

#include "pipeline/PrimitiveIndex.hpp"
#include "object/ArrayBufferObject.hpp"
#include "pipeline/index_provider/BufferObjectIndexProvider.hpp"
#include "pipeline/index_provider/ClientArrayIndexProvider.hpp"
#include "common/PointerFunction.hpp"

namespace my_gl {

	
     void ElementIndexManager::bindArrayBufferObject
	  (const my_gl::ArrayBufferObject *toBind)
     {
	  _bindedArrayBufferObject=toBind;
     }

     const PrimitiveIndex& ElementIndexManager::elements
	  (PrimitiveMode primitiveMode,size_t count,
	   DataType dataType,const void * indices,
	   size_t actualVertexNumber)
     {
	  if (_bindedArrayBufferObject)
	  {
	       _primitiveIndexPtr.reset
		    (new PrimitiveIndex
		    (primitiveMode,count,actualVertexNumber,
		     BufferObjectIndexProvider
		     (dataType,*_bindedArrayBufferObject,toInt(indices))));

	  }
	  else
	  {
	       _primitiveIndexPtr.reset(new PrimitiveIndex
		    (primitiveMode,count,actualVertexNumber,
		     ClientArrayIndexProvider(dataType,indices)));

	  }
	  return *_primitiveIndexPtr;
     }

} /* my_gl */
