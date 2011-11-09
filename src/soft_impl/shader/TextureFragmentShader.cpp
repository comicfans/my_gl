/*
 * =====================================================================================
 *
 *       Filename:  TextureFragmentShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-8 10:16:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TextureFragmentShader.hpp"
#include "MatrixParam.hpp"
#include "object/TextureObject.hpp"
#include "TextureFunc.hpp"

namespace my_gl {
	
     TextureFragmentShader::~TextureFragmentShader (){}

     TextureFragmentShader::TextureFragmentShader 
	  (const MatrixParam& matrixParam,
	   TextureFunc& textureFunc):
	       FragmentShader(matrixParam),_textureFunc(textureFunc)
     {}

     void TextureFragmentShader::shade
	       (const Vec4& inPosition,
		const Vec4& inPointSize,
		const Vec4& inFrontColor,
		const Vec4& inBackColor,
		const Vec4& inTexCoord,
		Vec4& outFragColor)
	       {
		    Vec4 translatedTexCoord=
			 _matrixParam.texture*inTexCoord;

		    assert(_textureObject);

		    Vec4 textureColor=(*_textureObject)
			 (translatedTexCoord.x(),translatedTexCoord.y());

		    outFragColor=_textureFunc(_textureObject->getFormat(),
			      inFrontColor,textureColor);

	       }
	
} /* my_gl */
