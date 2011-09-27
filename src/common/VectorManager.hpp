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

#include <memory>

#include "Enum.hpp"


namespace my_gl {

     using std::unique_ptr;

     class VectorProvider;
     class ArrayBufferObject;
     class VectorManager {
     public:

	  VectorManager(BindState bindState) noexcept;

	  virtual ~VectorManager()noexcept;

	  VectorProvider& getProvider() noexcept;

	  void bindArrayBufferObject(const ArrayBufferObject* toBind);

	  BindState getBindState()const noexcept;

	  void enableVertexArray(bool value)noexcept;

	  bool vertexArrayEnabled()const noexcept;

     protected:

	  virtual void clientStateChangeCallback(bool value);

	  void vertexArrayChange(int componentSize,
		    DataType type,size_t stride,const void* pointer);

	  unique_ptr<VectorProvider> _pImpl;

     private:

	  const ArrayBufferObject *_bindedArrayBufferObject;

	  const BindState _bindState;

	  bool _vertexArrayEnabled;

     };
	
} /* my_gl */



#endif /* end of include guard: VECTOR_MANAGER_HPP */
