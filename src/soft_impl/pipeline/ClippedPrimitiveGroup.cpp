/*
 * =====================================================================================
 *
 *       Filename:  ClippedPrimitiveGroup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-10 23:55:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ClippedPrimitiveGroup.hpp"

namespace my_gl {
     ClippedPrimitiveGroup::ClippedPrimitiveGroup 
	     (const VertexAttributeBuffer& originalVertexAttribute,
	      PrimitiveMode primitiveMode)
	     :_originalVertexAttribute(originalVertexAttribute),
	     _mixedIndex(primitiveMode)
	     {
	     }


     void ClippedPrimitiveGroup::
	  insertOriginalIndex(size_t original)
	  {
	       _mixedIndex.insertNew(original);
	  }

     const PrimitiveIndex& ClippedPrimitiveGroup
	  ::getPrimitiveIndex()const
     {
	  return _mixedIndex;
     }

	AttributeGroupRef ClippedPrimitiveGroup
	     ::writeClipGeneratedAttribute()
	     {

		  int newLength=
		       _clipGeneratedVertexAttribute.length()+1;

		  int originalIndexRange=
		       _originalVertexAttribute.length();

		  _clipGeneratedVertexAttribute.resize
		       (newLength);

		  //insert into new length
		  //but with index range more 
		  //than originalVertexAttribute
		  //length
		  _mixedIndex.insertNew(originalIndexRange
			    +newLength-1);

		  return _clipGeneratedVertexAttribute.
		       back();
	     }

	ConstAttributeGroupRef ClippedPrimitiveGroup
	     ::operator[](size_t index)
	     {
		  int originalIndexRange=
		       _originalVertexAttribute.length();
		  if (index<originalIndexRange)
		  {
		       return _originalVertexAttribute[index];
		  }
		  else
		  {
		       return _clipGeneratedVertexAttribute
			    [index-originalIndexRange];
		  }
	     }
} /* my_gl */
