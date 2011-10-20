/*
 * =====================================================================================
 *
 *       Filename:  Rasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-19 1:16:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Rasterizer.hpp"
#include "pipeline/ClippedPrimitiveGroup.hpp"

namespace my_gl {

	
     Rasterizer::~Rasterizer(){}

	  void Rasterizer::rasterize(
		    const ClippedPrimitiveGroup& clippedPrimitiveGroup,
		    FragmentAttributeBuffer& fragmentAttributeBuffer)
	  {
	       auto& primitiveIndex=
		    clippedPrimitiveGroup.getPrimitiveIndex();


	       int globalIndex=0;
	       for (int elementCounter=0; 
			 elementCounter<primitiveIndex.elementNumber(); 
			 ++elementCounter)
	       {

		    for(int vertexCounter=0;
			      vertexCounter<primitiveIndex.vertexPerPrimitive();
			      ++vertexCounter,++globalIndex)
		    {
			 _attributeGroupRefs.replace(vertexCounter,new 
				   ConstAttributeGroupRef(
					clippedPrimitiveGroup[globalIndex]));
		    }
		    //do element rasterize
		    elementRasterize(
			      &_attributeGroupRefs[0],
			      fragmentAttributeBuffer);
	       }

	  }

	  void Rasterizer::setViewportParameter
	       (const ViewportParameter& setValue)
	  {
	       _viewportParameter=setValue;

	  }

	  static inline int viewportCorrectImpl
	       (float normalizedDeviceCoordinate,
		    int begin,int length)
	       {
		    return (normalizedDeviceCoordinate+1)
			 *(length/2)+begin;
	       }

	  WindowCoordinates Rasterizer::viewportCorrect
	       (const Vec4& normalizedDeviceCoordinates)const
	       {
		    WindowCoordinates ret;

		    ret.first=viewportCorrectImpl(
			      normalizedDeviceCoordinates.x(),
			      _viewportParameter.x,
			      _viewportParameter.width);

		    ret.second=viewportCorrectImpl(
			      normalizedDeviceCoordinates.y(),
			      _viewportParameter.y,
			      _viewportParameter.height);

		    return ret;
	       }

} /* my_gl */
