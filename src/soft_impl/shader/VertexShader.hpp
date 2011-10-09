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

#include "Enum.hpp"

namespace my_gl {

     struct Vec4;
     struct Global;
     class VertexShader {
     public:
     	virtual ~VertexShader ();

	virtual void shade(const Global& global,
		  const Vec4 *inputAttributes,
		  Vec4 *outputAttributes);

	enum OutIndex{POSITION,POINT_SIZE,
	FRONT_COLOR,BACK_COLOR,TEXCOORD};

	const static int OUT_SIZE=5;
	const static int IN_SIZE=4;

     protected:

	virtual void shade(
		  const Global& global,

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
     
     };
	
} /* my_gl */



#endif /* end of include guard: VERTEX_SHADER_HPP */
