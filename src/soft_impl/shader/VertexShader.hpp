/*
 * =====================================================================================
 *
 *       Filename:  VertexShader.hpp
 *
 *    Description:  vertex shader
 *
 *        Version:  1.0
 *        Created:  2011-9-28 20:24:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VERTEX_SHADER_HPP

#define VERTEX_SHADER_HPP

#include <vector>

#include "Enum.hpp"

#include "VertexAttributeBuffer.hpp"

namespace my_gl {

     struct Vec4;
     struct Global;
     struct LightSourceParam;
     struct MaterialParam;

     using std::vector;

     class VertexShader {
	  public:

	       VertexShader(const Global& global,
			 const vector<LightSourceParam*>& activeLightSourceParams,
			 const MaterialParam& materialParam);

	       virtual ~VertexShader ();

	       virtual void shade(const Vec4* inputAttributes,
			 AttributeGroupRef outputAttributes);

	  protected:

	       virtual void shade(

			 const Vec4& inVertex,
			 const Vec4& inColor,
			 const Vec4& inNormal,
			 const Vec4& inTexCoord,

			 Vec4& outPosition,
			 Vec4& outPointSize,
			 Vec4& outFrontColor,
			 Vec4& outBackColor,
			 Vec4& outTexCoord
			 )=0;

	  protected:
	       const Global& _global;
	       const vector<LightSourceParam*>& _activeLightSourceParams;
	       const MaterialParam& _materialParam;

     };

} /* my_gl */



#endif /* end of include guard: VERTEX_SHADER_HPP */
