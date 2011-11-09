/*
 * =====================================================================================
 *
 *       Filename:  LightVertexShader.cpp
 *
 *    Description:  
 *
 *        oat Version:  1.0
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

#include <cmath>

#include "lighting/GroupLightingParam.hpp"
#include "MatrixParam.hpp"
#include "common/Vec.hpp"

namespace my_gl {

     using std::max;

     LightVertexShader::LightVertexShader(const MatrixParam& matrixParam,
			 const GroupLightingParam& groupLightParam)
	       :VertexShader(matrixParam,groupLightParam)
	  { }

     LightVertexShader::~LightVertexShader(){}

	  void LightVertexShader::infiniteLight(PerLightParam perLightParam,
		    const Vec3& normal,
		    Vec4& ambient,Vec4& diffuse,Vec4& specular)
	  {

	       // length attenuation is 1.0

	       auto &lightSourceParam=perLightParam.lightSourceParam;

	       float nDotVP=dotProduct(normal,
			 Vec3(lightSourceParam.position.values(),3));

	       //this halfVec does not depends on 
	       //vertex eye Coordinates 
	       //(infinite light,direction is just light position)
	       float nDotHV=dotProduct(normal,
			 Vec3(lightSourceParam.halfVector.values(),3));

	       float spotAttenuation=1.0;

	       if (lightSourceParam.spotCutoff!=180.0)
	       {
		    //direction from light to vertex
		    Vec3 Ppli=-Vec3(lightSourceParam.position.values(),3),
			 Sdli=lightSourceParam.spotDirection;

		    normalize(Ppli);
		    normalize(Sdli);

		    //cutoff < 90 .so dotProduct must be >=0
		    float dot=dotProduct(Ppli,Sdli);

		    spotAttenuation=pow(dot,_groupLightingParam.material.shininess);

	       }

	       float shineAttenuation=0.0;

	       if (nDotVP>0 && nDotHV>0)
	       {
		    shineAttenuation=pow(nDotHV,_groupLightingParam.material.shininess);
	       }
	       //else, no specular
	       
	       ambient+=lightSourceParam.ambient*spotAttenuation;
	       diffuse+=lightSourceParam.diffuse*spotAttenuation*max(0.0f,nDotVP);
	       specular+=lightSourceParam.specular*spotAttenuation*shineAttenuation;

	  }

	  /** 
	   * @brief finite spot light including cutoff=[0~90] and 180
	   * 
	   * @param lightIdx
	   * @param normal
	   * @param eye
	   * @param eyeCoordPosition
	   * @param ambient
	   * @param diffuse
	   * @param specular
	   */
	  void LightVertexShader::finiteLight(PerLightParam perLightParam,
		    const Vec3& normal,const Vec3& eye,
		    const Vec3& eyeCoordPosition,
		    Vec4& ambient,Vec4& diffuse,Vec4& specular)
	  {

	       auto &lightSourceParam=perLightParam.lightSourceParam;

	       Vec3 VP=Vec3(lightSourceParam.position.values(),3)-eyeCoordPosition;	       

	       float VPLength=length(VP);

	       //check cutoff first

	       float attenuation=1.0;

	       if (lightSourceParam.spotCutoff!=180.0)
	       {
		    float spotDot=dotProduct(-VP,lightSourceParam.spotDirection);

		    if (spotDot<lightSourceParam.spotCosCutoff)
		    {
			 //out of spot light cutoff,no light
			 return;
		    }

		    //this attenuation is spot cut off attenuation
		    attenuation*=pow(spotDot,lightSourceParam.spotExponent);
	       }


	       attenuation*=1.0/
		    (lightSourceParam.constantAttenuation+
		     lightSourceParam.linearAttenuation*VPLength+
		     lightSourceParam.quadraticAttenuation*VPLength*VPLength
		     );

	       //--------ambient calculation
	       ambient+=lightSourceParam.ambient;

	       //vector from vertex to light 
	       //light position is transformed by modelView Matrix and 
	       //then store in eye Coordinates,so no need to do w() division
	       //(already processed by transformation)
	       normalize(VP);

	       //theta is the angle VP between normal
	       //diffuse(extract Dcm to outter)
	       //percent is decided by theta
	       //cos(theta)=dotProduct(normal ,normalized(VP));
	       //if theta>90 degree, value is clamped by 0
	       //-------------diffuse calculation

	       float nDotVP=dotProduct(normal,VP);



	       //specular test,if normal dot VP <0,light is 
	       //on the other side of normal defined "plane"(actually vertex)
	       //no specular will be generated
	       //early GLSL not support branch test,so use max(0,nDotVP) instead

	       if (nDotVP<0)
	       {
		    //no specular generated
		    return;
	       }

	       diffuse+=lightSourceParam.diffuse*nDotVP;

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

	       float nDotHalfVec=dotProduct(normal,halfVec);

	       //shininess attenuation
	       if (nDotHalfVec<0)
	       {
		    //angle between vertex-eye direction and reflect >90
		    //no specular
		    return;
	       }
	       
	       //specular defined the "light point area" of object
	       float shineAttenuation=pow(nDotHalfVec,
			 _groupLightingParam.material.shininess);

	       specular+=lightSourceParam
		    .specular*attenuation*shineAttenuation;


	  }

	  Vec4 LightVertexShader::singleSideLighting
	       (const Vec4& inVertex,const Vec3& inNormal)
	       {
	       //reference 3DLabs GLSL ShaderGen
	       //for a vertex pass,material param is fixed
	       //so calculate ambient diffuse and specular pecent 
	       //of per light ,then sum together, then mul
	       //
	       //
	       //if inVertex.w()==0,this is a infinite point,
	       //only infinite light can color it 
	       //

	       Vec4 ambient={0,0,0,0},
	       diffuse={0,0,0,0},
	       specular={0,0,0,0};

	       Vec3 eyeCoordNormal=fnormal(inNormal);

	       Vec3 eyeCoordPosition;
	       
	       if (inVertex.w()!=0)
	       {
		    eyeCoordPosition=
			 Vec3((_matrixParam.modelView*inVertex)
			 .values(),3)/inVertex.w();
	       }
	       


		    //only apply infiniteLight

		    for (int i=0; i<_groupLightingParam.getActiveLightNumber(); ++i)
		    {
			 //per light iterator
			 PerLightParam perLightParam=
			      _groupLightingParam.getPerLightParam(i);

			 if (!perLightParam.lightSourceParam.isInfinite())
			 {
			      if (inVertex.w()==0)
			      {
				   continue;
			      }
			      finiteLight(perLightParam,
					//OpenGL ES 1.0 only support infinite viewer
					//eye vector will always be {0,0,1}
					eyeCoordNormal,Vec3{0,0,1},
					eyeCoordPosition,
					ambient,diffuse,specular);
			 }
			 else
			 {
			      infiniteLight(perLightParam,eyeCoordNormal,
					ambient,diffuse,specular);
			 }
				 
		    }

		    
		    //Ecm+Acm*Acs
		    Vec4 finalColor=_groupLightingParam.
			 lightModelProduct.sceneColor;

		    auto & material=_groupLightingParam.material;
		    finalColor+=componentMul(material.ambient,ambient);
		    finalColor+=componentMul(material.diffuse,diffuse);
		    finalColor+=componentMul(material.specular,specular);

		    return finalColor;

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
	       outFrontColor=singleSideLighting(inVertex,inNormal);

	       outPosition=ftransform(inVertex);
		  
	  }


} /* my_gl */
