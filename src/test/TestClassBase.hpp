/*
 * =====================================================================================
 *
 *       Filename:  TestClassBase.hpp
 *
 *    Description:  this test class call the same 
 *    OpenGL function for glut test and my_gl test
 *    some GLES GL1.5 GL2.0 function use glew to 
 *    call these function , but glew use macros to
 *    replace gl call ,this leads function linkage
 *    not same as gl.h define, and MyGL use exactly
 *    the same linkage in gl.h , so these function 
 *    can not be written in seperate implementation 
 *    cpp file. these GL function call are defined 
 *    depends on caller header definition
 *
 *        Version:  1.0
 *        Created:  2011-11-10 18:46:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_CLASS_BASE_HPP

#define TEST_CLASS_BASE_HPP

#include "GlutInit.hpp"

namespace my_gl {
     class TestClassBase {
     public:
 	  static void init()
	  {


	       glMatrixMode(GL_PROJECTION);

	       glLoadIdentity();

	       glOrtho(0,DEFAULT_WIDTH,0,DEFAULT_HEIGHT,-10000,10000);

	       glViewport(0,0,DEFAULT_WIDTH,DEFAULT_HEIGHT);

	       glMatrixMode(GL_MODELVIEW);

	       glLoadIdentity();

	  }

    
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_CLASS_BASE_HPP */
