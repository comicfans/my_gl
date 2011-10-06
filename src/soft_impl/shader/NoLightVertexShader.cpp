/*
 * =====================================================================================
 *
 *       Filename:  NoLightVertexShader.cpp
 *
 *    Description:  impl of NoLightVertexShader
 *
 *        Version:  1.0
 *        Created:  2011-9-29 17:44:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "NoLightVertexShader.hpp"

#include "common/Vec4.hpp"
#include "Global.hpp"

namespace my_gl {

     NoLightVertexShader::~NoLightVertexShader(){}

     void NoLightVertexShader::shade(
	       const Global& global,

	       const Vec4& inVertex,
	       const Vec4& inColor,
	       const Vec4& inNormal/*not used*/,
	       const Vec4& inTexCoord,

	       Vec4& outPosition,
	       Vec4& outPointSize,
	       Vec4& outClipVertex,
	       Vec4& outFrontColor,
	       Vec4& outBackColor /*not used*/,
	       Vec4& outTexCoord
	       )
     {
	  multiVec4To(global.modelView, inVertex, outPosition);
	  outFrontColor=inColor;
     }




} /* my_gl */
