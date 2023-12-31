/*
 * =====================================================================================
 *
 *       Filename:  Vec4Manager.hpp
 *
 *    Description:  manager object to provide a Vec4Provider
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

#ifndef VEC4_MANAGER_HPP

#define VEC4_MANAGER_HPP

#include <memory>

#include "Enum.hpp"
#include "Vec4Provider.hpp"


namespace my_gl {

     using std::unique_ptr;

     class Vec4Provider;
     class ArrayBufferObject;
     class Vec4Manager :public Vec4Provider{
     public:

	  Vec4Manager(GLenum bindState) ;

	  virtual ~Vec4Manager();

	  void bindArrayBufferObject(const ArrayBufferObject* toBind);

	  GLenum getBindState()const ;

	  void enableVertexArray(bool value);

	  bool vertexArrayEnabled()const ;

	  virtual Vec4 getValue(size_t index);
	
     protected:

	  virtual void clientStateChangeCallback(bool value);

	  void vertexArrayChange(int componentSize,
		    GLenum type,size_t stride,const void* pointer,
		    bool normalize=false);

	  unique_ptr<Vec4Provider> _pImpl;

     private:

	  const ArrayBufferObject *_bindedArrayBufferObject;

	  const GLenum _bindState;

	  bool _vertexArrayEnabled;

     };
	
} /* my_gl */



#endif /* end of include guard: VEC4_MANAGER_HPP */
