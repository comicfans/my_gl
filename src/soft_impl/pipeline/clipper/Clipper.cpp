/*
 * =====================================================================================
 *
 *       Filename:  Clipper.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-9 21:19:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Clipper.hpp"

#include "pipeline/PrimitiveIndex.hpp"

#include "shader/VertexAttributeBuffer.hpp"

#include "shader/VertexShader.hpp"

namespace my_gl {

     Clipper::~Clipper(){}

     void Clipper::clip
	  (const VertexAttributeBuffer& projectedDataBuffer,
	   const PrimitiveIndex& originalPrimitiveIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {
	       int globalCounter=0;


	       for(int elementCounter=0;
			 elementCounter<originalPrimitiveIndex.elementNumber();
			 ++elementCounter)
	       {

		    for(int perElementIndex=0;
			      perElementIndex<originalPrimitiveIndex.vertexPerPrimitive() ;
			      ++perElementIndex,++globalCounter)
		    {

			      _attributeGroups.replace(perElementIndex,
					new ConstAttributeGroupRef(
					     projectedDataBuffer[
				   originalPrimitiveIndex[globalCounter]]));
		    }


		    elementClip
			 (&_attributeGroups[0],
			  _vertexIndex,
			  clippedPrimitiveGroup);
		    //else clipped
	       }


	  }


     const Vec4& Clipper::getVertex(
	       const ConstAttributeGroupRef& attributeGroup)
     {

	return attributeGroup[int(VertexShader::OutIndex::POSITION)];
     }

} /* my_gl */
