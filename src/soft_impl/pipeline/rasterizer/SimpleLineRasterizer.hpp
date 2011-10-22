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

	  SimpleLineRasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer);

	  ~SimpleLineRasterizer();

     protected:

	virtual void rasterize
	     (const WindowCoordinates& coord1,
	      const WindowCoordinates& coord2,
	      const LineInfo& lineInfo,
	      StepCallback stepCallback);



     };
	
} /* my_gl */


#endif /* end of include guard: SIMPLE_LINE_RASTERIZER_HPP */
