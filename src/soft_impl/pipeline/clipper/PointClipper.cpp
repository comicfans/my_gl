/*
 * =====================================================================================
 *
 *       Filename:  PointClipper.cpp
 *
 *    Description:  implementation of PointClipper
 *
 *        Version:  1.0
 *        Created:  2011-10-9 21:31:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "PointClipper.hpp"

#include <algorithm>
#include <cmath>
#include <functional>

#include "common/Vec4.hpp"
#include "shader/VertexShader.hpp"

#include "pipeline/ClippedPrimitiveGroup.hpp"


using std::all_of;
using std::bind;
using std::abs;
using std::placeholders::_1;

namespace my_gl {

     inline static bool absLessEqual(float value,float threshold)
     {
	  return abs(value)<=abs(threshold);
     }

     bool PointClipper::inClipVolume
	  (const my_gl::Vec4 &projectedCoordinate)
	  {

	       float w=projectedCoordinate(3);

	       auto* values=projectedCoordinate.values();

	       return all_of(values,values+3,bind
			 (absLessEqual,_1,w));
	  }

     PointClipper::~PointClipper(){}
	  

     void PointClipper::elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
	       ClippedPrimitiveGroup& clippedPrimitiveGroup)
	       {
		    if(inClipVolume(
				   getVertex(attributeGroupRefs[0])))
		    {
			 clippedPrimitiveGroup.
			      insertOriginalIndex(vertexIndex[0]);
		    }
		    //else clipped
	       }

     


     

} /* my_gl */
