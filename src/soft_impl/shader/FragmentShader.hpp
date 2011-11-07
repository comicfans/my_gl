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

     class FragmentShader {
     public:

	  virtual void shade
	       (ConstAttributeGroupRef attributeGroupRef,
		 Vec4& fragColor)=0;

	  virtual ~FragmentShader();

	  void setTextureObject(TextureObject *textureObject);

     protected:

	  TextureObject *_textureObject;

     
     };
	
} /* my_gl */


#endif /* end of include guard: FRAGMENT_SHADER_HPP */
