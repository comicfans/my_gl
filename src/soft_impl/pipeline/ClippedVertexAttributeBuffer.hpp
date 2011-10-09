/*
 * =====================================================================================
 *
 *       Filename:  ClippedVertexAttributeBuffer.hpp
 *
 *    Description:  vertex attribute buffer after clipping
 *
 *        Version:  1.0
 *        Created:  2011-10-9 20:36:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CLIPPED_VERTEX_ATTRIBUTE_BUFFER_HPP

#define CLIPPED_VERTEX_ATTRIBUTE_BUFFER_HPP

#include "shader/VertexAttributeBuffer.hpp"

namespace my_gl {


     class ClippedVertexAttributeBuffer {
     public:
     	ClippedVertexAttributeBuffer 
	     (const VertexAttributeBuffer& originalBuffer);

	size_t length()const;

	Vec4* data(size_t index);

     private:

	const VertexAttributeBuffer& _originalBuffer;

	VertexAttributeBuffer _clippedNewBuffer;
     };
	
} /* my_gl */



#endif /* end of include guard: CLIPPED_VERTEX_ATTRIBUTE_BUFFER_HPP */
