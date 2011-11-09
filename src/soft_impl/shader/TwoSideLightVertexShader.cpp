/*
 * =====================================================================================
 *
 *       Filename:  TwoSideLightVertexShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-9 9:40:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TwoSideLightVertexShader.hpp"

namespace my_gl {
	 	  void TwoSideLightVertexShader::shade(

		    const Vec4& inVertex,
		    const Vec4& /* not used */,
		    const Vec3& inNormal,
		    const Vec4& inTexCoord,

		    Vec4& outPosition,
		    Vec4& outPointSize,
		    Vec4& outFrontColor,
		    Vec4& outBackColor ,
		    Vec4& outTexCoord
		    )
		  {
		       outFrontColor=singleSideLighting(inVertex,inNormal);
		       outBackColor=singleSideLighting(inVertex,-inNormal);
		       outPosition=ftransform(inVertex);

		  }


} /* my_gl */
