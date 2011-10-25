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
#include <climits>

#include "Enum.hpp"


namespace my_gl{

     using std::unique_ptr;
	
     class ArrayBufferObject;
     class ArrayIndexProvider;

     class ElementIndexManager{
     public:

	  void bindArrayBufferObject(const ArrayBufferObject& toBind);

	  //partial glDrawElements
	  const ArrayIndexProvider& elements(PrimitiveMode primitiveMode,
		    size_t count,DataType dataType,const void * indices,
		    size_t actualVertexNumber=INT_MAX);

     private:

	  const ArrayBufferObject *_bindedArrayBufferObjectPtr;

	  unique_ptr<ArrayIndexProvider> _indexProviderPtr;

     };
} /* my_gl */



#endif /* end of include guard: ELEMENT_INDEX_MANAGER_HPP */
