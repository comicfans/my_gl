/*
 * =====================================================================================
 *
 *       Filename:  Rasterizer.hpp
 *
 *    Description:  interface to Rasterizer primitive to 
 *    Frame Buffer input (before FragmentShader)
 *
 *        Version:  1.0
 *        Created:  2011-10-19 1:12:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef RASTERIZER_HPP

#define RASTERIZER_HPP


#include <boost/ptr_container/ptr_array.hpp>

#include "shader/VertexAttributeBuffer.hpp"

#include "ViewportParameter.hpp"
#include "WindowCoordinates.hpp"

namespace my_gl {

     using boost::ptr_array;

     class ClippedPrimitiveGroup;
     class FragmentAttributeBuffer;
     class Interpolator;

     class Rasterizer {
     public:

	  Rasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer);

	  void rasterize(
		    const ClippedPrimitiveGroup& clippedPrimitiveGroup);

	  /** 
	   * @brief use this function to change viewport parameter
	   * make it as a super class function for that sub-class
	   * only need to calculate the WindowCoordinates but not 
	   * need the viewport parameter
	   * 
	   * @param setValue
	   */
	  void setViewportParameter(ViewportParameter& setValue);

	  void setInterpolator(Interpolator& interpolator);

	  void setFragmentAttributeBuffer
	       (FragmentAttributeBuffer& fragmentAttributeBuffer);

	  virtual ~Rasterizer();

	  static int roundNearest(float value);

	  static void viewportCorrect(Vec4& toCorrect,
		    const WindowCoordinates& windowCoordinates);


     protected:

	  /** 
	   * @brief per-element rasterize,such as 
	   * point/line segment/triangle
	   * super class function rasterize use the 
	   * primitive information of PrimitiveIndex
	   * to determine how many vertex should be 
	   * grouped as a element
	   * 
	   * @param attributeGroupRefs attributeGroup of element vertex
	   * @param fragmentAttributeBuffer buffer to write fragment input
	   * 
	   * @return 
	   */
	  virtual void elementRasterize
	       (ConstAttributeGroupRef* attributeGroupRefs)=0;

	  WindowCoordinates toWindowCoordinates
	       (const Vec4& normalizedDeviceCoordinates)const;


	  FragmentAttributeBuffer& _fragmentAttributeBuffer;

	  Interpolator& _interpolator;

     private:

	  ptr_array<ConstAttributeGroupRef,
	       VertexAttributeBuffer::MAX_VERTEX_PER_ELEMENT>
		    _attributeGroupRefs;

	  ViewportParameter& _viewportParameter;

     };
	
} /* my_gl */


#endif /* end of include guard: RASTERIZER_HPP */
