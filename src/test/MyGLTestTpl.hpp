/*
 * =====================================================================================
 *
 *       Filename:  MyGLTestTpl.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-15 15:07:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MY_GL_TEST_TPL_HPP

#define MY_GL_TEST_TPL_HPP

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include "soft_impl/SoftContext.hpp"

namespace my_gl {
	
template<class T,int frames=30>
void myGLTestRun()
{
     const int DEFAULT_WIDTH=400;

     const int DEFAULT_HEIGHT=300;

     SoftContext context(DEFAULT_WIDTH,DEFAULT_HEIGHT);

     T::init();

     for (int i=0; i<frames; ++i)
     {
	  T::render();
	  glFlush();
     }

}




} /* my_gl */
#endif /* end of include guard: MY_GL_TEST_TPL_HPP */
