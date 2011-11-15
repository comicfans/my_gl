/*
 * =====================================================================================
 *
 *       Filename:  GlutTestTpl.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-15 14:44:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef GLUT_TEST_TPL_HPP

#define GLUT_TEST_TPL_HPP

#include <GL/glew.h>
#include <GL/glut.h>
#include "GlutInit.hpp"

namespace my_gl {

     template<class T>
	  void singleBufferRun()
	  {
	       initGlutGlew();
	       T::init();
	       glutDisplayFunc(T::render);
	       glutIdleFunc(idleFunc);
	       glutMainLoop();
	  }

     template<class T,int millionSecond>
	  void swapBuffers(int)
	  {
	       T::render();
	       glutSwapBuffers();
	       glutTimerFunc(millionSecond,
			 swapBuffers<T,millionSecond>,0);
	  }

     template <class T,int millionSecond=1000>
	  void doubleBufferRun()
	  {
	       initGlutGlew();
	       T::init();
	       glutTimerFunc(millionSecond,
			 swapBuffers<T,millionSecond>,0);
	       glutMainLoop();
	  }
	
} /* my_gl */


#endif /* end of include guard: GLUT_TEST_TPL_HPP */
