/*
 * =====================================================================================
 *
 *       Filename:  PointRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-19 13:42:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "PointRasterizer.hpp"

#include "ViewportParameter.hpp"
#include "shader/VertexAttributeBuffer.hpp"
#include "shader/FragmentAttributeBuffer.hpp"

namespace my_gl {


     void PointRasterizer::elementRasterize
	   (ConstAttributeGroupRef *attributeGroupRefs, 
	   FragmentAttributeBuffer &fragmentAttributeBuffer)
     {

	  auto coordinates=
	       getVertex(attributeGroupRefs[0]);

	  //do perspective division first
	  coordinates/=coordinates.w();

	  auto windowCoordinates=viewportCorrect(
		    coordinates);

	  //TODO currently point size is not implement

	  auto toWrite=fragmentAttributeBuffer
	       (windowCoordinates);
	       
	  toWrite=attributeGroupRefs[0];

	  toWrite[VertexAttributeBuffer::OutIndex::POSITION]
	       =coordinates;
     }
	
} /* my_gl */
