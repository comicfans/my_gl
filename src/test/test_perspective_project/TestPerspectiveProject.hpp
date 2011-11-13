/*
 * =====================================================================================
 *
 *       Filename:  TestPerspectiveProject.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-11 9:42:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_PERSPECTIVE_PROJECT_HPP

#define TESTPERSPECTIVE_PROJECT_HPP

#include "test_cull_face/TestCullFace.hpp"

namespace my_gl {
     class TestPerspectiveProject :public TestCullFace{
     public:

	  static void perspectiveProjection()
	  {
	       glMatrixMode(GL_PROJECTION);

	       glLoadIdentity();

	       glFrustum(-DEFAULT_WIDTH/2,DEFAULT_WIDTH/2,
			 -DEFAULT_HEIGHT/2,DEFAULT_HEIGHT/2,
			 100,500);

	  }

	  static void init()
	  {
	       TestCullFace::init();
	       perspectiveProjection();
	  }

	  static void render()
	  {

	       glMatrixMode(GL_MODELVIEW);
	       glLoadIdentity();

	       glTranslatef(-DEFAULT_WIDTH/2,-DEFAULT_HEIGHT/2,-300);

	       TestDrawElements::transformPosition();

	       TestDrawElements::drawCube();


	  }

     
     };
	
} /* my_gl */


#endif /* end of include guard: TESTPERSPECTIVE_PROJECT_HPP */
