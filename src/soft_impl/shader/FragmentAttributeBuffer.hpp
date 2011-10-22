/*
 * =====================================================================================
 *
 *       Filename:  FragmentAttributeBuffer.hpp
 *
 *    Description:  store rasterized attribute
 *    			VertexAttributeBuffer->FragmentAttributeBuffer use copy approach
 *    			because a few primitive vertex may leads many fragment
 *
 *        Version:  1.0
 *        Created:  2011-10-19 9:39:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef FRAGMENT_ATTRIBUTE_BUFFER_HPP

#define FRAGMENT_ATTRIBUTE_BUFFER_HPP

#include <boost/multi_array.hpp>

#include "common/Vec4.hpp"


namespace my_gl {

     using boost::multi_array;

     typedef multi_array<Vec4,3>::reference::reference AttributeGroupRef;

     struct WindowCoordinates;

     class FragmentAttributeBuffer :protected multi_array<Vec4,3>{
     public:

	  typedef multi_array<Vec4,3> SuperType;
     
	  FragmentAttributeBuffer 
	     (size_t width,size_t height,size_t attributeNumber);

	  size_t attributeNumber()const;

	  AttributeGroupRef operator()(const WindowCoordinates& windowCoordinate);

     };
	
} /* my_gl */



#endif /* end of include guard: FRAGMENT_ATTRIBUTE_BUFFER_HPP */
