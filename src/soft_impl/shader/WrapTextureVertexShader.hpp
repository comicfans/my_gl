/*
 * =====================================================================================
 *
 *       Filename:  WrapTextureVertexShader.hpp
 *
 *    Description:  transform texcoord in vertex shader
 *    just a wrapper
 *
 *        Version:  1.0
 *        Created:  2011-11-16 19:30:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef WRAP_TEXTURE_VERTEX_SHADER_HPP

#define WRAP_TEXTURE_VERTEX_SHADER_HPP

#include <memory>

#include "VertexShader.hpp"

namespace my_gl {

     using std::unique_ptr;

     class WrapTextureVertexShader :public VertexShader{
     public:

	  WrapTextureVertexShader(
		    const MatrixParam& matrixParam,
		    const GroupLightingParam& groupLightingParam,
		    VertexShader* toWrap);
     	
	  virtual ~WrapTextureVertexShader();

	  VertexShader* releaseWrapped();

     protected:
	 	  void shade(

		    const Vec4& inVertex,
		    const Vec4& /* not used */,
		    const Vec3& inNormal,
		    const Vec4& inTexCoord,

		    Vec4& outPosition,
		    Vec4& outPointSize,
		    Vec4& outFrontColor,
		    Vec4& outBackColor ,
		    Vec4& outTexCoord
		    );
    
     private:
		       unique_ptr<VertexShader> _wrapped;
     };
	
} /* my_gl */



#endif /* end of include guard: WRAP_TEXTURE_VERTEX_SHADER_HPP */
