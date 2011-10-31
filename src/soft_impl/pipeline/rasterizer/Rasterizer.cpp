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

     WinCoord Rasterizer::toWinCoord
	  (const Vec4& normalizedDeviceCoordinates)const
	  {
	       WinCoord ret;

	       ret.first=viewportCorrectImpl(
			 normalizedDeviceCoordinates.y(),
			 _viewportParameter.y,
			 _viewportParameter.height);


	       ret.second=viewportCorrectImpl(
			 normalizedDeviceCoordinates.x(),
			 _viewportParameter.x,
			 _viewportParameter.width);

	       return ret;
	  }

     void Rasterizer::viewportCorrect(Vec4& toCorrect,
	       const WinCoord& windowCoordinates)
     {
	  toCorrect[0]=windowCoordinates[0];
	  toCorrect[1]=windowCoordinates[1];
     }



} /* my_gl */
