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

#include <cassert>
#include <cstddef>


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

	       size_t vertexPerPrimitive=originalPrimitiveIndex.vertexPerPrimitive();

	       ptr_vector<ConstAttributeGroupRef> 
		    _attributeGroups(vertexPerPrimitive);

	       size_t _vertexIndex[
	       VertexAttributeBuffer::MAX_VERTEX_PER_ELEMENT];
 
		    
	       for(size_t elementCounter=0;
			 elementCounter<vertexPerPrimitive;
			 ++elementCounter)
	       {

		    for(size_t perElementIndex=0;
			      perElementIndex<originalPrimitiveIndex.vertexPerPrimitive() ;
			      ++perElementIndex,++globalCounter)
		    {
			 int globalIndex=originalPrimitiveIndex[globalCounter];

			 _vertexIndex[perElementIndex]=globalIndex;

			 _attributeGroups.replace(perElementIndex,
					new ConstAttributeGroupRef(
					     projectedDataBuffer[globalIndex]));
		    }




		    elementClip
			 (_attributeGroups,
			  _vertexIndex,
			  clippedPrimitiveGroup);
		    //else clipped
	       }


	  }



} /* my_gl */
