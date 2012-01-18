/*
 * =====================================================================================
 *
 *       Filename:  PerElementRasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-18 14:18:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "PerElementRasterizer.hpp"

#include "pipeline/ClippedPrimitiveGroup.hpp"
#include "shader/FragmentAttributeBuffer.hpp"

namespace my_gl {
	 	      
     PerElementRasterizer::PerElementRasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange)
		    :Rasterizer(viewportParameter,
			      interpolator,fragmentAttributeBuffer,
			      depthBuffer,depthRange)
		    {}

     PerElementRasterizer::~PerElementRasterizer(){}
	
     void PerElementRasterizer::rasterize(
	       const ClippedPrimitiveGroup& clippedPrimitiveGroup)
     {

	  assert(clippedPrimitiveGroup.attributeNumber()==
		    _fragmentAttributeBuffer.attributeNumber());

	  auto& primitiveIndex=
	       clippedPrimitiveGroup.getPrimitiveIndex();

	  int vertexPerPrimitive=primitiveIndex.vertexPerPrimitive();

	  int globalCounter=0;
	  for (size_t elementCounter=0; 
		    elementCounter<primitiveIndex.elementNumber(); 
		    ++elementCounter)
	  {

	       ConstAttributeGroupRefList 
		    attributeGroupRefs(vertexPerPrimitive);

	       for(int vertexCounter=0;
			 vertexCounter<vertexPerPrimitive;
			 ++vertexCounter,++globalCounter)
	       {
		    int globalIndex=primitiveIndex[globalCounter];
		    attributeGroupRefs.push_back(new 
			      ConstAttributeGroupRef(
				   clippedPrimitiveGroup[globalIndex]));
	       }
	       //do element rasterize
	       elementRasterize(attributeGroupRefs);
	  }

     }


} /* my_gl */
