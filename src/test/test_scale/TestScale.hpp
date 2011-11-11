/*
 * =====================================================================================
 *
 *       Filename:  TestScale.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-11 8:27:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_SCALE_HPP

#define TEST_SCALE_HPP

#include "test_client_vertex_pointer/TestClientArrayPointer.hpp"

namespace my_gl {

     class TestScale :public TestClientArrayPointer{
     public:

	  static void init()
	  {
	       TestClientArrayPointer::init();
	  }

	  static void render()
	  {
	       static const int loop=100;
	       static int counter=1;
	       static int step=1;

	       glMatrixMode(GL_MODELVIEW);

	       glLoadIdentity();

	       glTranslatef(200,200,0);

	       float factor=float(counter)/loop;

	       glScalef(factor,1-factor,factor*2);

	       glTranslatef(-54,-77,0);

	       glClear(GL_COLOR_BUFFER_BIT);

	       TestClientArrayPointer::render();

	       counter+=step;

	       if (counter==loop)
	       {
		    step=-1;
	       }else if (counter==0)
	       {
		    step=1;
	       }
	       
	  }
     
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_SCALE_HPP */
