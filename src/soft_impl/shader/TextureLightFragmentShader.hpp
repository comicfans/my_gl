/*
 * =====================================================================================
 *
 *       Filename:  TextureLightFragmentShader.hpp
 *
 *    Description:  do fragment shader when lighting and 
 *    texture is enabled
 *
 *        Version:  1.0
 *        Created:  2011-11-8 15:05:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEXTURE_LIGHT_FRAGMENT_SHADER_HPP

#define TEXTURE_LIGHT_FRAGMENT_SHADER_HPP
#include "TextureFragmentShader.hpp"

namespace my_gl {
     class TextureLightFragmentShader :public TextureFragmentShader{
     public:
     	TextureLightFragmentShader 
	     (const MatrixParam& matrixParam);

     	virtual ~TextureLightFragmentShader ();

     protected:

	  virtual void shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor);
     
     };
	
} /* my_gl */


#endif /* end of include guard: TEXTURE_LIGHT_FRAGMENT_SHADER_HPP */
