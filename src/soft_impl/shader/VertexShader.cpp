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

     VertexShader::VertexShader(const Global& global,
	       const vector<LightSourceParam*>& activeLightSourceParams,
	       const MaterialParam& materialParam)
	  :_global(global),
	  _activeLightSourceParams(activeLightSourceParams),
	  _materialParam(materialParam)
     {
     }

     VertexShader::~VertexShader(){}


     void VertexShader::shade
	   (const Vec4* inputAttributes,
	   AttributeGroupRef outputAttributes)
	  {
	       shade(
			 inputAttributes[int(BindState::VERTEX)],
			 inputAttributes[int(BindState::COLOR)],
			 inputAttributes[int(BindState::NORMAL)],
			 inputAttributes[int(BindState::TEXCOORD)],
			 
			 outputAttributes[int(
			      VertexAttributeBuffer::OutIndex::POSITION)],
			 outputAttributes[int(
			      VertexAttributeBuffer::OutIndex::POINT_SIZE)],
			 outputAttributes[int(
			      VertexAttributeBuffer::OutIndex::FRONT_COLOR)],
			 outputAttributes[int(
			      VertexAttributeBuffer::OutIndex::BACK_COLOR)],
			 outputAttributes[int(
			      VertexAttributeBuffer::OutIndex::TEXCOORD)]
			 );
	  }


} /* my_gl */
