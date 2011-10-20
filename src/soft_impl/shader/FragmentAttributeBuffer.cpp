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

namespace my_gl {
	
	  AttributeGroupRef FragmentAttributeBuffer::operator()
	       (WindowCoordinate windowCoordinate)
	       {
		    return (*this)
			 [windowCoordinate.first]
			 [windowCoordinate.second];

	       }
} /* my_gl */
