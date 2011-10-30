/*
 * =====================================================================================
 *
 *       Filename:  TriangleClipper.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-16 11:34:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TriangleClipper.hpp"

#include <memory>
#include <algorithm>

#include "LineClipper.hpp"
#include "shader/VertexAttributeBuffer.hpp"
#include "pipeline/ClippedPrimitiveGroup.hpp"

namespace my_gl {

     using std::unique_ptr;

     TriangleClipper::~TriangleClipper (){}
     static ClippedPrimitiveGroup parallellPlaneClip(
	       const ClippedPrimitiveGroup& prevResult,
	       LineClipper::ClipDim clipDim)
     {
	  ClippedPrimitiveGroup ret
	       (prevResult.getRefVertexAttributeBuffer(),
		prevResult.getPrimitiveIndex().primitiveMode());

	  auto &primitiveIndex=prevResult.getPrimitiveIndex(); 

	  int prevSize=primitiveIndex.size();

	  for(int i=0;i<prevSize;++i)
	  {

	       int beginIndex=primitiveIndex[i],
		   endIndex=primitiveIndex[(i+1)%prevSize];

	       auto clipPercent=LineClipper::
		    parallelClip(
			 getVertex
			 (prevResult[beginIndex]),

			 //next point
			 getVertex
			 (prevResult[endIndex]),

			 clipDim);

	       //vertex on clip plane,or clipped out,
	       //not insert
	       if (LineClipper::onlyPoint(clipPercent)
			 || 
			 LineClipper::outOfClipVolume(clipPercent))
	       {
		    continue;
	       }

	       if (clipPercent.first!=0)
	       {

		    LineClipper::insertInterpolatedAttributes(
			      prevResult[beginIndex],beginIndex,
			      prevResult[endIndex],endIndex,
			      clipPercent.first,ret);
		    //if first vertex is just original,
		    //leave it as the last back insert 
	       }
	       //always insert clipped end vertex,
	       //because it must be next segment begin vertex

	       LineClipper::insertInterpolatedAttributes(
			 prevResult[beginIndex],beginIndex,
			 prevResult[endIndex],endIndex, 
			 clipPercent.second,ret);
	  }

	  return ret;

     }

     static void merge(const ClippedPrimitiveGroup& source,
	       ClippedPrimitiveGroup& destination,size_t index)
     {
	  if (source.isOriginal(index))
	  {
	       destination.insertOriginalIndex(index);
	  }
	  else
	  {
	       auto attributes=destination.
		    writeClipGeneratedAttribute().second;

	       attributes=source[index];

	  }
     }

     void TriangleClipper::elementClip
	  (const ConstAttributeGroupRefList& attributeGroupRefs,
	   const size_t *vertexIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {

	       unique_ptr<ClippedPrimitiveGroup> pBuffer(
			 new ClippedPrimitiveGroup
			 (clippedPrimitiveGroup.
			  getRefVertexAttributeBuffer(),

			  clippedPrimitiveGroup.
			  getPrimitiveIndex().primitiveMode()));

		    for (int i=0; i<3; ++i)
		    {
			 pBuffer->insertOriginalIndex
			      (vertexIndex[i]);
		    }

		    //three parallel plane clip x,y,z
		    for(int i=0;i<3;++i)
		    {
			 pBuffer.reset(new ClippedPrimitiveGroup
				   (parallellPlaneClip
				    (*pBuffer,
				     LineClipper::ClipDim(i))));
		    }

		    //after clip ,pBuffer contains only internal
		    //vertex of triangle,then use triangle fan 
		    //to add these triangles
		    
		    auto& primitiveIndex=
			 pBuffer->getPrimitiveIndex();
	
		    if (primitiveIndex.vertexNumber()==0)
		    {
			 //no vertex retained,all clipped
			 return;
		    }
		    
		    assert(primitiveIndex.vertexNumber()>=3);
		    for(size_t i=2;i<primitiveIndex.vertexNumber();++i)
		    {

			 merge(*pBuffer,clippedPrimitiveGroup,
			      primitiveIndex[0]);

			 merge(*pBuffer,clippedPrimitiveGroup,
				   primitiveIndex[i-1]);
			 merge(*pBuffer,clippedPrimitiveGroup,
				   primitiveIndex[i]);
		    }
	  }
} /* my_gl */
