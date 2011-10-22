/*
 * =====================================================================================
 *
 *       Filename:  FragmentAttributeBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-19 10:28:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "FragmentAttributeBuffer.hpp"
#include "pipeline/rasterizer/WindowCoordinates.hpp"

namespace my_gl {
	
	  AttributeGroupRef FragmentAttributeBuffer::operator()
	       (const WindowCoordinates& windowCoordinate)
	       {
		    return (*this)
			 [windowCoordinate.first]
			 [windowCoordinate.second];

	       }
	  size_t FragmentAttributeBuffer::
	       attributeNumber()const
	       {
		    return shape()[2];
	       }
} /* my_gl */
