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



#include "shader/VertexAttributeBuffer.hpp"

namespace my_gl {


     

     class ClippedPrimitiveGroup;
     class PrimitiveIndex;

     class Clipper {
     public:

	  virtual ~Clipper ();

	  void clip
	       (const VertexAttributeBuffer& projectedDataBuffer,
		const PrimitiveIndex& originalPrimitiveIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);

     protected:


	  virtual void elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
	       ClippedPrimitiveGroup& clippedPrimitiveGroup)=0;


    
     };
	
} /* my_gl */


#endif /* end of include guard: CLIPPER_HPP */
