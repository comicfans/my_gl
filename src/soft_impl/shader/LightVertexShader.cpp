/*
 * =====================================================================================
 *
 *       Filename:  LightVertexShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-2 12:09:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LightVertexShader.hpp"

namespace my_gl {


 	  LightVertexShader(const MatrixParam& matrixParam,
			 const GroupLightingParam& groupLightParam)
	       :VertexShader(matrixParam,groupLightParam)
	  { }
		  void LightVertexShader::shade(

		    const Vec4& inVertex,
		    const Vec4& inColor/*not used*/,
		    const Vec3& inNormal,
		    const Vec4& inTexCoord,

		    Vec4& outPosition,
		    Vec4& outPointSize,
		    Vec4& outFrontColor,
		    Vec4& outBackColor, 
		    Vec4& outTexCoord
		    )
	  {
	       //reference 3DLabs GLSL ShaderGen
	       //for a vertex pass,material param is fixed
	       //so calculate ambient diffuse and specular pecent 
	       //of per light ,then sum together, then mul
	       //
	       //
	       //
	       //
	       Vec3 eyeCoordPosition=Vec3((_matrixParam.modelView*inVertex)
			 .values(),3)/inVertex.w();

	       Vec3 eyeCoordNormal=fnormal(inNormal);
		  
	  }


} /* my_gl */
