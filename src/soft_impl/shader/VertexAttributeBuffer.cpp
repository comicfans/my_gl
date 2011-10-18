/*
 * =====================================================================================
 *
 *       Filename:  VertexAttributeBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-6 13:36:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "VertexAttributeBuffer.hpp"

#include "VertexShader.hpp"

namespace my_gl {

     using boost::extents;

     size_t VertexAttributeBuffer::length()const
     {
	  return shape()[0];
     }

     size_t VertexAttributeBuffer::attributeNumber()const
     {
	  return shape()[1];
     }

     void VertexAttributeBuffer::resize(size_t length)
     {
	  multi_array<Vec4,2>::resize(extents
		    [length][VertexShader::OUT_SIZE]);
     }

     AttributeGroupRef VertexAttributeBuffer::back()
     {
	  return (*this)[length()-1];
     }

     const Vec4& VertexAttributeBuffer::getVertex(
	       const ConstAttributeGroupRef& attributeGroup)
     {
	return attributeGroup[int(
		  VertexShader::OutIndex::POSITION)];
     }

     Vec4& VertexAttributeBuffer::getVertex(
	       AttributeGroupRef attributeGroup)
     {
	  return attributeGroup[int(
		    VertexShader::OutIndex::POSITION)];
     }

} /* my_gl */
