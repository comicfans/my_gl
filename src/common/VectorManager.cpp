/*
 * =====================================================================================
 *
 *       Filename:  VectorManager.cpp
 *
 *    Description:  implementation of VectorManager
 *
 *        Version:  1.0
 *        Created:  2011-9-19 16:20:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "VectorManager.hpp"

#include <cassert>

#include "object/BufferObjectVectorProvider.hpp"
#include "ClientArrayVectorProvider.hpp"
#include "object/ArrayBufferObject.hpp"

namespace my_gl{
	
     VectorManager::VectorManager(BindState bindState)noexcept
	  :_bindedArrayBufferObject(nullptr),
	  _bindState(bindState),_vertexArrayEnabled(false)
     {}

     void VectorManager::bindArrayBufferObject
	  (const ArrayBufferObject *toBind)
     {
	  _bindedArrayBufferObject=toBind;
     }

     BindState VectorManager::getBindState() const noexcept
     {
	  return _bindState;
     }


     bool VectorManager::vertexArrayEnabled()const noexcept
     {return _vertexArrayEnabled;}

     void VectorManager::enableVertexArray(bool value)noexcept
     {
	  if(value!=_vertexArrayEnabled)
	  {
	       _vertexArrayEnabled=value;
	       clientStateChangeCallback(value);
	  }
     }

     void VectorManager::clientStateChangeCallback(bool value)
     {
     }

     VectorProvider& VectorManager::getProvider() noexcept
     {
	  return *_pImpl;
     }

     void VectorManager::vertexArrayChange(int componentSize,  
DataType type,  size_t stride,  const void *pointer)
     {

	  //if none zero array buffer object is binded to NORMAL_ARRAY_BINDING
	  //pointer is interperate as a offset in buffer object
	  if(_bindedArrayBufferObject)
	  {
	       _pImpl.reset(new BufferObjectVectorProvider
			 (*_bindedArrayBufferObject, reinterpret_cast<intptr_t>(pointer),
			  3,type,stride));
	  }
	  else
	  {
	       //should this a assert?
	       //OpenGL defined that if 
	       assert(_vertexArrayEnabled);
	  
	       _pImpl.reset(new ClientArrayVectorProvider
			 (pointer,3,type,stride));
	  }

     }
} /* my_gl */
