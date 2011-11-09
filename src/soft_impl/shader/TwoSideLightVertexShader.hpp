/*
 * =====================================================================================
 *
 *       Filename:  TwoSideLightVertexShader.hpp
 *
 *    Description:  vertex shader which color two side lighting
 *
 *        Version:  1.0
 *        Created:  2011-11-9 9:37:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TWO_SIDE_LIGHT_VERTEX_SHADER_HPP

#define TWO_SIDE_LIGHT_VERTEX_SHADER_HPP

#include "LightVertexShader.hpp"

namespace my_gl {

     class TwoSideLightVertexShader :public LightVertexShader{
     public:
	  TwoSideLightVertexShader(const MatrixParam& matrixParam,
			 const GroupLightingParam& groupLightParam);
     	
     	virtual ~TwoSideLightVertexShader ();

     protected:
 	  virtual void shade(

		    const Vec4& inVertex,
		    const Vec4& /* not used */,
		    const Vec3& inNormal,
		    const Vec4& inTexCoord,

		    Vec4& outPosition,
		    Vec4& outPointSize,
		    Vec4& outFrontColor,
		    Vec4& outBackColor ,
		    Vec4& outTexCoord
		    );

    
     };
	
} /* my_gl */



#endif /* end of include guard: TWO_SIDE_LIGHT_VERTEX_SHADER_HPP */
