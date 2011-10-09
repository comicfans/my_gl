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

#include <vector>

namespace my_gl {

     using std::vector;
     using std::size_t;


     typedef vector<size_t> PrimitiveIndex;

     class VertexAttributeBuffer;
     class ClippedVertexAttributeBuffer;

     class Clipper {
     public:

	  virtual void clip
	       (const VertexAttributeBuffer& projectedDataBuffer,
		const PrimitiveIndex& originalPrimitiveIndex,
		PrimitiveIndex& clippedPrimitiveIndex,
		ClippedVertexAttributeBuffer& clippedVertexAttributeBuffer)=0;

     	virtual ~Clipper ();
     
     };
	
} /* my_gl */


#endif /* end of include guard: CLIPPER_HPP */
