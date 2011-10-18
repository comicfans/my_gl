/*
 * =====================================================================================
 *
 *       Filename:  Clipper.hpp
 *
 *    Description:  interface to clip primitive
 *
 *        Version:  1.0
 *        Created:  2011-10-9 20:51:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CLIPPER_HPP

#define CLIPPER_HPP

#include <cstddef>

#include <boost/ptr_container/ptr_array.hpp>

#include "shader/VertexAttributeBuffer.hpp"


namespace my_gl {


     using boost::ptr_array;
     

     class VertexAttributeBuffer;
     class ClippedPrimitiveGroup;
     class PrimitiveIndex;
     struct Vec4;


     class Clipper {
     public:

	  virtual ~Clipper ();

	  void clip
	       (const VertexAttributeBuffer& projectedDataBuffer,
		const PrimitiveIndex& originalPrimitiveIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);


	  //reserved for quad use, right now only triangle is used
	  static const size_t MAX_VERTEX_PER_ELEMENT=4;

     protected:


	  virtual void elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
	       ClippedPrimitiveGroup& clippedPrimitiveGroup)=0;

     private:

	  ptr_array<ConstAttributeGroupRef,MAX_VERTEX_PER_ELEMENT> _attributeGroups;

	  size_t _vertexIndex[MAX_VERTEX_PER_ELEMENT];
     
     };
	
} /* my_gl */


#endif /* end of include guard: CLIPPER_HPP */
