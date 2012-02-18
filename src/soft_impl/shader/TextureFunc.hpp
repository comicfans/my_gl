/*
 * =====================================================================================
 *
 *       Filename:  TextureFunc.hpp
 *
 *    Description:  decide how fragment color and texture color blend
 *
 *
 *        Version:  1.0
 *        Created:  2011-11-9 11:08:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEXTURE_FUNC_HPP

#define TEXTURE_FUNC_HPP

#include <functional>

#include "Enum.hpp"
#include "common/Vec.hpp"

namespace my_gl {

     using std::function;

     class TextureFunc {
     public:
     	TextureFunc (GLenum texEnvMode=GL_REPLACE);

	Vec4 operator()
	     (GLenum imageFormat,
	      const Vec4& fragmentColor,
	      const Vec4& textureColor)const;

	typedef function<Vec4(const Vec4& ,const Vec4& )> Func;

     private:

	GLenum _texEnvMode;

     };
	
} /* my_gl */


#endif /* end of include guard: TEXTURE_FUNC_HPP */
