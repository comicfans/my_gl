/*
 * =====================================================================================
 *
 *       Filename:  GroupLightingParam.hpp
 *
 *    Description:  group all glsl related lighting parameter together
 *
 *        Version:  1.0
 *        Created:  2011-11-2 15:23:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef GROUP_LIGHTING_PARAM_HPP

#define GROUP_LIGHTING_PARAM_HPP

#include <vector>

#include "common/MatrixFwd.hpp"
#include "MaterialParam.hpp"
#include "LightSourceParam.hpp"

namespace my_gl {

     using std::vector;

	  struct LightProducts {
	       Vec4 ambient;//Acm*Acli
	       Vec4 diffuse;//Dcm*Dcli
	       Vec4 specular;//Scm*Scli
	  } ;


     struct PerLightParam{
	       PerLightParam
		    (const LightSourceParam& lightSourceParamSet,
		     const LightProducts& lightProductSet);

	       const LightSourceParam& lightSourceParam;
	       const LightProducts& lightProduct;
	  };


     struct GroupLightingParam {

	  const static int MAX_LIGHTS=8;

	  size_t getActiveLightNumber()const;

	  MaterialParam material;

	  struct LightModelParam {
	       Vec4 ambient;//Acs
	  }lightModel;

	  struct LightModelProduct {
	       Vec4 sceneColor;//Ecm+Acm*Acs
	  } lightModelProduct;


	  	  const PerLightParam getPerLightParam(size_t idx)const;

	  void lightf(GLenum lightIndex,
		    GLenum paramName,float param);

	  void lightfv(GLenum lightIndex,
		    GLenum paramName,const float* param,
		    const Matrix4& modelViewMatrix);

	  void lightModelfv(GLenum paramName,const float* param);

	  void materialf(GLenum face,GLenum paramName,float param);

	  void materialfv(GLenum face,GLenum paramName,const float* param);

	  void enable(GLenum lightIndex);

	  void disable(GLenum lightIndex);

	  void updateAll();

	  private:

	  LightSourceParam _allLightSourceParams[MAX_LIGHTS];
	  LightProducts _allLightProducts[MAX_LIGHTS];

	  vector<size_t> _activeIndices;

	  /* data */
     } /* optional variable list */;

} /* my_gl */


#endif /* end of include guard: GROUP_LIGHTING_PARAM_HPP */
