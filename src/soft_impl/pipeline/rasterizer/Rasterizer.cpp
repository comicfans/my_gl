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

#include "pipeline/ClippedPrimitiveGroup.hpp"
#include "shader/FragmentAttributeBuffer.hpp"
#include "pipeline/interpolator/Interpolator.hpp"
#include "DepthRange.hpp"
#include "pipeline/DepthBuffer.hpp"

namespace my_gl {

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
	       

     void Rasterizer::rasterize(
	       const ClippedPrimitiveGroup& clippedPrimitiveGroup)
     {

	  assert(clippedPrimitiveGroup.attributeNumber()==
		    _fragmentAttributeBuffer.attributeNumber());

	  auto& primitiveIndex=
	       clippedPrimitiveGroup.getPrimitiveIndex();

	  int vertexPerPrimitive=primitiveIndex.vertexPerPrimitive();

	  int globalCounter=0;
	  for (size_t elementCounter=0; 
		    elementCounter<primitiveIndex.elementNumber(); 
		    ++elementCounter)
	  {

	       ConstAttributeGroupRefList 
		    attributeGroupRefs(vertexPerPrimitive);

	       for(int vertexCounter=0;
			 vertexCounter<vertexPerPrimitive;
			 ++vertexCounter,++globalCounter)
	       {
		    int globalIndex=primitiveIndex[globalCounter];
		    attributeGroupRefs.push_back(new 
			      ConstAttributeGroupRef(
				   clippedPrimitiveGroup[globalIndex]));
	       }
	       //do element rasterize
	       elementRasterize(attributeGroupRefs);
	  }

     }

     int Rasterizer::roundNearest(float value)
     {
	  //0.5 up down/splite
	  return int(value+0.5);
     }

     template<typename T=int>
     static inline float viewportCorrectImpl
	  (float normalizedDeviceCoordinate,
	   T begin,T length)
	  {
	       float value=(normalizedDeviceCoordinate+1)
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

	       ret.y()=Rasterizer::roundNearest(
			 viewportCorrectImpl<int>(
			 normalizedDeviceCoordinates.y(),
			 _viewportParameter.y,
			 _viewportParameter.height));


	       ret.x()=Rasterizer::roundNearest(
			 viewportCorrectImpl<int>(
			 normalizedDeviceCoordinates.x(),
			 _viewportParameter.x,
			 _viewportParameter.width));

	       ret.z()=viewportCorrectImpl(normalizedDeviceCoordinates.z(),
			 _depthRange.near,
			 _depthRange.far-_depthRange.near);

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
