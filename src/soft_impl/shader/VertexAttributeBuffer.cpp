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

namespace my_gl {

     using boost::extents;

     size_t VertexAttributeBuffer::elementNumber()const
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
		    [length][attributeNumber()]);
     }

     AttributeGroupRef VertexAttributeBuffer::back()
     {
	  return (*this)[elementNumber()-1];
     }

     const Vec4& getVertex(
	       const ConstAttributeGroupRef& attributeGroup)
     {
	return attributeGroup[int(
		  VertexAttributeBuffer::OutIndex::POSITION)];
     }

     Vec4& getVertex(
	       AttributeGroupRef attributeGroup)
     {
	  return attributeGroup[int(
		    VertexAttributeBuffer::OutIndex::POSITION)];
     }

} /* my_gl */
