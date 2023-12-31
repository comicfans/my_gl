/*
 * =====================================================================================
 *
 *       Filename:  GlutInit.hpp
 *
 *    Description:  init glut and glew function
 *
 *        Version:  1.0
 *        Created:  2011-11-10 19:29:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef GLUT_INIT_HPP

#define GLUT_INIT_HPP



namespace my_gl {
	
     const int DEFAULT_WIDTH=500;
     const int DEFAULT_HEIGHT=400;

     void initGlutGlew(const char *p="test");

     void idleFunc();
} /* my_gl */



#endif /* end of include guard: GLUT_INIT_HPP */
