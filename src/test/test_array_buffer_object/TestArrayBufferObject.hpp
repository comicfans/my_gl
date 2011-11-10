/*
 * =====================================================================================
 *
 *       Filename:  TestArrayBuffer.hpp
 *
 *    Description:  test exported array buffer object
 *
 *        Version:  1.0
 *        Created:  2011-11-10 10:33:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef TEST_ARRAY_BUFFER_OBJECT_HPP

#define TEST_ARRAY_BUFFER_OBJECT_HPP


#include "TestClassBase.hpp"


namespace my_gl {

     class TestArrayBufferObject {
     public:

	  static void init()
	  {

	       TestClassBase::init();

	       createTriangleBuffer();
	  }

	  static void createTriangleBuffer()
	  {
	       glEnableClientState(GL_VERTEX_ARRAY);

	       glGenBuffers(1,&triangleVertexName);

	       glBindBuffer(GL_ARRAY_BUFFER,triangleVertexName);

	       GLfloat triangle[][2]={{12,12},{100,19},{50,200}};
	       
	       glBufferData(GL_ARRAY_BUFFER,sizeof(triangle),
			 triangle,GL_STATIC_DRAW);
	  }

	  static void render()
	  {

	       glColor4f(0.5,0.6,0.1,1);

	       glVertexPointer(2,GL_FLOAT,0,0);

	       glDrawArrays(GL_TRIANGLES,0,3);

	  }

	  static GLuint triangleVertexName;

     
     };

     GLuint TestArrayBufferObject::triangleVertexName;
	
} /* my_gl */

#endif /* end of include guard: TEST_ARRAY_BUFFER_OBJECT_HPP*/
