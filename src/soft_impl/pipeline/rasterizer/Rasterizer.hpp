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

#include "soft_impl/shader/VertexAttributeBuffer.hpp"

#include "soft_impl/Rectangle.hpp"
#include "soft_impl/pipeline/rasterizer/WinCoord.hpp"

namespace my_gl {

     using boost::ptr_vector;

     class ClippedPrimitiveGroup;
     class FragmentAttributeBuffer;
     struct DepthRange;
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

	       virtual void rasterize(
			 const ClippedPrimitiveGroup& clippedPrimitiveGroup)=0;

	       void setInterpolator(Interpolator& interpolator);

	       void setFragmentAttributeBuffer
		    (FragmentAttributeBuffer& fragmentAttributeBuffer);

	       virtual ~Rasterizer();

	       static void viewportCorrect(Vec4& toCorrect,
			 const WinCoord& windowCoordinates);

		   //TODO a temp hack,msvc c++ has no nearbyint
		   static int nearbyint(double value);

	  protected:

	       WinCoord toWinCoord
		    (const Vec4& normalizedDeviceCoordinates)const;

	       bool earlyZTest(const WinCoord& winCoord);



	       const ViewportParameter& _viewportParameter;
	       const DepthRange& _depthRange;

	       Interpolator& _interpolator;
	       FragmentAttributeBuffer& _fragmentAttributeBuffer;
	       DepthBuffer& _depthBuffer;




     };

} /* my_gl */


#endif /* end of include guard: RASTERIZER_HPP */
