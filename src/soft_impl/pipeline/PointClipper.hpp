/*
 * =====================================================================================
 *
 *       Filename:  PointClipper.hpp
 *
 *    Description:  clipper to clip point
 *
 *        Version:  1.0
 *        Created:  2011-10-9 21:30:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef POINT_CLIPPER_HPP

#define POINT_CLIPPER_HPP

#include "Clipper.hpp"

namespace my_gl {

     class PointClipper {
     public:

     	virtual ~PointClipper ();

	virtual void clip
	       (const VertexAttributeBuffer& projectedDataBuffer,
		const PrimitiveIndex& originalPrimitiveIndex,
		PrimitiveIndex& clippedPrimitiveIndex,
		ClippedVertexAttributeBuffer& clippedVertexAttributeBuffer);


     };
	
} /* my_gl */


#endif /* end of include guard: POINT_CLIPPER_HPP */
