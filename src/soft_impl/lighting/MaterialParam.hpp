/*
 * =====================================================================================
 *
 *       Filename:  MaterialParam.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 23:47:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef MATERIAL_PARAM_H

#define MATERIAL_PARAM_H

#include "common/Vec4.hpp"
#include "Enum.hpp"

namespace my_gl {
     struct MaterialParam {

	  Vec4 emission;
	  Vec4 ambient;
	  Vec4 diffuse;
	  Vec4 specular;
	  float shininess;

	  MaterialParam();

	  void materialf(Face face,LightParamName paramName,float param);

	  void materialfv(Face face,LightParamName paramName,const float* param);

     } /* optional variable list */;
	
} /* my_gl */


#endif /* end of include guard: MATERIAL_PARAM_H */
