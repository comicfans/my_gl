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

namespace my_gl {


     void PointRasterizer::elementRasterize
	   (ConstAttributeGroupRef *attributeGroupRefs, 
	   FragmentAttributeBuffer &fragmentAttributeBuffer)
     {
	  auto windowCoordinates-viewportCorrect(
		    getVertex(attributeGroupRefs[0]));
	  //TODO currently point size is not implement

	  fragmentAttributeBuffer(windowCoordinates)

     }
	
} /* my_gl */
