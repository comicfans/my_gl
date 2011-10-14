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

#include "Enum.hpp"


namespace my_gl {

     using std::vector;
     using std::size_t;


     class IndexProvider;
     class PrimitiveIndex:protected vector<size_t>{
     public:
     	PrimitiveIndex (const PrimitiveMode primitiveMode,
		  size_t useVertexNumber,
		  size_t actualVertexNumber,
		  const IndexProvider& indexProvider);

	PrimitiveIndex(const PrimitiveMode primitiveMode);

	using vector<size_t>::begin;

	using vector<size_t>::end;

	using vector<size_t>::size;

	using vector<size_t>::operator[];

	const size_t vertexNumber()const;

	const size_t elementNumber()const;

	const size_t vertexPerPrimitive()const;

	//insert new vertex index
	void insertNew(size_t newIndex);

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
