/*
 * =====================================================================================
 *
 *       Filename:  Rasterizer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-19 1:16:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Rasterizer.hpp"

#include <cmath>

#include "pipeline/interpolator/Interpolator.hpp"
#include "shader/FragmentAttributeBuffer.hpp"
#include "DepthRange.hpp"
#include "pipeline/DepthBuffer.hpp"

namespace my_gl {

     using std::nearbyint;

     Rasterizer::Rasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer,
		     DepthBuffer& depthBuffer,
		     DepthRange& depthRange)
	  :_viewportParameter(viewportParameter),
	  _interpolator(interpolator),
	  _fragmentAttributeBuffer(fragmentAttributeBuffer),
	  _depthBuffer(depthBuffer),
	  _depthRange(depthRange)
     { }


     void Rasterizer::setInterpolator(Interpolator& interpolator)
     {
	  _interpolator=interpolator;
     }

     void Rasterizer::setFragmentAttributeBuffer
	  (FragmentAttributeBuffer& fragmentAttributeBuffer)
	  {_fragmentAttributeBuffer=fragmentAttributeBuffer;}


     Rasterizer::~Rasterizer(){}
	       


     template<typename T=int>
     static inline double viewportCorrectImpl
	  (float normalizedDeviceCoordinate,
	   T begin,T length)
	  {
	       double value=(normalizedDeviceCoordinate+1)
		    *(length/2)+begin;

	       return value;
	  }

     bool Rasterizer::earlyZTest(const WinCoord& winCoord)
     {
	  return _depthBuffer.testAndUpdate(winCoord);
     }

     WinCoord Rasterizer::toWinCoord
	  (const Vec4& normalizedDeviceCoordinates)const
	  {
	       WinCoord ret;
	       //see gl spec Basic Line Segment Rasterization
	       //"diamond - exit" rule

	       ret.y()=nearbyint(
			 viewportCorrectImpl<int>(
			 normalizedDeviceCoordinates.y(),
			 _viewportParameter.y,
			 _viewportParameter.height));


	       ret.x()=nearbyint(
			 viewportCorrectImpl<int>(
			 normalizedDeviceCoordinates.x(),
			 _viewportParameter.x,
			 _viewportParameter.width));

	       ret.z()=viewportCorrectImpl<double>(normalizedDeviceCoordinates.z(),
			 _depthRange.nearValue,
			 _depthRange.diff);

	       return ret;
	  }

     void Rasterizer::viewportCorrect(Vec4& toCorrect,
	       const WinCoord& windowCoordinates)
     {
	  toCorrect[0]=windowCoordinates.x();
	  toCorrect[1]=windowCoordinates.y();
	  toCorrect[2]=windowCoordinates.z();
     }



} /* my_gl */
