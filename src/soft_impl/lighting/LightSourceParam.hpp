/*
 * =====================================================================================
 *
 *       Filename:  LightSourceParam.hpp
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

#ifndef LIGHT_SOURCE_PARAM_HPP

#define LIGHT_SOURCE_PARAM_HPP

#include "common/Vec.hpp"
#include "Enum.hpp"

namespace my_gl {

     struct LightSourceParam {

	  Vec4 ambient;//Acli
	  Vec4 diffuse;//Dcli
	  Vec4 specular;//Scli
	  Vec4 position;//Ppli
	  Vec4 halfVector;//Derived: Hi
	  Vec4 spotDirection;//Sdli only 3 component used
	  float spotExponent;//Srli
	  float spotCutoff;//Crli range:[0~90],180

	  float spotCosCutoff;//Derived cos(Crli) range(1~0),-1

	  float constantAttenuation;//K0
	  float linearAttenuation;//K1
	  float quadraticAttenuation;//K2

	  LightSourceParam(bool firstOne=false);

	  void lightf(LightParamName paramName,float param);

	  void lightfv(LightParamName paramName,const float* param);

	  bool isDirectional()const;

     } /* optional variable list */;
	
} /* my_gl */


#endif /* end of include guard: LIGHT_SOURCE_PARAM_HPP*/
