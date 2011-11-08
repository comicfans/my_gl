/*
 * =====================================================================================
 *
 *       Filename:  FragmentShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-28 23:40:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "FragmentShader.hpp"

namespace my_gl {

     FragmentShader::FragmentShader(const 
	       MatrixParam& matrixParam)
	  :_matrixParam(matrixParam)
     {

     }

	  void FragmentShader::setTextureObject
	       (TextureObject *textureObject)
	  {
	       _textureObject=textureObject;
	  }

     FragmentShader::~FragmentShader(){}
} /* my_gl */
