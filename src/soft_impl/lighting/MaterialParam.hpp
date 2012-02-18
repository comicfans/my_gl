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

#include "common/Vec.hpp"
#include "Enum.hpp"

namespace my_gl {
     struct MaterialParam {

	  Vec4 emission;//Ecm
	  Vec4 ambient;//Acm
	  Vec4 diffuse;//Dcm
	  Vec4 specular;//Scm
	  float shininess;//Srm

	  MaterialParam();

	  void materialf(GLenum face,GLenum paramName,float param);

	  void materialfv(GLenum face,GLenum paramName,const float* param);

     } /* optional variable list */;
	
} /* my_gl */


#endif /* end of include guard: MATERIAL_PARAM_H */
