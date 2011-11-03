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

#include "common/Vec.hpp"
#include "MatrixParam.hpp"

namespace my_gl {
     NoLightVertexShader::
	  NoLightVertexShader(const MatrixParam& matrixParam,
	       const GroupLightingParam& groupLightingParam)
	  :VertexShader(matrixParam,groupLightingParam){}
 

     NoLightVertexShader::~NoLightVertexShader(){}

     void NoLightVertexShader::shade(

	       const Vec4& inVertex,
	       const Vec4& inColor,
	       const Vec4& inNormal/*not used*/,
	       const Vec4& inTexCoord,

	       Vec4& outPosition,
	       Vec4& outPointSize,
	       Vec4& outFrontColor,
	       Vec4& outBackColor /*not used*/,
	       Vec4& outTexCoord
	       )
     {

	  outPosition=_matrixParam.modelViewProjection*inVertex;

	  outFrontColor=inColor;
	  outBackColor=inColor;
     }




} /* my_gl */
