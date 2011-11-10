/*
 * =====================================================================================
 *
 *       Filename:  TestClassBase.hpp
 *
 *    Description:  
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

namespace my_gl {
     class TestClassBase {
     public:
 	  static void init(int width,int height)
	  {
	       glMatrixMode(GL_PROJECTION);

	       glLoadIdentity();

	       glOrtho(0,width,0,height,-1,1);

	       glViewport(0,0,width,height);

	       glMatrixMode(GL_MODELVIEW);

	       glLoadIdentity();

	  }

    
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_CLASS_BASE_HPP */
