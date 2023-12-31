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

#include <vector>
#include <utility>

#include "PrimitiveIndex.hpp"

#include "soft_impl/shader/VertexAttributeBuffer.hpp"
#include "common/VecFwd.hpp"

namespace my_gl {


     using std::vector;
     using std::pair;

     class ClippedPrimitiveGroup {
     public:
     	ClippedPrimitiveGroup 
	     (const VertexAttributeBuffer& originalVertexAttribute,
	      GLenum primitiveMode); 

	ClippedPrimitiveGroup
	     (const ClippedPrimitiveGroup& rhs);

	virtual ~ClippedPrimitiveGroup();

	void insertOriginalIndex(size_t original);

	pair<size_t,AttributeGroupRef> writeClipGeneratedAttribute();

	const PrimitiveIndex& getPrimitiveIndex()const;

	const VertexAttributeBuffer& getRefVertexAttributeBuffer()const;

	ConstAttributeGroupRef operator[](size_t index)const;

	void duplicateVertexAttribute(size_t index);

	bool isOriginal(size_t index)const;

	size_t elementNumber()const;

	size_t attributeNumber()const;

	size_t getClipGeneratedElementNumber()const;

     private:

	const VertexAttributeBuffer& _originalVertexAttribute;

	VertexAttributeBuffer _clipGeneratedVertexAttribute;

	PrimitiveIndex _mixedIndex;

	ConstAttributeGroupRef getClipGeneratedAttribute(size_t index)const;

     };
	
} /* my_gl */



#endif /* end of include guard: CLIPPED_PRIMITIVE_GROUP_HPP */
