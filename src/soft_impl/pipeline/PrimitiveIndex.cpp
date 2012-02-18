/*
 * =====================================================================================
 *
 *       Filename:  PrimitiveIndex.cpp
 *
 *    Description:  implementation 
 *
 *        Version:  1.0
 *        Created:  2011-10-10 16:29:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "PrimitiveIndex.hpp"

#include <cmath>
#include <cassert>

#include "index_provider/IndexProvider.hpp"
#include "common/TypeTraits.hpp"
#include "common/CheckEnum.hpp"

using std::min;
using std::max;

namespace my_gl {


     //{POINTS,LINE_STRIP,LINE_LOOP,LINES,
     //	  TRIANGLE_STRIP,TRIANGLE_FAN,TRIANGLES};


     PrimitiveIndex::PrimitiveIndex
	  (const GLenum primitiveMode)
		:_vertexPerPrimitive(
			  VERTEX_PER_PRIMITIVE[primitiveMode]),
		_primitiveMode(primitiveMode),_elementNumber(0)
	  {
	       checkPrimitiveMode(primitiveMode);
	  }


     PrimitiveIndex::PrimitiveIndex
	  (const GLenum primitiveMode,
	   const size_t useVertexNumber,
	   const IndexProvider& indexProvider,
	   const size_t actualVertexNumber)
	  :_vertexPerPrimitive(
		    VERTEX_PER_PRIMITIVE[int(primitiveMode)]),
	  _primitiveMode(primitiveMode)
     {

	  checkPrimitiveMode(primitiveMode);

	  //vertex number less equal than vertex attribute buffer length 
	  int actualVertex=min
	       (useVertexNumber,actualVertexNumber);

	  switch(primitiveMode)
	  {
	       case GL_POINTS:
		    {fillPointIndex(actualVertex,
			      indexProvider);break;}

	       case GL_LINE_LOOP:
	       case GL_LINE_STRIP:
	       case GL_LINES:
		    {fillLineIndex(actualVertex,
			      indexProvider);break;}

	       case GL_TRIANGLES:
	       case GL_TRIANGLE_STRIP:
	       case GL_TRIANGLE_FAN:
		    {fillTriangleIndex(actualVertex,
			      indexProvider);break;}
	  }

     }

     PrimitiveIndex::PrimitiveIndex
	  (const PrimitiveIndex& rhs)
	  :SuperType(rhs),
	  _vertexPerPrimitive(rhs._vertexPerPrimitive),
	   _primitiveMode(rhs._primitiveMode),
	   _elementNumber(rhs._elementNumber)
	{}

     size_t PrimitiveIndex
	  ::vertexNumber()const
	  {
	       return size();
	  }

	
     size_t PrimitiveIndex
	  ::elementNumber()const
	  {
	       return _elementNumber;
	  }

     size_t PrimitiveIndex::vertexPerPrimitive() const 
     {
	  return _vertexPerPrimitive;
     }

     void PrimitiveIndex::fillPointIndex
	  (size_t atMostVertexNumber,
	   const IndexProvider& indexProvider)
	  {

	       _elementNumber=atMostVertexNumber;

	       resize(atMostVertexNumber);

	       for (size_t i=0; i<atMostVertexNumber; ++i)
	       {(*this)[i]=indexProvider.getIndex(i);}
	  }

     void PrimitiveIndex::fillLineIndex
	  (const size_t atMostVertexNumber,
	   const IndexProvider& indexProvider)
	  {


	       if (_primitiveMode==GL_LINES)
	       {
		    _elementNumber=atMostVertexNumber/2;

		    resize(_elementNumber*2);

		    for (size_t i=0; i<size(); ++i)
		    {
			 (*this)[i]=indexProvider.getIndex(i);
		    }
	       }

	       else
	       {
		    //treat LINE_STRIP as LINE_LOOP first,than cut it off

		    _elementNumber=atMostVertexNumber;

		    resize(_elementNumber*2);

		    for (size_t i=0; i<_elementNumber; ++i)
		    {
			 (*this)[i*2]=indexProvider.getIndex(i);
			 //last point index is overflow
			 (*this)[i*2+1]=indexProvider.getIndex(i+1);
		    }

		    if (_primitiveMode==GL_LINE_STRIP)
		    {
			 --_elementNumber;
			 resize(size()-2);
		    }

		    else
		    {
			 //roll last element to base 0
			 back()=0;
		    }
	       }

	  }    

     void PrimitiveIndex::fillTriangleIndex
	  (const size_t atMostVertexNumber,
	   const IndexProvider& indexProvider)
	  {
	       switch(_primitiveMode)
	       {
		    case GL_TRIANGLES:
			 {
			      _elementNumber=atMostVertexNumber/3;
			      resize(_elementNumber*3);

			      for (size_t i=0; i<size(); ++i)
			      {
				   (*this)[i]=indexProvider.getIndex(i);
			      }
			      break;

			 }

		    case GL_TRIANGLE_STRIP:
			 {
			      _elementNumber=max<int>(atMostVertexNumber-2,0);
			      resize(_elementNumber*3);
			      bool odd=false;
			      for (size_t i=0; i<_elementNumber; ++i)
			      {
				   (*this)[i*3]=indexProvider.getIndex(i+odd);
				   (*this)[i*3+1]=indexProvider.getIndex(i+!odd);
				   (*this)[i*3+2]=indexProvider.getIndex(i+2);
				   odd=!odd;
			      }
			      break;
			 }
		    case GL_TRIANGLE_FAN:
			 {
			      _elementNumber=max<int>(atMostVertexNumber-2,0);
			      resize(_elementNumber*3);
			      for (size_t i=0; i<_elementNumber; ++i)
			      {
				   (*this)[i*3]=indexProvider.getIndex(0);
				   (*this)[i*3+1]=indexProvider.getIndex(i+1);
				   (*this)[i*3+2]=indexProvider.getIndex(i+2);
			      }
			      break;
			 }
		    default:
			 {
			      //not possible
			      assert(false);
			 }
	       }
	  }

     void PrimitiveIndex::insertNew(size_t newIndex)
     {
	  push_back(newIndex);
	  _elementNumber=size()/_vertexPerPrimitive;
     }

	
     GLenum PrimitiveIndex::primitiveMode()const
     {return _primitiveMode;}
} /* my_gl */
