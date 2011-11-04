/*
 * =====================================================================================
 *
 *       Filename:  GroupLightingParam.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-2 16:08:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "GroupLightingParam.hpp"

#include <algorithm>
#include <cassert>

using std::remove;

namespace my_gl {

     
     PerLightParam::PerLightParam
		    (const LightSourceParam& lightSourceParamSet,
		     const LightProducts& lightProductSet)
		    :lightSourceParam(lightSourceParamSet),
		    lightProduct(lightProductSet){}


	  const PerLightParam
	       GroupLightingParam::
	       getPerLightParam(size_t idx)const
	       {
		    assert(idx<_activeIndices.size());

		    int directIdx=_activeIndices[idx];

		    return PerLightParam(
			      _allLightSourceParams[directIdx],
			      _allLightProducts[directIdx]);
	       }

		
	  size_t GroupLightingParam::getActiveLightNumber()const
	  {
	       return _activeIndices.size();
	  }

	  void GroupLightingParam::enable(LightIndex lightIndex)
	{
	     //check LIGHTING enabled is outside work

	     int idx=int(lightIndex);

	     assert(idx<MAX_LIGHTS);

	     if (find(_activeIndices.begin(),_activeIndices.end(),idx)
		       ==_activeIndices.end())
	     {
		  _activeIndices.push_back(idx);
	     }
	}

	void GroupLightingParam::disable(LightIndex lightIndex)
	{
	     auto removeEndIt=remove(_activeIndices.begin(),
		       _activeIndices.end(),int(lightIndex));

	     _activeIndices.resize
		  (_activeIndices.end()-removeEndIt);
	}

	  void GroupLightingParam::lightf(LightIndex lightIndex,
		    LightParamName paramName,float param)
	  {
	       _allLightSourceParams[int(lightIndex)]
		    .lightf(paramName,param);
	  }

	  void GroupLightingParam::lightfv(LightIndex lightIndex,
		    LightParamName paramName,const float* param)
	  {
	       _allLightSourceParams[int(lightIndex)]
		    .lightfv(paramName,param);
	  }

	  void GroupLightingParam::materialf(Face face,
		    LightParamName paramName,float param)
	  {
	       material.materialf(face,paramName,param);
	  }

	  void GroupLightingParam::materialfv(Face face,
		    LightParamName paramName,const float* param)
	  {
	       material.materialfv(face,paramName,param);
	  }

	  void GroupLightingParam::updateAll()
	  {
	       lightModelProduct.sceneColor=material.emission+
		    componentMul(material.ambient,lightModel.ambient);

	       for(auto i:_activeIndices)
	       {
		    //Acm * Acli
		    _allLightProducts[i].ambient=componentMul
			 (material.ambient,_allLightSourceParams[i].ambient);

		    //Dcm * Dcli
		    _allLightProducts[i].diffuse=componentMul
			 (material.diffuse,_allLightSourceParams[i].diffuse);

		    //Scm * Scli
		    _allLightProducts[i].specular=componentMul
			 (material.specular,_allLightSourceParams[i].specular);
	       }
	  }

} /* my_gl */
