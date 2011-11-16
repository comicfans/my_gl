/*
 * =====================================================================================
 *
 *       Filename:  TestTexEnvFunc.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-16 22:38:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_TEX_ENV_FUNC_HPP

#define TEST_TEX_ENV_FUNC_HPP

#include "TestTexture.hpp"

namespace my_gl {
     class TestTexEnvFunc {
     public:

	  static void init()
	  {
	       TestTexture::init();

	       glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	       glEnableClientState(GL_COLOR_ARRAY);
	  }

	  static void render()
	  {
	       static GLfloat colors[3][3]={{0,0,1},{0,1,0},{1,0,0}};

	       glBindBuffer(GL_ARRAY_BUFFER,0);
	       glColorPointer(3,GL_FLOAT,0,colors);

	       TestTexture::render();
	  }
     
     };
	
} /* my_gl */


#endif /* end of include guard: TEST_TEX_ENV_FUNC_HPP */
