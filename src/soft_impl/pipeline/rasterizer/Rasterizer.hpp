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


#include <boost/ptr_container/ptr_vector.hpp>

#include "shader/VertexAttributeBuffer.hpp"

#include "ViewportParameter.hpp"
#include "WinCoord.hpp"

namespace my_gl {

     using boost::ptr_vector;

     class ClippedPrimitiveGroup;
     class FragmentAttributeBuffer;
     class DepthRange;
     class DepthBuffer;
     class Interpolator;

     typedef ptr_vector<ConstAttributeGroupRef> ConstAttributeGroupRefList;

     class Rasterizer {
	  public:

	       Rasterizer
		    (ViewportParameter& viewportParameter,
		     Interpolator& interpolator,
		     FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange);

	       void rasterize(
			 const ClippedPrimitiveGroup& clippedPrimitiveGroup);

	       void setInterpolator(Interpolator& interpolator);

	       void setFragmentAttributeBuffer
		    (FragmentAttributeBuffer& fragmentAttributeBuffer);

	       virtual ~Rasterizer();

	       static void viewportCorrect(Vec4& toCorrect,
			 const WinCoord& windowCoordinates);


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
		    (const ConstAttributeGroupRefList& attributeGroupRefs)=0;

	       WinCoord toWinCoord
		    (const Vec4& normalizedDeviceCoordinates)const;

	       bool earlyZTest(const WinCoord& winCoord);


	  private:

	       const ViewportParameter& _viewportParameter;
	  protected:
	       Interpolator& _interpolator;
	       FragmentAttributeBuffer& _fragmentAttributeBuffer;
	  private:
	       DepthBuffer& _depthBuffer;
	       const DepthRange& _depthRange;




     };

} /* my_gl */


#endif /* end of include guard: RASTERIZER_HPP */
