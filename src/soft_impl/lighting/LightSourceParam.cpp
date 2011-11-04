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

namespace my_gl {

     LightSourceParam::LightSourceParam(bool firstOne)
     {
	  ambient={0,0,0,1};
	  diffuse=(firstOne?Vec4{1,1,1,1}:Vec4{0,0,0,1});
	  specular=(firstOne?Vec4{1,1,1,1}:Vec4{0,0,0,1});
	  position={1,1,1,0};
	  //TODO
	  //halfVector ?;
	  spotDirection={0,0,-1,0};//only 3 component used

	  spotExponent=0;
	  spotCutoff=180;

	  //TODO
	  //spotCosCutoff ?;

	  constantAttenuation=1;
	  linearAttenuation=0;
	  quadraticAttenuation=0;


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

     void LightSourceParam::lightfv(LightParamName paramName,const float* param)
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
		    position=param;
		    break;
	       case LightParamName::SPOT_DIRECTION:
		    spotDirection=param;
	       default:
		    {
			 assert(false);
		    }
	  }
     }


     bool LightSourceParam::isInfinite()const
     {
	  return position.w()==0;
     }


} /* my_gl */
