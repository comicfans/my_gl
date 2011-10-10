/*
 * =====================================================================================
 *
 *       Filename:  ClippedPrimitiveGroup.hpp
 *
 *    Description:  vertex attribute and PrimitiveIndex group
 *
 *        Version:  1.0
 *        Created:  2011-10-10 19:57:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CLIPPED_PRIMITIVE_GROUP_HPP

#define CLIPPED_PRIMITIVE_GROUP_HPP

#include "common/VertexAttributeBuffer.hpp"

namespace my_gl {

     class ClippedPrimitiveGroup {
     public:
     	ClippedPrimitiveGroup 
	     (const VertexAttributeBuffer& originalVertexAttribute);

	void insertOriginalIndex(size_t original);

	void insertClippedAttribute();

     private:

	const VertexAttributeBuffer& _originalVertexAttribute;

	VertexAttributeBuffer _clipGeneratedVertexAttribute;
     };
	
} /* my_gl */



#endif /* end of include guard: CLIPPED_PRIMITIVE_GROUP_HPP */
