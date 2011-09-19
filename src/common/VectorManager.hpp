/*
 * =====================================================================================
 *
 *       Filename:  VectorManager.hpp
 *
 *    Description:  manager object to provide a VectorProvider
 *
 *        Version:  1.0
 *        Created:  2011-9-19 15:55:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VECTOR_MANAGER_HPP

#define VECTOR_MANAGER_HPP

#include "Enum.hpp"

namespace my_gl {

     class VectorProvider;
     class ArrayBufferObject;
     class VectorManager {
     public:

	  VectorManager(BindState bindState)noexcept;

	  virtual VectorProvider& getProvider()noexcept=0;

	  void bindArrayBufferObject(const ArrayBufferObject* toBind);

	  BindState getBindState();

     protected:

	  const ArrayBufferObject * getBindedBufferObject()const noexcept;

     private:

	  BindState _bindState;

	  const ArrayBufferObject *_bindedArrayBufferObject;

     };
	
} /* my_gl */



#endif /* end of include guard: VECTOR_MANAGER_HPP */
