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
	
     Vec4Manager::Vec4Manager(GLenum bindState)
	  :_bindedArrayBufferObject(nullptr),
	  _bindState(bindState),_vertexArrayEnabled(false)
     {
	  assert(bindState==GL_VERTEX_ARRAY ||
		    bindState==GL_COLOR_ARRAY ||
		    bindState==GL_TEXTURE_COORD_ARRAY||
		    bindState==GL_NORMAL_ARRAY ||
		    "wrong vertex array attribute value");
     }

     Vec4Manager::~Vec4Manager()
     {}

     void Vec4Manager::bindArrayBufferObject
	  (const ArrayBufferObject *toBind)
     {
	  _bindedArrayBufferObject=toBind;
     }

     GLenum Vec4Manager::getBindState() const 
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
	       GLenum type,  size_t stride,  const void *pointer,bool normalize)
     {
	       //should this a assert?
	       //OpenGL defined that if 
	  assert(_vertexArrayEnabled);
	
	  //if none zero array buffer object is binded to NORMAL_ARRAY_BINDING
	  //pointer is interperate as a offset in buffer object
	  if(_bindedArrayBufferObject)
	  {
	       _pImpl.reset(new BufferObjectVec4Provider
			 (*_bindedArrayBufferObject, toInt(pointer),
			  componentSize,type,stride,normalize));
	  }
	  else
	  {
  
	       _pImpl.reset(new ClientArrayVec4Provider(pointer,
			      componentSize,type,stride,normalize));
	  }

     }


     Vec4 Vec4Manager::getValue(size_t index)
     {
	  return _pImpl->getValue(index);
     }
	
	  
} /* my_gl */
