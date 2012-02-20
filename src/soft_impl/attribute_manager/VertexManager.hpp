/*
 * =====================================================================================
 *
 *       Filename:  VertexManager.hpp
 *
 *    Description:  class to manager vertex attribute call
 *
 *        Version:  1.0
 *        Created:  2011-9-20 22:12:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VERTEX_MANAGER_HPP

#define VERTEX_MANAGER_HPP

#include "common/Vec4Manager.hpp"


namespace my_gl {

     class VertexManager :public Vec4Manager{
     public:
     	VertexManager ();

	//glVertexPointer
	void vertexPointer(int componentSize,GLenum type,size_t stride,const void* pointer);

	static const GLenum BIND_STATE=GL_VERTEX_ARRAY;

     };
	
} /* my_gl */


#endif /* end of include guard: VERTEX_MANAGER_HPP */
