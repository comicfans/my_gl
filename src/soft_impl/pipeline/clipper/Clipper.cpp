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

#include <boost/ptr_container/ptr_array.hpp>

#include "pipeline/PrimitiveIndex.hpp"

#include "shader/VertexAttributeBuffer.hpp"

#include "shader/VertexShader.hpp"

namespace my_gl {

     using boost::ptr_array;

     Clipper::~Clipper(){}

     void Clipper::clip
	  (const VertexAttributeBuffer& projectedDataBuffer,
	   const PrimitiveIndex& originalPrimitiveIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {
	       int globalCounter=0;

	       ptr_array<ConstAttributeGroupRef,
	       VertexAttributeBuffer::MAX_VERTEX_PER_ELEMENT> 
		    _attributeGroups;

	       size_t _vertexIndex[
	       VertexAttributeBuffer::MAX_VERTEX_PER_ELEMENT];
 

	       for(size_t elementCounter=0;
			 elementCounter<originalPrimitiveIndex.elementNumber();
			 ++elementCounter)
	       {

		    for(size_t perElementIndex=0;
			      perElementIndex<originalPrimitiveIndex.vertexPerPrimitive() ;
			      ++perElementIndex,++globalCounter)
		    {

			 _vertexIndex[perElementIndex]=globalCounter;

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



} /* my_gl */
