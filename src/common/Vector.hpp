/*
 * =====================================================================================
 *
 *       Filename:  Vector.hpp
 *
 *    Description:  simple vector float 4 
 *
 *        Version:  1.0
 *        Created:  2011-9-13 16:05:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VECTOR_HPP


#define VECTOR_HPP

#include <cstddef>

namespace my_gl {
     struct Vector{
    
	  public:

	       Vector(bool fillZero=true)noexcept;

	       Vector(float fx,float fy,float fz=0,float fw=1)noexcept;

	       Vector& operator=(const Vector& rhs);

	       static const int LENGTH=4;

	       float& operator()(size_t idx)noexcept;
	       const float& operator()(size_t idx)const noexcept;

	       float& operator[](size_t idx)noexcept;
	       const float& operator[](size_t idx)const noexcept;

	       const float* values()const noexcept;
	       float * values() noexcept;
	  private:
	       float _values[LENGTH];
     	/* data */
     };

     void normalize(float * values);
	
} /* my_gl */


#endif /* end of include guard: VECTOR_HPP */
