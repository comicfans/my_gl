/*
 * =====================================================================================
 *
 *       Filename:  ArrayVec4Provider.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-19 13:18:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ArrayVec4Provider.hpp"

#include <cassert>

#include "PointerFunction.hpp"

namespace my_gl {

     static size_t calcBlockSize(GLenum type,int componentNumber,
	       size_t stride)
     {
	  assert(type==GL_BYTE || type==GL_UNSIGNED_BYTE || 
		    type==GL_SHORT || type==GL_FIXED 
		    ||type==GL_FLOAT || "wrong data type enum ");

	  return stride? stride :
	  DATA_TYPE_UNDERLINE_SIZE[type]*componentNumber;
     }

     ArrayVec4Provider::ArrayVec4Provider
	  (int componentNumber,GLenum type,size_t stride,bool normalize)
	  :_dataType(type),_componentNumber(componentNumber),
	  _blockSize(calcBlockSize(type,componentNumber,stride)),
	  _normalize(normalize)
     {}

	  template<GLenum dataType>
	       Vec4 ArrayVec4Provider::copyToFloats(const void* p)
	       const 
	       {
		    typedef typename 
			 DataTypeTraits<dataType>::underlineType type;
		    type const *tp=static_cast<type const*>(p);
		    Vec4 ret;
		    copy_n(tp,_componentNumber,ret.values());

		    if (_normalize)
		    {
			 for (int i=0; i<_componentNumber; ++i)
			 {
			      ret(i)=DataTypeTraits<dataType>::
				   normalize(ret(i));
			 }
		    }

		    return ret;
	       }



     Vec4 ArrayVec4Provider::castRead
	  (const void* pointer,size_t index)const 
	  {
	       const void* actualPointer=
		    add(pointer,index*_blockSize);

	       switch(_dataType)
	       {
		    case GL_BYTE:
			 {return this->copyToFloats<GL_BYTE>
			      (actualPointer);}
		    case GL_UNSIGNED_BYTE:
			      {return copyToFloats<GL_UNSIGNED_BYTE>
			      (actualPointer);}
		    case GL_SHORT:
			 {return copyToFloats<GL_SHORT>
			      (actualPointer);}
		    case GL_UNSIGNED_SHORT:
			 {return copyToFloats<GL_UNSIGNED_SHORT>
			      (actualPointer);}
		    case GL_FIXED:
			 {return copyToFloats<GL_FIXED>
			      (actualPointer);}
		    case GL_FLOAT:
			      {return copyToFloats<GL_FLOAT>
				   (actualPointer);}
		    default:
				   //SHOULD NOT here
				   {assert(false || "wrong data type passed to castRead");}

	       }
	  }

} /* my_gl */
