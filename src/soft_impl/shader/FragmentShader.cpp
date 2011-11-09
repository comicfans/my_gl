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
#include "VertexAttributeBuffer.hpp"

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

	  void FragmentShader::shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor)
	       {
	       enum OutIndex{POSITION,POINT_SIZE,
		    FRONT_COLOR,BACK_COLOR,TEXCOORD};


		    shade(attributeGroupRef[int(VertexAttributeBuffer
				   ::OutIndex::POSITION)],
			      attributeGroupRef[int(VertexAttributeBuffer
				   ::OutIndex::POINT_SIZE)],
			      attributeGroupRef[int(VertexAttributeBuffer
				   ::OutIndex::FRONT_COLOR)],
			      attributeGroupRef[int(VertexAttributeBuffer
				   ::OutIndex::BACK_COLOR)],
			      attributeGroupRef[int(VertexAttributeBuffer
				   ::OutIndex::TEXCOORD)],
			      fragColor);
	       }


     FragmentShader::~FragmentShader(){}
} /* my_gl */
