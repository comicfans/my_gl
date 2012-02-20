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

     static const float PI=4*(std::atan(1.0));

     LightSourceParam::LightSourceParam(bool firstOne)
     {
	  ambient=Vec4(0,0,0,1);
	  diffuse=(firstOne?Vec4(1,1,1,1):Vec4(0,0,0,1));
	  specular=(firstOne?Vec4(1,1,1,1):Vec4(0,0,0,1));
	  position=Vec4(1,1,1,0);
	  spotDirection=Vec3(0,0,-1);//only 3 component used

	  spotExponent=0;
	  spotCutoff=180;

	  constantAttenuation=1;
	  linearAttenuation=0;
	  quadraticAttenuation=0;

	  updateAll();

     }

     void LightSourceParam::lightf(GLenum paramName,float param)
     {
	  switch (paramName)
	  {
	       case GL_SPOT_CUTOFF:
		    spotCutoff=param;
		    break;
	       case GL_SPOT_EXPONENT:
		    spotExponent=param;
	       case GL_CONSTANT_ATTENUATION:
		    constantAttenuation=param;
		    break;
	       case GL_LINEAR_ATTENUATION:
		    linearAttenuation=param;
		    break;
	       case GL_QUADRATIC_ATTENUATION:
		    quadraticAttenuation=param;
		    break;

	       default:
		    {
			 assert(false);
		    }
	  }

     }

     void LightSourceParam::lightfv(GLenum paramName,
	       const float* param,const Matrix4& modelViewMatrix)
     {
	  switch (paramName)
	  {
	       case GL_AMBIENT:
		    ambient=param;
		    break;
	       case GL_DIFFUSE:
		    diffuse=param;
	       case GL_SPECULAR:
		    specular=param;
		    break;
	       case GL_POSITION:
		    position=modelViewMatrix*Vec4(param);
		    break;
	       case GL_SPOT_DIRECTION:
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
	  halfVector=Vec3(position.values(),3)+Vec3(0,0,1);

	  normalize(halfVector);


	  spotCosCutoff=cos(spotCutoff/180*PI);


     }

     bool LightSourceParam::isInfinite()const
     {
	  return position.w()==0;
     }


} /* my_gl */
