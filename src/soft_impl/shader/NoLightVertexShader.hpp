/*
 * =====================================================================================
 *
 *       Filename:  NoLightVertexShader.hpp
 *
 *    Description:  vertex shader that require no light
 *
 *        Version:  1.0
 *        Created:  2011-9-29 17:42:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef NO_LIGHT_VERTEX_SHADER_HPP

#define NO_LIGHT_VERTEX_SHADER_HPP

#include "VertexShader.hpp"

namespace my_gl {
     class NoLightVertexShader : public  VertexShader{
     public:

	  NoLightVertexShader(const Global& global,
			 const vector<LightSourceParam*>& activeLightSourceParams,
			 const MaterialParam& materialParam);

	  virtual void shade(

		    const Vec4& inVertex,
		    const Vec4& inColor,
		    const Vec4& inNormal/*not used*/,
		    const Vec4& inTexCoord,

		    Vec4& outPosition,
		    Vec4& outPointSize,
		    Vec4& outFrontColor,
		    Vec4& outBackColor /*not used*/,
		    Vec4& outTexCoord
		    );



	  virtual ~NoLightVertexShader();

     private:
     };

} /* my_gl */



#endif /* end of include guard: NO_LIGHT_VERTEX_SHADER_HPP */
