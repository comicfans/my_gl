/*
 * =====================================================================================
 *
 *       Filename:  LineClipper.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-11 11:28:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "LineClipper.hpp"

namespace my_gl {

     LineClipper::~LineClipper(){}

     bool LineClipper::isInfinit(const Vec4 &position)
     {
	  return position.w()==0;
     }

     void LineClipper::elementClip
	  (size_t attributeNumber,
	   const Vec4 ** attributeGroups,
	   const size_t *vertexIndex,
	   ClippedPrimitiveGroup& clippedPrimitiveGroup)
	  {

	  }


} /* my_gl */
