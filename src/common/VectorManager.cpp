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
	
     VectorManager::VectorManager(BindState bindState)
	  :_bindState(bindState),_bindedArrayBufferObject(nullptr)
     {}

     void VectorManager::bindArrayBufferObject
	  (const ArrayBufferObject *toBind)
     {
	  _bindedArrayBufferObject=toBind;
     }

     const ArrayBufferObject* VectorManager::getBindedBufferObject() const 
     {
	  return _bindState;
     }
} /* my_gl */
