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
	  virtual void shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor);
	  ~SimpleFragmentShader();
     };
	
} /* my_gl */


#endif /* end of include guard: SIMPLE_FRAGMENT_SHADER_HPP */
