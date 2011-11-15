/*
 * =====================================================================================
 *
 *       Filename:  LightSourceParam.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-2 0:11:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LightSourceParam.hpp"

#include <cassert>
#include <cmath>

#include "common/Matrix.hpp"

namespace my_gl {

     using std::atan;
     using std::cos;

     static const float PI=4*atan(1);

     LightSourceParam::LightSourceParam(bool firstOne)
     {
	  ambient={0,0,0,1};
	  diffuse=(firstOne?Vec4{1,1,1,1}:Vec4{0,0,0,1});
	  specular=(firstOne?Vec4{1,1,1,1}:Vec4{0,0,0,1});
	  position={1,1,1,0};
	  spotDirection={0,0,-1,0};//only 3 component used

	  spotExponent=0;
	  spotCutoff=180;

	  constantAttenuation=1;
	  linearAttenuation=0;
	  quadraticAttenuation=0;

	  updateAll();

     }

     void LightSourceParam::lightf(LightParamName paramName,float param)
     {
	  switch (paramName)
	  {
	       case LightParamName::SPOT_CUTOFF:
		    spotCutoff=param;
		    break;
	       case LightParamName::SPOT_EXPONENT:
		    spotExponent=param;
	       case LightParamName::CONSTANT_ATTENUATION:
		    constantAttenuation=param;
		    break;
	       case LightParamName::LINEAR_ATTENUATION:
		    linearAttenuation=param;
		    break;
	       case LightParamName::QUADRATIC_ATTENUATION:
		    quadraticAttenuation=param;
		    break;

	       default:
		    {
			 assert(false);
		    }
	  }

     }

     void LightSourceParam::lightfv(LightParamName paramName,
	       const float* param,const Matrix4& modelViewMatrix)
     {
	  switch (paramName)
	  {
	       case LightParamName::AMBIENT:
		    ambient=param;
		    break;
	       case LightParamName::DIFFUSE:
		    diffuse=param;
	       case LightParamName::SPECULAR:
		    specular=param;
		    break;
	       case LightParamName::POSITION:
		    position=modelViewMatrix*Vec4(param);
		    break;
	       case LightParamName::SPOT_DIRECTION:
		    {

		    Matrix3 mat3=upperLeft(modelViewMatrix)
			 .inverse().transpose();

		    spotDirection=mat3*Vec3(param);
		    normalize(spotDirection);

		    break;
		    }
	       default:
		    {
			 assert(false);
		    }
	  }
     }

     void LightSourceParam::updateAll()
     {

	  //halfVector is the sum of 
	  //vertex-lightPostion direction vector and vertex-eye direction vector
	  //in OpenGL ES 1.0, only infinite eye position is supported
	  //so use {0,0,1} as eye direction
	  halfVector=Vec3(position.values(),3)+Vec3{0,0,1};

	  normalize(halfVector);


	  spotCosCutoff=cos(spotCutoff/180*PI);


     }

     bool LightSourceParam::isInfinite()const
     {
	  return position.w()==0;
     }


} /* my_gl */
