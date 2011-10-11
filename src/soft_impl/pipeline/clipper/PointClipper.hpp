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


     protected:

	  virtual void elementClip
	       (size_t attributeNumber,
		const Vec4 ** attributeGroups,
		const size_t *vertexIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);


	bool inClipVolume(const Vec4& projectedCoordinate);

     };
	
} /* my_gl */


#endif /* end of include guard: POINT_CLIPPER_HPP */
