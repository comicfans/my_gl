/*
 * =====================================================================================
 *
 *       Filename:  LightVertexShader.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-2 12:07:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LIGHT_VERTEX_SHADER_HPP

#define LIGHT_VERTEX_SHADER_HPP

#include "VertexShader.hpp"

namespace my_gl {

     class LightVertexShader :public VertexShader{
     public:
 	  LightVertexShader(const MatrixParam& matrixParam,
			 const GroupLightingParam& groupLightParam);
     	
	  virtual ~LightVertexShader ();

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


#endif /* end of include guard: LIGHT_VERTEX_SHADER_HPP */
