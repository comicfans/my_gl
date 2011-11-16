/*
 * =====================================================================================
 *
 *       Filename:  WrapTextureVertexShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-16 19:35:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "WrapTextureVertexShader.hpp"
namespace my_gl {
     WrapTextureVertexShader::
	  WrapTextureVertexShader(
		    const MatrixParam& matrixParam,
		    const GroupLightingParam& groupLightingParam,
		    VertexShader* toWrap)
	  :
	       VertexShader(matrixParam,groupLightingParam),
	       _wrapped(toWrap){}
     	
     WrapTextureVertexShader::~WrapTextureVertexShader(){}

	  VertexShader* WrapTextureVertexShader::releaseWrapped()
	  {
	       return _wrapped.release();
	  }

	 	  void WrapTextureVertexShader::shade(

		    const Vec4& inVertex,
		    const Vec4& inColor,
		    const Vec3& inNormal,
		    const Vec4& inTexCoord,

		    Vec4& outPosition,
		    Vec4& outPointSize,
		    Vec4& outFrontColor,
		    Vec4& outBackColor ,
		    Vec4& outTexCoord
		    )
		  {
		       _wrapped->shade(inVertex,inColor,
				 inNormal,inTexCoord,
				 outPosition,outPointSize,outFrontColor,
				 outBackColor,outTexCoord);

		       outTexCoord=_matrixParam.texture*inTexCoord;
		  }
    

} /* my_gl */
