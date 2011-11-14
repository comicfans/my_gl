/*
 * =====================================================================================
 *
 *       Filename:  TestCullFaceBack.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-14 8:39:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_CULL_FACE_BACK_HPP

#define TEST_CULL_FACE_BACK_HPP

#include "TestCullFace.hpp"

namespace my_gl {

     class TestCullFaceBack :public TestCullFace{
     public:

	  static void init()
	  {
	       TestCullFace::init();
	       glCullFace(GL_FRONT);
	  }

	  static void render()
	  {
	       TestCullFace::render();
	  }
     
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_CULL_FACE_BACK_HPP */
