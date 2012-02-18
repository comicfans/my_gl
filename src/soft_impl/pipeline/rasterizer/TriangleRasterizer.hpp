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

#include "PerElementRasterizer.hpp"
#include "Enum.hpp"

namespace my_gl {

     using std::unique_ptr;

     class LineRasterizer;

     class TriangleRasterizer :public PerElementRasterizer{
	  public:

	       TriangleRasterizer
		    (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange,
		LineRasterizer *pLineRasterizer);

	       virtual ~TriangleRasterizer ();

	       void setLineRasterizer(LineRasterizer *pLineRasterizer);

	       void enableCullFace();

	       void disableCullFace();

	       void frontFace(GLenum faceMode);

	       void cullFace(GLenum face);

	  protected:

	       virtual void elementRasterize
		    (const ConstAttributeGroupRefList& attributeGroupRefs);


	  private:

	       bool isCulled(const ConstAttributeGroupRefList& 
			 attributeGroupRefs)const;

	       static bool areaSignPositive(const WinCoord points[3]);

	       LineRasterizer *_pLineRasterizer;

	       GLenum _cullFaceMode;

	       bool _cullFaceEnabled;

	       GLenum _cullFace;

	       GLenum _frontFaceMode;
     };

} /* my_gl */

#endif /* end of include guard: TRIANGLE_RASTERIZER_HPP */

