/*
 * =====================================================================================
 *
 *       Filename:  FragmentShader.hpp
 *
 *    Description:  class to process fragment
 *
 *        Version:  1.0
 *        Created:  2011-10-15 22:15:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef FRAGMENT_SHADER_HPP

#define FRAGMENT_SHADER_HPP

#include "FragmentAttributeBuffer.hpp"

namespace my_gl {

     class TextureObject;

     class MatrixParam;

     class FragmentShader {
     public:

	  FragmentShader(const MatrixParam& matrixParam);

	  virtual void shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor);

	  virtual ~FragmentShader();

	  void setTextureObject(TextureObject *textureObject);


    protected:

	  virtual void shade
	       (const Vec4& inPosition,
		const Vec4& inPointSize,
		const Vec4& inFrontColor,
		const Vec4& inBackColor,
		const Vec4& inTexCoord,
		Vec4& outFragColor)=0;

	  TextureObject *_textureObject;

	  const MatrixParam& _matrixParam;

     
     };
	
} /* my_gl */


#endif /* end of include guard: FRAGMENT_SHADER_HPP */
