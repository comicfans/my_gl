/*
 * =====================================================================================
 *
 *       Filename:  PrimitiveIndex.hpp
 *
 *    Description:  a simple typedef
 *
 *        Version:  1.0
 *        Created:  2011-10-10 14:24:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef PRIMITIVE_INDEX_HPP

#define PRIMITIVE_INDEX_HPP

#include <vector>
#include <cstdint>
#include <limits>

#include "Enum.hpp"


namespace my_gl {

     using std::vector;
     using std::uint32_t;
     using std::size_t;
     using std::numeric_limits;


     class IndexProvider;
     class PrimitiveIndex:protected vector<uint32_t>{
	  typedef vector<uint32_t> SuperType;
     public:
     	PrimitiveIndex (const PrimitiveMode primitiveMode,
		  size_t useVertexNumber,
		  const IndexProvider& indexProvider,
		  size_t actualVertexNumber=
		  numeric_limits<size_t>::max());

	PrimitiveIndex(const PrimitiveMode primitiveMode);

	PrimitiveIndex(const PrimitiveIndex& rhs);

	using SuperType::begin;

	using SuperType::end;

	using SuperType::size;

	using SuperType::operator[];

	size_t vertexNumber()const;

	size_t elementNumber()const;

	size_t vertexPerPrimitive()const;

	//insert new vertex index
	void insertNew(size_t newIndex);

	PrimitiveMode primitiveMode()const;

     private:

	const size_t _vertexPerPrimitive;

	const PrimitiveMode _primitiveMode;

	size_t _elementNumber;

	void fillLineIndex(const size_t atMostVertexNumber,
		  const IndexProvider& indexProvider);
	void fillTriangleIndex(const size_t atMostVertexNumber,
		  const IndexProvider& indexProvider);
	void fillPointIndex(const size_t atMostVertexNumber,
		  const IndexProvider& indexProvider);
     

     };

	
} /* my_gl */



#endif /* end of include guard: PRIMITIVE_INDEX_HPP */
