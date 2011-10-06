/*
 * =====================================================================================
 *
 *       Filename:  VertexShader.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-28 21:12:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "VertexShader.hpp"

#include "common/Vec4.hpp"

#include "Global.hpp"
namespace my_gl {

     VertexShader::~VertexShader(){}


     void VertexShader::shade
	  (const Global& global,
	   const Vec4 *inputAttributes,
	   Vec4 *outputAttributes)
	  {
	       shade(	 global,
			 inputAttributes[int(BindState::VERTEX)],
			 inputAttributes[int(BindState::COLOR)],
			 inputAttributes[int(BindState::NORMAL)],
			 inputAttributes[int(BindState::TEXCOORD)],
			 
			 outputAttributes[int(OutIndex::POSITION)],
			 outputAttributes[int(OutIndex::POINT_SIZE)],
			 outputAttributes[int(OutIndex::CLIP_VERTEX)],
			 outputAttributes[int(OutIndex::FRONT_COLOR)],
			 outputAttributes[int(OutIndex::BACK_COLOR)],
			 outputAttributes[int(OutIndex::TEXCOORD)]
			 );
	  }


} /* my_gl */
