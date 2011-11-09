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

     class TextureFunc;

     class TextureFragmentShader :public FragmentShader{
     public:
     	TextureFragmentShader (const MatrixParam& matrixParam,
		  TextureFunc& textureFunc);

     	virtual ~TextureFragmentShader ();
     
     protected:

     
	virtual void shade
	       (const Vec4& inPosition,
		const Vec4& inPointSize,
		const Vec4& inFrontColor,
		const Vec4& inBackColor,
		const Vec4& inTexCoord,
		Vec4& outFragColor);
	
	TextureFunc& _textureFunc;

     };
	
} /* my_gl */



#endif /* end of include guard: TEXTURE_FRAGMENT_SHADER_HPP */
