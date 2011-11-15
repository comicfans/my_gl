/*
 * =====================================================================================
 *
 *       Filename:  TestMovingLight.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-15 14:36:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_MOVING_LIGHT_HPP

#define TEST_MOVING_LIGHT_HPP

#include "TestLighting.hpp"

namespace my_gl {
     class TestMovingLight:public TestLighting {
     public:

	  static void init()
	  {
	       TestLighting::init();
	  }

	  static void render()
	  {
	       static const int loop=100;
	       static int counter=0;

	       glMatrixMode(GL_MODELVIEW);

	       glPushMatrix();
	       glLoadIdentity();
	       glRotatef(360.0/loop*counter,0,-1,0);

	       const float position[]={1000,1000,1000,1};
	       glLightfv(GL_LIGHT0,GL_POSITION,position);

	       glPopMatrix();

	       TestLighting::render();

	       counter=(counter+1)%loop;
	  }


     };
	
} /* my_gl */

#endif /* end of include guard: TEST_MOVING_LIGHT_HPP */
