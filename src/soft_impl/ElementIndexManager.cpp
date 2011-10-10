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

namespace my_gl {

	
     void ElementIndexManager::bindArrayBufferObject
	  (const my_gl::ArrayBufferObject *toBind)
     {
	  _bindedArrayBufferObject=toBind;
     }

     const PrimitiveIndex& ElementIndexManager::elements
	  (PrimitiveMode primitiveMode,size_t count,
	   DataType dataType,const void * indices)
     {
	  if (_bindedArrayBufferObject)
	  {
	       const uint8_t *firstMemory= 
		    static_cast<const uint8_t*>(indices)+
		    reinterpret_cast<intptr_t>(indices);
		    
	       //TODO

	  }
	  else
	  {

	  }

     }


} /* my_gl */
