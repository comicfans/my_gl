/*
 * =====================================================================================
 *
 *       Filename:  LineRasterizer.hpp
 *
 *    Description:  common interface of LineRasterizer
 *
 *        Version:  1.0
 *        Created:  2011-10-20 20:20:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LINE_RASTERIZER_HPP

#define LINE_RASTERIZER_HPP

#include "Rasterizer.hpp"

namespace my_gl {
     class LineRasterizer :public Rasterizer{
     public:
     	virtual ~LineRasterizer ();

	static void groupAction
	       (const ConstAttributeGroupRef& attributeGroup1,
		const ConstAttributeGroupRef& attributeGroup2,
		const WindowCoordinates& winCoord,
		float percent,
		FragmentAttributeBuffer& fragmentAttributeBuffer);

     protected:

	virtual void elementRasterize
	       (ConstAttributeGroupRef* attributeGroupRefs,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		const Interpolator& interpolator);

	virtual void rasterize
	     (ConstAttributeGroupRef& vertexAttribute1,
	      ConstAttributeGroupRef& vertexAttribute2,
	      WindowCoordinates windowPos1,
	      WindowCoordinates windowPos2,
	      FragmentAttributeBuffer& fragmentAttributeBuffer,
	      const Interpolator& interpolator)=0;

     };
	
} /* my_gl */


#endif /* end of include guard: LINE_RASTERIZER_HPP */
