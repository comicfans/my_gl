/*
 * =====================================================================================
 *
 *       Filename:  LineClipper.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-11 11:24:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef LINE_CLIPPER_HPP

#define LINE_CLIPPER_HPP

#include "Clipper.hpp"

namespace my_gl {

     class LineClipper :public Clipper{
     public:

     	virtual ~LineClipper ();

     protected:

	static bool isInfinit(const Vec4& position);



	  virtual void elementClip
	       (size_t attributeNumber,
		const Vec4 ** attributeGroups,
		const size_t *vertexIndex,
		ClippedPrimitiveGroup& clippedPrimitiveGroup);


     };
	
} /* my_gl */


#endif /* end of include guard: LINE_CLIPPER_HPP */
