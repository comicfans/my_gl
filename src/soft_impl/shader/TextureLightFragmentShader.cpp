/*
 * =====================================================================================
 *
 *       Filename:  TextureLightFragmentShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-8 15:07:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TextureLightFragmentShader.hpp"
#include "VertexAttributeBuffer.hpp"

namespace my_gl {

     TextureLightFragmentShader::
	  ~TextureLightFragmentShader(){}

     TextureLightFragmentShader::
	  TextureLightFragmentShader(const MatrixParam& matrixParam)
	  :TextureFragmentShader(matrixParam){}

	void TextureLightFragmentShader::shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor)
	       {
		    TextureFragmentShader::
			 shade(attributeGroupRef,
			      fragColor);

		    auto & frontColor=attributeGroupRef
			 [VertexAttributeBuffer::
			 OutIndex::FRONT_COLOR];

		    fragColor=componentMul
			 (frontColor,fragColor);
	       }
     

} /* my_gl */
