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

	
     ClippedPrimitiveGroup::ClippedPrimitiveGroup
	     (const ClippedPrimitiveGroup& rhs)
	     :_originalVertexAttribute
	      (rhs._originalVertexAttribute),
	      _mixedIndex(rhs._mixedIndex)
	     {}

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

	pair<size_t,AttributeGroupRef> ClippedPrimitiveGroup
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
		  size_t thisIndex=originalIndexRange
			    +newLength-1;
		  _mixedIndex.insertNew(thisIndex);

		  return {thisIndex,_clipGeneratedVertexAttribute.
		       back()};
	     }

	ConstAttributeGroupRef ClippedPrimitiveGroup
	     ::operator[](size_t index)const
	     {
		  if (isOriginal(index))
		  {
		       return _originalVertexAttribute[index];
		  }
		  else
		  {
		       return getClipGeneratedAttribute(index);
		  }
	     }

	const VertexAttributeBuffer& ClippedPrimitiveGroup::
	     getRefVertexAttributeBuffer()const
	     {
		  return _originalVertexAttribute;
	     }

	void ClippedPrimitiveGroup::duplicateVertexAttribute
	     (size_t index)
	     {
		  if (isOriginal(index))
		  {
		       //still insert original index
		       insertOriginalIndex(index);
		  }
		  else
		  {
		       //change PrimitiveIndex only,
		       //not insert new data
		       _mixedIndex.insertNew(index);
		  }

	     }

	bool ClippedPrimitiveGroup::isOriginal(size_t index)const
	{
		  int originalIndexRange=
		       _originalVertexAttribute.length();
		  return index<originalIndexRange;
	}

	ConstAttributeGroupRef ClippedPrimitiveGroup::
	     getClipGeneratedAttribute(size_t index)const
	     {
		  return _clipGeneratedVertexAttribute[
		       index-_originalVertexAttribute.length()];
	     }
	size_t ClippedPrimitiveGroup::length()const
	{
	     return _originalVertexAttribute.length()+
		  _clipGeneratedVertexAttribute.length();
	}

} /* my_gl */
