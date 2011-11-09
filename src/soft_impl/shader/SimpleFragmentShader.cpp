/*
 * =====================================================================================
 *
 *       Filename:  SimpleFragmentShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-22 17:08:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SimpleFragmentShader.hpp"

namespace my_gl {

     SimpleFragmentShader::SimpleFragmentShader
	  (const MatrixParam& matrixParam)
	  :FragmentShader(matrixParam)
	  {}

     void SimpleFragmentShader::shade
	       (const Vec4& inPosition,
		const Vec4& inPointSize,
		const Vec4& inFrontColor,
		const Vec4& inBackColor,
		const Vec4& inTexCoord,
		Vec4& outFragColor)
	       {
		    outFragColor=inFrontColor;
	       }


     SimpleFragmentShader::~SimpleFragmentShader(){}
} /* my_gl */
