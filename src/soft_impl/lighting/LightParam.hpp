/*
 * =====================================================================================
 *
 *       Filename:  LightParam.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-2 0:05:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LIGHT_PARAM_H

#define LIGHT_PARAM_H

#include "common/Vec4.hpp"
#include "Enum.hpp"

namespace my_gl {

     struct LightParam {

	  Vec4 ambient;
	  Vec4 diffuse;
	  Vec4 specular;
	  Vec4 position;
	  Vec4 halfVector;
	  Vec4 spotDirection;//only 3 component used
	  float spotExponent;
	  float spotCutoff;

	  float spotCosCutoff;

	  float constantAttenuation;
	  float linearAttenuation;
	  float quadraticAttenuation;

	  LightParam(bool firstOne=false);

	  void lightf(LightParamName paramName,float param);

	  void lightfv(LightParamName paramName,const float* param);

     } /* optional variable list */;
	
} /* my_gl */


#endif /* end of include guard: LIGHT_PARAM_H */
