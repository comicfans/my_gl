/*
 * =====================================================================================
 *
 *       Filename:  BufferObject.cpp
 *
 *    Description:  implementation of BufferObject
 *
 *        Version:  1.0
 *        Created:  2011-9-13 20:31:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "BufferObject.hpp"
#include "common/UntypedArray.hpp"

namespace my_gl {


     BufferObject::BufferObject(Name name)
	   :_name(name)
     {}

     Name BufferObject::name()const 
     {return _name;}

	  template<typename T>
	  const T * BufferObject::getBufferPointer()const 
	  {
	       return _dataPointer->get<T>();
	  }

	  template 
	       const float* BufferObject::
	       getBufferPointer<float>()const;

	  template 
	       const int8_t* BufferObject::
	       getBufferPointer<int8_t>()const;
	
	  template 
	       const uint8_t* BufferObject::
	       getBufferPointer<uint8_t>()const;

	  template 
	       const int16_t* BufferObject::
	       getBufferPointer<int16_t>()const;

	  template 
	       const uint16_t* BufferObject::
	       getBufferPointer<uint16_t>()const;

	  template 
	       const int32_t* BufferObject::
	       getBufferPointer<int32_t>()const;

	  template 
	       const uint32_t* BufferObject::
	       getBufferPointer<uint32_t>()const;
} /* my_gl */
