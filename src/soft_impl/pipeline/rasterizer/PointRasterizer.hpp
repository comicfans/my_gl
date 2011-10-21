/*
 * =====================================================================================
 *
 *       Filename:  PointRasterizer.hpp
 *
 *    Description:  class to rasterize point
 *
 *        Version:  1.0
 *        Created:  2011-10-19 13:38:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef POINT_RASTERIZER_HPP

#define POINT_RASTERIZER_HPP

#include "Rasterizer.hpp"

namespace my_gl {

     class PointRasterizer :public Rasterizer{
     public:
     	virtual ~PointRasterizer ();

	static void rasterizePoint(
		  ConstAttributeGroupRef& attributeGroup,
		  FragmentAttributeBuffer& fragmentAttributeBuffer,
		  WindowCoordinates winCoord);

     protected:
	  virtual void elementRasterize
		(ConstAttributeGroupRef* attributeGroupRefs,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		const Interpolator& interpolator)=0;
     };
	
} /* my_gl */



#endif /* end of include guard: POINT_RASTERIZER_HPP */
