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

     PointRasterizer::~PointRasterizer(){}
     PointRasterizer::PointRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer)
	       :Rasterizer
		(viewportParameter,interpolator,fragmentAttributeBuffer){}


	void PointRasterizer::rasterizePoint(
		  ConstAttributeGroupRef& attributeGroup,
		  FragmentAttributeBuffer& fragmentAttributeBuffer,
		  WindowCoordinates winCoord)
	{
	  //TODO currently point size is not implement

	  auto toWrite=fragmentAttributeBuffer.
	       writeNewFragment(winCoord);
	       
	  toWrite=attributeGroup;

	  viewportCorrect(toWrite
		    [VertexAttributeBuffer::OutIndex::POSITION],
		    winCoord);
	}



     void PointRasterizer::elementRasterize
	   (ConstAttributeGroupRef *attributeGroupRefs)
     {

	  auto coordinates=
	       getVertex(attributeGroupRefs[0]);

	  //do perspective division first
	  coordinates/=coordinates.w();

	  auto winCoord=toWindowCoordinates(coordinates);

	  rasterizePoint(attributeGroupRefs[0],
		    _fragmentAttributeBuffer,winCoord);
    }
	
} /* my_gl */
