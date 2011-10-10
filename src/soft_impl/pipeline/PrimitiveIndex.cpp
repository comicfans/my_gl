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

#include "IndexProvider.hpp"

using std::min;
using std::max;

namespace my_gl {


     //{POINTS,LINE_STRIP,LINE_LOOP,LINES,
     //	  TRIANGLE_STRIP,TRIANGLE_FAN,TRIANGLES};

     static const int VERTEX_PER_PRIMITIVE[]={1,2,2,2,3,3,3};

     PrimitiveIndex::PrimitiveIndex
	  (const PrimitiveMode primitiveMode,
	   const size_t useVertexNumber,
	   const size_t actualVertexNumber,
	   const IndexProvider& indexProvider)
	  :_vertexPerPrimitive(VERTEX_PER_PRIMITIVE[int(primitiveMode)]),
	  _primitiveMode(primitiveMode),
	  _indexProvider(indexProvider)
     {

	  //vertex number less equal than vertex attribute buffer length 
	  int actualVertex=min
	       (useVertexNumber,actualVertexNumber);

	  switch(primitiveMode)
	  {
	       case PrimitiveMode::POINTS:
		    {fillPointIndex(actualVertex);break;}

	       case PrimitiveMode::LINE_LOOP:
	       case PrimitiveMode::LINE_STRIP:
	       case PrimitiveMode::LINES:
		    {fillLineIndex(actualVertex);break;}

	       case PrimitiveMode::TRIANGLES:
	       case PrimitiveMode::TRIANGLE_STRIP:
	       case PrimitiveMode::TRIANGLE_FAN:
		    {fillTriangleIndex(actualVertex);break;}
	  }

     }

     const size_t PrimitiveIndex
	  ::vertexNumber()const
	  {
	       return size();
	  }

     const size_t PrimitiveIndex
	  ::elementNumber()const
	  {
	       return _elementNumber;
	  }

     void PrimitiveIndex::fillPointIndex
	  (size_t atMostVertexNumber)
	  {

	       _elementNumber=atMostVertexNumber;

	       resize(atMostVertexNumber);

	       for (int i=0; i<atMostVertexNumber; ++i)
	       {(*this)[i]=_indexProvider.getIndex(i);}
	  }

     void PrimitiveIndex::fillLineIndex
	  (const size_t atMostVertexNumber)
	  {


	       if (_primitiveMode==PrimitiveMode::LINES)
	       {
		    _elementNumber=atMostVertexNumber/2;

		    resize(_elementNumber*2);

		    for (int i=0; i<size(); ++i)
		    {
			 (*this)[i]=_indexProvider.getIndex(i);
		    }
	       }

	       else
	       {
		    //treat LINE_STRIP as LINE_LOOP first,than cut it off

		    _elementNumber=atMostVertexNumber;

		    resize(_elementNumber*2);

		    for (int i=0; i<_elementNumber; ++i)
		    {
			 (*this)[i*2]=_indexProvider.getIndex(i);
			 //last point index is overflow
			 (*this)[i*2+1]=_indexProvider.getIndex(i+1);
		    }

		    if (_primitiveMode==PrimitiveMode::LINE_STRIP)
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
	  (const size_t atMostVertexNumber)
	  {
	       switch(_primitiveMode)
	       {
		    case PrimitiveMode::TRIANGLES:
			 {
			      _elementNumber=atMostVertexNumber/3;
			      resize(_elementNumber*3);

			      for (int i=0; i<size(); ++i)
			      {
				   (*this)[i]=_indexProvider.getIndex(i);
			      }
			      break;

			 }

		    case PrimitiveMode::TRIANGLE_STRIP:
			 {
			      _elementNumber=max<int>(atMostVertexNumber-2,0);
			      resize(_elementNumber*3);
			      for (int i=0; i<size(); ++i)
			      {
				   (*this)[i*3]=_indexProvider.getIndex(i);
				   (*this)[i*3+1]=_indexProvider.getIndex(i+1);
				   (*this)[i*3+2]=_indexProvider.getIndex(i+2);
			      }
			      break;
			 }
		    case PrimitiveMode::TRIANGLE_FAN:
			 {
			      _elementNumber=max<int>(atMostVertexNumber-2,0);
			      resize(_elementNumber*3);
			      for (int i=0; i<size(); ++i)
			      {
				   (*this)[i*3]=_indexProvider.getIndex(0);
				   (*this)[i*3+1]=_indexProvider.getIndex(i+1);
				   (*this)[i*3+2]=_indexProvider.getIndex(i+2);
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
} /* my_gl */
