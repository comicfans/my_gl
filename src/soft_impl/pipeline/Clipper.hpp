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

namespace my_gl {


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
	       (size_t attributeNumber,
		const Vec4 ** attributeGroups,
		const size_t *vertexIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup)=0;

	  const Vec4& getVertex(const Vec4**,size_t index);

     private:

	  const Vec4 *_attributeGroups[MAX_VERTEX_PER_ELEMENT];
	  size_t _vertexIndex[MAX_VERTEX_PER_ELEMENT];
     
     };
	
} /* my_gl */


#endif /* end of include guard: CLIPPER_HPP */
