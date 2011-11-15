/*
 * =====================================================================================
 *
 *       Filename:  TestSpotLight.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-15 16:52:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_SPOT_LIGHT_HPP

#define TEST_SPOT_LIGHT_HPP

#include "TestMovingLight.hpp"

namespace my_gl {

     class TestSpotLight :public TestMovingLight{
     public:

	  static void init()
	  {
	       TestMovingLight::init();

	       glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,7);

	       float spotDirection[]={-1,-1,-1};
	       glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDirection);
	  }

	  static void render()
	  {
	       TestMovingLight::render();	       
	  }

     };
	
} /* my_gl */


#endif /* end of include guard: TEST_SPOT_LIGHT_HPP */
