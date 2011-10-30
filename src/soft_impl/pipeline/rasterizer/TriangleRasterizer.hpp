/*
 * =====================================================================================
 *
 *       Filename:  TriangleRasterizer.hpp
 *
 *    Description:  class to rasterize triangle
 *
 *        Version:  1.0
 *        Created:  2011-10-21 15:41:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TRIANGLE_RASTERIZER_HPP

#define TRIANGLE_RASTERIZER_HPP

#include <memory>

#include "Rasterizer.hpp"

namespace my_gl {

     using std::unique_ptr;

     class LineRasterizer;

     class TriangleRasterizer :public Rasterizer{
	  public:

	       TriangleRasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     FragmentAttributeBuffer& fragmentAttributeBuffer,
		     LineRasterizer *pLineRasterizer);

	       virtual ~TriangleRasterizer ();

	       void setLineRasterizer(LineRasterizer *pLineRasterizer);

	  protected:

	       virtual void elementRasterize
		    (const ConstAttributeGroupRefList& attributeGroupRefs);


	  private:

	       LineRasterizer *_pLineRasterizer;
     };

} /* my_gl */

#endif /* end of include guard: TRIANGLE_RASTERIZER_HPP */

