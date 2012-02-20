/*
 * =====================================================================================
 *
 *       Filename:  ElementIndexManager.hpp
 *
 *    Description:  manage glDrawElements indirect index 
 *    drawing command
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

	  /** 
	   * @brief call glBindBuffer with 
	   * target=GL_ELEMENT_ARRAY_BUFFER
	   * will bind corresponding buffer object
	   * to ELEMENT_ARRAY_BUFFER_BIND
	   * this array buffer object will be used
	   * when glBufferData with target=GL_ELEMENT_ARRAY_BUFFER
	   * is called.
	   * element index will be also fected from this 
	   * buffer object
	   *
	   * if non null ArrayBufferObject is binded,
	   * indices in glDrawElements will be interpret
	   * as offset of basic machine unit in buffer object
	   *
	   * if call glBindBuffer with GL_ELEMENT_ARRAY_BUFFER,0
	   * nullptr will be binded to this,
	   * indices in glDrawElements will be interpret
	   * as client array pointer of draw index
	   * 
	   * @param toBind
	   */
	  void bindArrayBufferObject(const ArrayBufferObject* toBind);

	  //partial glDrawElements
	  const ArrayIndexProvider& elements(GLenum primitiveMode,
		    size_t count,GLenum dataType,const void * indices,
		    size_t actualVertexNumber=INT_MAX);

     private:

	  const ArrayBufferObject *_bindedArrayBufferObjectPtr;

	  unique_ptr<ArrayIndexProvider> _indexProviderPtr;

     };
} /* my_gl */



#endif /* end of include guard: ELEMENT_INDEX_MANAGER_HPP */
