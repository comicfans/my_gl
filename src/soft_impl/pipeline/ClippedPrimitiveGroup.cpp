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
	      GLenum primitiveMode)
	     :_originalVertexAttribute(originalVertexAttribute),
	     _mixedIndex(primitiveMode)
	     {
	     }

	
     ClippedPrimitiveGroup::ClippedPrimitiveGroup
	     (const ClippedPrimitiveGroup& rhs)
	     :_originalVertexAttribute
	      (rhs._originalVertexAttribute),
	      _clipGeneratedVertexAttribute
	      (rhs._clipGeneratedVertexAttribute),
	      _mixedIndex(rhs._mixedIndex)
	     {}

     ClippedPrimitiveGroup::~ClippedPrimitiveGroup(){}

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
		       _clipGeneratedVertexAttribute.elementNumber()+1;

		  int originalIndexRange=
		       _originalVertexAttribute.elementNumber();

		  _clipGeneratedVertexAttribute.resize
		       (newLength);

		  //insert into new length
		  //but with index range more 
		  //than originalVertexAttribute
		  //length
		  size_t thisIndex=originalIndexRange
			    +newLength-1;
		  _mixedIndex.insertNew(thisIndex);

		  return pair<size_t,AttributeGroupRef>(thisIndex,_clipGeneratedVertexAttribute.
		       back());
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
		  size_t originalIndexRange=
		       _originalVertexAttribute.elementNumber();
		  return index<originalIndexRange;
	}

	ConstAttributeGroupRef ClippedPrimitiveGroup::
	     getClipGeneratedAttribute(size_t index)const
	     {
		  int reindex=index-_originalVertexAttribute.elementNumber();
		  assert(reindex<_clipGeneratedVertexAttribute.elementNumber()
			    || "index of _clipGeneratedVertexAttribute out_of_range");
		  return _clipGeneratedVertexAttribute[reindex];
	     }
	size_t ClippedPrimitiveGroup::elementNumber()const
	{
	     return _mixedIndex.vertexNumber();
	}

	size_t ClippedPrimitiveGroup::attributeNumber()const
	{
	     return _originalVertexAttribute.attributeNumber();
	}

	size_t ClippedPrimitiveGroup::getClipGeneratedElementNumber()const
	{
	     return _clipGeneratedVertexAttribute.elementNumber();
	}

} /* my_gl */
