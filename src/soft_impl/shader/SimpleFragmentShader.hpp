/*
 * =====================================================================================
 *
 *       Filename:  SimpleFragmentShader.hpp
 *
 *    Description:  simply use color to fragColor,no texture support
 *
 *        Version:  1.0
 *        Created:  2011-10-22 17:07:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SIMPLE_FRAGMENT_SHADER_HPP

#define SIMPLE_FRAGMENT_SHADER_HPP

#include "FragmentShader.hpp"

namespace my_gl {


     class SimpleFragmentShader :public FragmentShader{
     public:

     
	  SimpleFragmentShader
	       (const MatrixParam& matrixParam);
	  ~SimpleFragmentShader();
     protected:
	  virtual void shade
	       (const Vec4& inPosition,
		const Vec4& inPointSize,
		const Vec4& inFrontColor,
		const Vec4& inBackColor,
		const Vec4& inTexCoord,
		Vec4& outFragColor);


     };
	
} /* my_gl */


#endif /* end of include guard: SIMPLE_FRAGMENT_SHADER_HPP */
