/*
 * =====================================================================================
 *
 *       Filename:  PointClipper.hpp
 *
 *    Description:  clipper to clip point
 *
 *        Version:  1.0
 *        Created:  2011-10-9 21:30:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef POINT_CLIPPER_HPP

#define POINT_CLIPPER_HPP

#include "Clipper.hpp"

namespace my_gl {

     struct Vec4;
     class PointClipper :public Clipper{
     public:

     	virtual ~PointClipper ();

	static bool inClipVolume(const Vec4& projectedCoordinate);

	static bool isInfinit(const Vec4& position);

	static void perspectiveDivision(Vec4& position);

     protected:


	  virtual void elementClip
	       (const ConstAttributeGroupRef* attributeGroupRefs,
		const size_t *vertexIndex,
	       ClippedPrimitiveGroup& clippedPrimitiveGroup);



     };
	
} /* my_gl */


#endif /* end of include guard: POINT_CLIPPER_HPP */
