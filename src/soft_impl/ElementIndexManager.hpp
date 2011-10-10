/*
 * =====================================================================================
 *
 *       Filename:  ElementIndexManager.hpp
 *
 *    Description:  manage glDrawElements 
 *
 *        Version:  1.0
 *        Created:  2011-10-10 12:30:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ELEMENT_INDEX_MANAGER_HPP

#define ELEMENT_INDEX_MANAGER_HPP

#include <memory>

#include "Enum.hpp"


namespace my_gl{

     using std::unique_ptr;
	
     class ArrayBufferObject;
     class PrimitiveIndex;

     class ElementIndexManager{
     public:

	  void bindArrayBufferObject(const ArrayBufferObject* toBind);

	  //partial glDrawElements
	  const PrimitiveIndex& elements(PrimitiveMode primitiveMode,
		    size_t count,DataType dataType,const void * indices);

     private:

	  unique_ptr<PrimitiveIndex> _primitiveIndexPointer;

	  const ArrayBufferObject *_bindedArrayBufferObject;

	  const void *_clientIndex;

     };
} /* my_gl */



#endif /* end of include guard: ELEMENT_INDEX_MANAGER_HPP */
