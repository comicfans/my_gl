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

namespace my_gl {

     Rasterizer::Rasterizer
	       (ViewportParameter& viewportParameter,
		Interpolator& interpolator,
		FragmentAttributeBuffer& fragmentAttributeBuffer)
	  :_viewportParameter(viewportParameter),
	  _interpolator(interpolator),
	  _fragmentAttributeBuffer(fragmentAttributeBuffer)
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

	  assert(clippedPrimitiveGroup.elementNumber()==
		    _fragmentAttributeBuffer.attributeNumber());

	  auto& primitiveIndex=
	       clippedPrimitiveGroup.getPrimitiveIndex();


	  int globalIndex=0;
	  for (int elementCounter=0; 
		    elementCounter<primitiveIndex.elementNumber(); 
		    ++elementCounter)
	  {

	       for(int vertexCounter=0;
			 vertexCounter<primitiveIndex.vertexPerPrimitive();
			 ++vertexCounter,++globalIndex)
	       {
		    _attributeGroupRefs.replace(vertexCounter,new 
			      ConstAttributeGroupRef(
				   clippedPrimitiveGroup[globalIndex]));
	       }
	       //do element rasterize
	       elementRasterize(
			 &_attributeGroupRefs[0]);
	  }

     }

     void Rasterizer::setViewportParameter
	  (ViewportParameter& setValue)
	  {
	       _viewportParameter=setValue;

	  }

     int Rasterizer::roundNearest(float value)
     {
	  //0.5 up down/splite
	  return int(value+0.5);
     }

     static inline int viewportCorrectImpl
	  (float normalizedDeviceCoordinate,
	   int begin,int length)
	  {
	       float value=(normalizedDeviceCoordinate+1)
		    *(length/2)+begin;

	       //see gl spec Basic Line Segment Rasterization
	       //"diamond - exit" rule
	       return Rasterizer::roundNearest(value);
	  }

     WindowCoordinates Rasterizer::toWindowCoordinates
	  (const Vec4& normalizedDeviceCoordinates)const
	  {
	       WindowCoordinates ret;

	       ret.first=viewportCorrectImpl(
			 normalizedDeviceCoordinates.x(),
			 _viewportParameter.x,
			 _viewportParameter.width);

	       ret.second=viewportCorrectImpl(
			 normalizedDeviceCoordinates.y(),
			 _viewportParameter.y,
			 _viewportParameter.height);

	       return ret;
	  }

     void Rasterizer::viewportCorrect(Vec4& toCorrect,
	       const WindowCoordinates& windowCoordinates)
     {
	  toCorrect[0]=windowCoordinates[0];
	  toCorrect[1]=windowCoordinates[1];
     }



} /* my_gl */
