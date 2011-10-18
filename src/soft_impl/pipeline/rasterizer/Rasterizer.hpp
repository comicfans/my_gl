/*
 * =====================================================================================
 *
 *       Filename:  Rasterizer.hpp
 *
 *    Description:  interface to Rasterizer primitive to 
 *    Frame Buffer input (before FragmentShader)
 *
 *        Version:  1.0
 *        Created:  2011-10-19 1:12:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef RASTERIZER_HPP

#define RASTERIZER_HPP

#include <boost/ptr_container/ptr_array.hpp>

#include "shader/VertexAttributeBuffer.hpp"

namespace my_gl {

     using boost::ptr_array;

     class ClippedPrimitiveGroup;

     class Rasterizer {
     public:

	  void rasterize(const ClippedPrimitiveGroup& 
		    clippedPrimitiveGroup);

     protected:

	  virtual void elementRasterize();

     private:

	  ptr_array<ConstAttributeGroupRef,
	       VertexAttributeBuffer::MAX_VERTEX_PER_ELEMENT>
		    _attributeGroups;
     
     };
	
} /* my_gl */


#endif /* end of include guard: RASTERIZER_HPP */
