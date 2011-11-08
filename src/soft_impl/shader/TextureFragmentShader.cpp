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
#include "VertexAttributeBuffer.hpp"

namespace my_gl {
	
	void TextureFragmentShader::shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor)
	       {

		    auto & texCoord=attributeGroupRef
			 [int(VertexAttributeBuffer::OutIndex::TEXCOORD)];

		    Vec4 translatedTexCoord=_matrixParam.texture*texCoord;

		    assert(_textureObject);

		    fragColor=(*_textureObject)
			 (translatedTexCoord.x(),
			  translatedTexCoord.y());
	       }
} /* my_gl */
