/*
 * =====================================================================================
 *
 *       Filename:  TestInfinitePointLight.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-15 20:55:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_INFINITE_POINT_LIGHT_HPP

#define TEST_INFINITE_POINT_LIGHT_HPP

#include "TestLighting.hpp"

namespace my_gl {
     class TestInfinitePointLight {
     public:

	  static void init()
	  {
	       TestLighting::init();

	       float position[]={1,1,1,0};

	       glLightfv(GL_LIGHT0,GL_POSITION,position);
	  }

	  static void render()
	  {
	       TestLighting::render();
	  }
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_INFINITE_POINT_LIGHT_HPP */
