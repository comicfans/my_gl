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
     using boost::extents;

     const int SIDE_OFFSET=4;
	
     FragmentAttributeBuffer::FragmentAttributeBuffer 
	     (size_t width,size_t height,size_t attributeNumber)
	     :SuperType(extents[height+SIDE_OFFSET*2]
		       [width][attributeNumber+SIDE_OFFSET*2])
	     {
		  //clipped coordinates may be out of clip volume a little
		  //so makes FragmentAttributeBuffer a little outter
		  reindex(SIDE_OFFSET);
	     }

	  AttributeGroupRef FragmentAttributeBuffer::operator()
	       (size_t y,size_t x)
	       {
		    return (*this)[y][x];

	       }
	  AttributeGroupRef FragmentAttributeBuffer::operator()
	       (const WindowCoordinates& windowCoordinate)
	       {
		    return (*this)
			 (windowCoordinate.first,windowCoordinate.second);

	       }
	  size_t FragmentAttributeBuffer::
	       attributeNumber()const
	       {
		    return shape()[2];
	       }

	  size_t FragmentAttributeBuffer::width()const
	  {
	       return shape()[1];
	  }
	  size_t FragmentAttributeBuffer::height()const
	  {
	       return shape()[0];
	  }
} /* my_gl */
