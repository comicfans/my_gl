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


	  void pointLight(int lightIdx,const Vec3& normal,const Vec3& eye,
		    const Vec3& eyeCoordPosition,
		    Vec4& ambient,Vec4& diffuse,Vec4& specular)
	  {


	       PerLightParam perLightParam=
		    _groupLightParam.getPerLightParam(lightIdx);

	       auto &lightSourceParam=perLightParam.lightSourceParam;



	       float attenuation=1.0/
		    (lightSourceParam.constantAttenuation+
		     lightSourceParam.linearAttenuation*VPLength+
		     lightSourceParam.quadraticAttenuation*VPLength*VPLength
		     );

	       //--------ambient calculation
	       ambient+=perLightParam.ambient

	       //vector from vertex to light 
	       //light position is transformed by modelView Matrix and 
	       //then store in eye Coordinates,so no need to do w() division
	       //(already processed by transformation)
	       Vec3 VP=Vec3(lightSourceParam.position.values,3)-eyeCoordPosition;	       

	       float VPLength=length(VP);

	       normalize(VP);

	       //theta is the angle VP between normal
	       //diffuse(extract Dcm to outter)
	       //percent is decided by theta
	       //cos(theta)=dotProcduct(normal ,normalized(VP));
	       //if theta>90 degree, value is clamped by 0
	       //-------------diffuse calculation

	       float nDotVP=dotProcduct(normal,VP);



	       //specular test,if normal dot VP <0,light is 
	       //on the other side of normal defined "plane"(actually vertex)
	       //no specular will be generated
	       //early GLSL not support branch test,so use max(0,nDotVP) instead

	       if (nDotVP<0)
	       {
		    //no specular generated
		    return;
	       }

	       diffuse+=nDotVP*perLightParam.diffuse;

	       Vec3 halfVec=eye+VP;

	       normalize(halfVec);

	       //OpenGL fixed function pipeline use
	       //normal-halfVec to calculate angle
	       //this is approximately when eye is 
	       //infinite (OpenGL ES 1.0 only support infinite viewer
	       // not support LOCAL_VIEWER)
	       // 
	       // actually ,the reflact vector is
	       // R=(2N dot L)N - L
	       // 
	       // real angle is between  R-eye
	       //

	       float nDotHalfVec=dotProcduct(normal,halfVec);

	       //shininess attenuation
	       if (nDotHalfVec<0)
	       {
		    return;
	       }
	       
	       float shineAttenuation=pow(nDotHalfVec,
			 _groupLightParam.material.shininess.shine);

	       specular+=perLightParam.specular*attenuation*shineAttenuation;


	  }

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
	       //if inVertex.w()==0,this is a infinite point,
	       //only directional light can color it 
	       //
	       //

	       Vec3 eyeCoordPosition=Vec3((_matrixParam.modelView*inVertex)
			 .values(),3)/inVertex.w();

	       Vec3 eyeCoordNormal=fnormal(inNormal);
		  
	  }


} /* my_gl */
