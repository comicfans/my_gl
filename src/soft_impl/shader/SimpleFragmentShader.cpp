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

#include "VertexAttributeBuffer.hpp"

namespace my_gl {

     SimpleFragmentShader::SimpleFragmentShader
	  (const MatrixParam& matrixParam)
	  :FragmentShader(matrixParam)
	  {}

     void SimpleFragmentShader::shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor)
	       {
		    fragColor=attributeGroupRef
			 [VertexAttributeBuffer::OutIndex::FRONT_COLOR];
	       }
 
     SimpleFragmentShader::~SimpleFragmentShader(){}
} /* my_gl */
