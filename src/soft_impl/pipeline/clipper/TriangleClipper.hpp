/*
 * =====================================================================================
 *
 *       Filename:  TriangleClipper.hpp
 *
 *    Description:  clipper to clip triangle
 *
 *        Version:  1.0
 *        Created:  2011-10-16 11:31:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TRIANGLE_CLIPPER_HPP

#define TRIANGLE_CLIPPER_HPP

#include "Clipper.hpp"

namespace my_gl {

     class TriangleClipper :public Clipper{
     public:

     	virtual ~TriangleClipper ();
     protected:
	  virtual void elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);




     private:
     	/* data */
     };
	
} /* my_gl */


#endif /* end of include guard: TRIANGLE_CLIPPER_HPP */
