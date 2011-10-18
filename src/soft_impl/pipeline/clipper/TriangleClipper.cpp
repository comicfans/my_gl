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

     static ClippedPrimitiveGroup parallellPlaneClip(
	       const ClippedPrimitiveGroup& prevResult,
	       LineClipper::ClipPlane clipPlane)
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

	       auto clipResult=LineClipper::commonClip(

			 VertexAttributeBuffer::getVertex
			 (prevResult[beginIndex]),

			 //next point
			 VertexAttributeBuffer::getVertex
			 (prevResult[endIndex]),

			 clipPlane);

	       bool hasInfinit=clipResult.first;
	       auto& clipPercent=clipResult.second;

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
		    auto newData=ret.writeClipGeneratedAttribute();
		    LineClipper::interpolateAttributeGroup(
			      prevResult[beginIndex],
			      prevResult[endIndex],clipPercent.first,
			      newData.second);
		    //if first vertex is just original,
		    //leave it as the last back insert 
	       }
	       //always insert clipped end vertex,
	       //because it must be next segment begin vertex

	       LineClipper::insertInterpolatedAttributes(
			 prevResult[beginIndex], beginIndex, 
			 prevResult[endIndex], endIndex, 
			 clipPercent.second, ret, hasInfinit);
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
	  (const ConstAttributeGroupRef* attributeGroupRefs,
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
				     LineClipper::ClipPlane(i))));
		    }

		    //after clip ,pBuffer contains only internal
		    //vertex of triangle,then use triangle fan 
		    //to add these triangles

		    if (pBuffer->length()==0)
		    {
			 //no vertex retained,all clipped
			 return;
		    }

		    auto& primitiveIndex=
			 pBuffer->getPrimitiveIndex();
		    
		    merge(*pBuffer,clippedPrimitiveGroup,
			      primitiveIndex[0]);

		    for(int i=2;i<pBuffer->length();++i)
		    {

			 merge(*pBuffer,clippedPrimitiveGroup,
				   primitiveIndex[i-1]);
			 merge(*pBuffer,clippedPrimitiveGroup,
				   primitiveIndex[i]);
		    }
	  }
} /* my_gl */
