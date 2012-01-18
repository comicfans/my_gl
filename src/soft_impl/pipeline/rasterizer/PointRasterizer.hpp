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

#include "PerElementRasterizer.hpp"

namespace my_gl {

     class PointRasterizer :public PerElementRasterizer{
     public:
     	virtual ~PointRasterizer ();
	  PointRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange);


	static void rasterizePoint(
		  const ConstAttributeGroupRef& attributeGroup,
		  FragmentAttributeBuffer& fragmentAttributeBuffer,
		  WinCoord winCoord);

     protected:
	  virtual void elementRasterize
		(const ConstAttributeGroupRefList& attributeGroupRefs);
     };
	
} /* my_gl */



#endif /* end of include guard: POINT_RASTERIZER_HPP */
