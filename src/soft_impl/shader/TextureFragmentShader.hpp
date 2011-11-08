/*
 * =====================================================================================
 *
 *       Filename:  TextureFragmentShader.hpp
 *
 *    Description:  FragmentShader which can process Texture
 *
 *        Version:  1.0
 *        Created:  2011-11-8 9:59:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef TEXTURE_FRAGMENT_SHADER_HPP

#define TEXTURE_FRAGMENT_SHADER_HPP

#include "FragmentShader.hpp"

namespace my_gl {

     class TextureFragmentShader :public FragmentShader{
     public:
     	TextureFragmentShader (const MatrixParam& matrixParam);
     	virtual ~TextureFragmentShader ();
     
     protected:

	virtual void shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor);


     };
	
} /* my_gl */



#endif /* end of include guard: TEXTURE_FRAGMENT_SHADER_HPP */
