/*
 * =====================================================================================
 *
 *       Filename:  SimpleLineRasterizer.hpp
 *
 *    Description:  use simple float division to rasterize line segment
 *
 *        Version:  1.0
 *        Created:  2011-10-20 22:12:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SIMPLE_LINE_RASTERIZER_HPP

#define SIMPLE_LINE_RASTERIZER_HPP

#include "LineRasterizer.hpp"

namespace my_gl {
     class SimpleLineRasterizer :public LineRasterizer{
     public:
	  ~SimpleLineRasterizer();

     protected:
     	virtual void rasterize
	     (ConstAttributeGroupRef& vertexAttribute1,
	      ConstAttributeGroupRef& vertexAttribute2,
	      WindowCoordinates windowPos1,
	      WindowCoordinates windowPos2,
	      FragmentAttributeBuffer& fragmentAttributeBuffer,
	      const Interpolator& interpolator);


     };
	
} /* my_gl */


#endif /* end of include guard: SIMPLE_LINE_RASTERIZER_HPP */
