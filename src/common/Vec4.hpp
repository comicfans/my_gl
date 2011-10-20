/*
 * =====================================================================================
 *
 *       Filename:  Vec4.hpp
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

#ifndef VEC4_HPP


#define VEC4_HPP

#include <cstddef>

namespace my_gl {
     struct Vec4{
    
	  public:

	       Vec4(bool fillZero=true);

	       Vec4(float fx,float fy,float fz=0,float fw=1);

	       Vec4& operator=(const Vec4& rhs);

	       void operator*=(float scalar);

	       void operator/=(float scalar);

	       void operator+=(const Vec4& rhs);

	       static const int LENGTH=4;

	       float& operator()(size_t idx);
	       const float& operator()(size_t idx)const ;

	       float& operator[](size_t idx);
	       const float& operator[](size_t idx)const ;

	       const float* values()const ;
	       float * values() ;

	       const float& x()const;
	       const float& y()const;
	       const float& z()const;
	       const float& w()const;
	       
	  private:
	       float _values[LENGTH];
     	/* data */
     };

     Vec4 operator*(const Vec4& lhs,float scalar);
     Vec4 operator*(float scalar,const Vec4& rhs);
     Vec4 operator/(const Vec4& lhs,float scalar);
     Vec4 operator+(const Vec4& lhs,const Vec4& rhs);

     void normalize(float * values);

     void perspectiveDivision(Vec4& vec4);

     bool isInfinit(const Vec4& vec4);
	
} /* my_gl */


#endif /* end of include guard: VEC4_HPP */
