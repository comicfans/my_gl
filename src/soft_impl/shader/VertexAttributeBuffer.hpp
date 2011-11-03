/*
 * =====================================================================================
 *
 *       Filename:  VertexAttributeBuffer.hpp
 *
 *    Description:  a buffer to store vertex shader processed
 *    vertex attribute
 *    
 *
 *        Version:  1.0
 *        Created:  2011-10-6 13:33:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef VERTEX_ATTRIBUTE_BUFFER_HPP

#define VERTEX_ATTRIBUTE_BUFFER_HPP

#include <boost/multi_array.hpp>


#include "common/Vec.hpp"

namespace my_gl {

     //TODO var width
     using boost::multi_array;

	  
     typedef multi_array<Vec4,2>::reference AttributeGroupRef;

     typedef multi_array<Vec4,2>::const_reference ConstAttributeGroupRef;


     class VertexAttributeBuffer :protected multi_array<Vec4,2>
     {

	  public:

	       VertexAttributeBuffer();

	       size_t elementNumber()const ;

	       size_t attributeNumber()const;

	       void resize(size_t length);

	       typedef multi_array<Vec4,2> SuperType;

	       using SuperType::operator[];

	       using SuperType::begin;
	       using SuperType::end;


	       //reserved for quad use, right now only triangle is used
	       static const size_t MAX_VERTEX_PER_ELEMENT=4;

	       static const size_t DEFAULT_OUT_SIZE=5;

	       enum OutIndex{POSITION,POINT_SIZE,
		    FRONT_COLOR,BACK_COLOR,TEXCOORD};

	       AttributeGroupRef back();

	       	       
     };

     const Vec4& getVertex(
		    const ConstAttributeGroupRef& attributeGroup);
	  
     Vec4& getVertex(
		    AttributeGroupRef attributeGroup);


} /* my_gl */

#endif /* end of include guard: VERTEX_ATTRIBUTE_BUFFER_HPP */

