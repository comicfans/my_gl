/*
 * =====================================================================================
 *
 *       Filename:  TestRotate.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-10 23:16:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_ROTATE_HPP

#define TEST_ROTATE_HPP

#include "test_client_vertex_pointer/TestClientArrayPointer.hpp"

namespace my_gl {
     class TestRotate :public TestClientArrayPointer{
     public:

	  static void init()
	  {
	       TestClientArrayPointer::init();
	       initClearColor();
	  }

	  static void initClearColor()
	  {
	       glClearColor(0,0,0,0);
	  }

	  static void render()
	  {
	       static const int loop=1000;

	       static int counter=0;

	       glClear(GL_COLOR_BUFFER_BIT);

	       glMatrixMode(GL_MODELVIEW);

	       glLoadIdentity();

	       glTranslatef(200,200,0);

	       glRotatef(360.0/loop*counter,0,0,1);

	       glTranslatef(-54,-77,0);

	       TestClientArrayPointer::render();

	       counter=(counter+1)%loop;

	  }
     
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_ROTATE_HPP */
