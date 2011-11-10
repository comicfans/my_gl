/*
 * =====================================================================================
 *
 *       Filename:  TestClientArrayPointer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 19:38:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_CLIENT_ARRAY_POINTER_HPP

#define TEST_CLIENT_ARRAY_POINTER_HPP

#include "test_array_buffer_object/TestArrayBufferObject.hpp"

namespace my_gl {
		  static float color3x3[3][3]={
	       {0,0,1},
	       {0,1,0},
	       {1,0,0}};


     class TestClientArrayPointer {
     public:

	  static void init()
	  {
	       TestArrayBufferObject::init();

	       createColor3x3();

	  }

	  static void createColor3x3()
	  {
	       glEnableClientState(GL_COLOR_ARRAY);
	  }

	  static void render()
	  {

	       glBindBuffer(GL_ARRAY_BUFFER,
			 TestArrayBufferObject::triangleVertexName);
	       glVertexPointer(2,GL_FLOAT,0,0);


	       glBindBuffer(GL_ARRAY_BUFFER,0);
	       glColorPointer(3,GL_FLOAT,0,color3x3);

	       glDrawArrays(GL_TRIANGLES,0,3);
	  }
     
     };

} /* my_gl */


#endif /* end of include guard: TEST_CLIENT_ARRAY_POINTER_HPP */
