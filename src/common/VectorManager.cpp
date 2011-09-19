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

namespace my_gl{
	
     VectorManager::VectorManager(BindState bindState)noexcept
	  :_bindState(bindState),_bindedArrayBufferObject(nullptr)
     {}

     void VectorManager::bindArrayBufferObject
	  (const ArrayBufferObject *toBind)
     {
	  _bindedArrayBufferObject=toBind;
     }

     BindState VectorManager::getBindState()
     {
	  return _bindState;
     }

     const ArrayBufferObject* VectorManager::getBindedBufferObject() 
	  const noexcept
     {
	  return _bindedArrayBufferObject;
     }
} /* my_gl */
