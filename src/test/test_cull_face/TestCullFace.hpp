/*
 * =====================================================================================
 *
 *       Filename:  TestCullFace.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-13 22:16:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_CULL_FACE_HPP

#define TEST_CULL_FACE_HPP

#include "test_draw_elements/TestDrawElements.hpp"

namespace my_gl {
     class TestCullFace :public TestDrawElements{
     public:

	  static void enableCullFace()
	  {
	       glEnable(GL_CULL_FACE);
	  }

	  static void init()
	  {
	       TestDrawElements::init();
	       enableCullFace();
	  }

	  static void render()
	  {
	       TestDrawElements::render();
	  }
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_CULL_FACE_HPP */
