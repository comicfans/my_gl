/*
 * =====================================================================================
 *
 *       Filename:  Vec.hpp
 *
 *    Description:  simple vector3 and vector4 
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

#ifndef VEC_HPP


#define VEC_HPP

#include <cstddef>

namespace my_gl {
	  

     template<size_t L>
     struct VecBase{
    
	  public:

	       VecBase(bool fillZero=true);

	       VecBase(const float* values,size_t copyN=L);

		   VecBase(float x,float y=0,float z=0,float w=1);

	       VecBase(const VecBase& rhs);

	       VecBase& operator=(const VecBase& rhs);

	       void operator*=(float scalar);

	       void operator/=(float scalar);

	       void operator+=(const VecBase& rhs);

	       VecBase operator*(float scalar)const ;

	       VecBase operator/(float scalar)const;

	       VecBase operator+(const VecBase<L>& rhs)const;

	       VecBase operator-(const VecBase<L>& rhs)const;

	       static const size_t LENGTH=L;

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

	       bool operator==(const VecBase& rhs)const;

	       VecBase operator-()const;
	
       
	  private:
	       float _values[LENGTH];
     	/* data */
     };

     typedef VecBase<3> Vec3;
     typedef VecBase<4> Vec4;

     void normalize(Vec3& vec);

     float dotProduct(const Vec3& lhs,const Vec3& rhs);

     Vec4 componentMul(const Vec4& lhs,const Vec4& rhs);

     void perspectiveDivision(Vec4& vec4);

     float length(const Vec3& vec3);

     bool isInfinit(const Vec4& vec4);

	
} /* my_gl */


#endif /* end of include guard: VEC_HPP */
