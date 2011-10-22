/*
 * =====================================================================================
 *
 *       Filename:  Vec4Manager.cpp
 *
 *    Description:  implementation of Vec4Manager
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

#include "Vec4Manager.hpp"

#include <cassert>

#include "BufferObjectVec4Provider.hpp"
#include "ClientArrayVec4Provider.hpp"
#include "object/ArrayBufferObject.hpp"
#include "common/PointerFunction.hpp"

namespace my_gl{
	
     Vec4Manager::Vec4Manager(BindState bindState)
	  :_bindedArrayBufferObject(nullptr),
	  _bindState(bindState),_vertexArrayEnabled(false)
     {}

     Vec4Manager::~Vec4Manager()
     {}

     void Vec4Manager::bindArrayBufferObject
	  (const ArrayBufferObject *toBind)
     {
	  _bindedArrayBufferObject=toBind;
     }

     BindState Vec4Manager::getBindState() const 
     {
	  return _bindState;
     }


     bool Vec4Manager::vertexArrayEnabled()const 
     {return _vertexArrayEnabled;}

     void Vec4Manager::enableVertexArray(bool value)
     {
	  if(value!=_vertexArrayEnabled)
	  {
	       _vertexArrayEnabled=value;
	       clientStateChangeCallback(value);
	  }
     }

     void Vec4Manager::clientStateChangeCallback(bool value)
     {
     }

     void Vec4Manager::vertexArrayChange(int componentSize,  
DataType type,  size_t stride,  const void *pointer)
     {

	  //if none zero array buffer object is binded to NORMAL_ARRAY_BINDING
	  //pointer is interperate as a offset in buffer object
	  if(_bindedArrayBufferObject)
	  {
	       _pImpl.reset(new BufferObjectVec4Provider
			 (*_bindedArrayBufferObject, toInt(pointer),
			  3,type,stride));
	  }
	  else
	  {
	       //should this a assert?
	       //OpenGL defined that if 
	       assert(_vertexArrayEnabled);
	  
	       _pImpl.reset(new ClientArrayVec4Provider
			 (pointer,3,type,stride));
	  }

     }

	 
     Vec4 Vec4Manager::value()
     {
	  return _pImpl->value();
     }
	
	  
     void Vec4Manager::next(size_t steps)
     {
	  _pImpl->next(steps);
     }
} /* my_gl */
