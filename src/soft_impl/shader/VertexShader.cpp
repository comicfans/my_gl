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

#include "common/Vec.hpp"

#include "common/Matrix.hpp"

#include "MatrixParam.hpp"

#include "lighting/GroupLightingParam.hpp"

namespace my_gl {

     VertexShader::VertexShader(const MatrixParam& matrixParam,
	       const GroupLightingParam& groupLightingParam)
	  :_matrixParam(matrixParam),
	  _groupLightingParam(groupLightingParam)
     {
     }

     VertexShader::~VertexShader(){}

	       
     Vec4 VertexShader::ftransform(const Vec4& inVertex)
     {
	  return _matrixParam.modelViewProjection*inVertex;
     }
	       
     void VertexShader::enable(NormalizeNormal normalizeNormal)
     {

	  switch(normalizeNormal)
	  {
	       case NormalizeNormal::NORMALIZE:
		    _normalizeNormal=true;
		    break;
	       case NormalizeNormal::RESCALE_NORMAL:
		    _rescaleNormal=true;
		    break;
	  }
     }

     void VertexShader::disable(NormalizeNormal normalizeNormal)
     {
	  switch(normalizeNormal)
	  {
	       case NormalizeNormal::NORMALIZE:
		    _normalizeNormal=false;
		    break;
	       case NormalizeNormal::RESCALE_NORMAL:
		    _rescaleNormal=false;
		    break;
	  }
     }


     Vec3 VertexShader::fnormal(const Vec3& inNormal)
     {
	  Vec3 ret=_matrixParam.normal*Vec3(inNormal.values(),3);

	  if (_rescaleNormal)
	  {
	       //TODO
	  }
	  if (_normalizeNormal)
	  {
	       normalize(ret);
	  }

	  return ret;
     }

     void VertexShader::shade
	  (const Vec4* inputAttributes,
	   AttributeGroupRef outputAttributes)
	  {
	       shade(
			 inputAttributes[int(BindState::VERTEX)],
			 inputAttributes[int(BindState::COLOR)],
			 Vec3(inputAttributes[int(BindState::NORMAL)].values(),3),
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
