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

#include "shader/VertexAttributeBuffer.hpp"
#include "shader/FragmentAttributeBuffer.hpp"

namespace my_gl {

     PointRasterizer::~PointRasterizer(){}
     PointRasterizer::PointRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange)
	       :PerElementRasterizer
		(viewportParameter,interpolator,
		 fragmentAttributeBuffer,depthBuffer,depthRange){}


	void PointRasterizer::rasterizePoint(
		  const ConstAttributeGroupRef& attributeGroup,
		  FragmentAttributeBuffer& fragmentAttributeBuffer,
		  WinCoord winCoord)
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
	   (const ConstAttributeGroupRefList &attributeGroupRefs)
     {

	  auto coordinates=
	       getVertex(attributeGroupRefs[0]);

	  //do perspective division first
	  coordinates/=coordinates.w();

	  auto winCoord=toWinCoord(coordinates);

	  if (earlyZTest(winCoord.z()))
	  {
	       rasterizePoint(attributeGroupRefs[0],
		    _fragmentAttributeBuffer,winCoord);
	  }

}
	
} /* my_gl */
