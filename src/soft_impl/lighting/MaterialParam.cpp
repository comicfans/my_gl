/*
 * =====================================================================================
 *
 *       Filename:  MaterialParam.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 23:54:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "MaterialParam.hpp"

#include <cassert>

namespace my_gl {

     MaterialParam::MaterialParam()
     {
	  //OpenGL spec default value
	  emission=Vec4(0,0,0,1);
	  ambient=Vec4(0.2,0.2,0.2,1);
	  diffuse=Vec4(0.8,0.8,0.8,1);
	  specular=Vec4(0,0,0,1);
	  shininess=0;
     }

     void MaterialParam::materialf
	  (Face /*ignore*/,LightParamName paramName,float param)
	  {
	       assert(paramName==LightParamName::SHININESS);

	       shininess=param;
	  }

     void MaterialParam::materialfv
	  (Face /*ignore*/,LightParamName paramName,const float* param)
	  {
	       switch (paramName)
	       {
		    case LightParamName::AMBIENT:
			 ambient=param;
			 break;
		    case LightParamName::DIFFUSE:
			 diffuse=param;
			 break;
		    case LightParamName::SPECULAR:
			 specular=param;
			 break;
		    case LightParamName::EMISSION:
			 emission=param;
			 break;
		    case LightParamName::AMBIENT_AND_DIFFUSE:
			 ambient=diffuse=param;
			 break;
		    default:
			 {
			      assert(false);
			 }
	       }
	  }

} /* my_gl */
