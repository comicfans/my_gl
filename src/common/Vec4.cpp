/*
 * =====================================================================================
 *
 *       Filename:  Vec4.cpp
 *
 *    Description:  implementation of Vec4
 *
 *        Version:  1.0
 *        Created:  2011-9-14 14:00:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Vec4.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>

using std::fill_n;
using std::copy_n;
using std::sin;
using std::cos;
using std::sqrt;
using std::for_each;
using std::divides;
using std::plus;
using std::transform;
using std::bind;
using std::placeholders::_1;

namespace my_gl {

     Vec4::Vec4(bool fillZero)
     {
	  if (fillZero)
	  {
	       fill_n(_values,LENGTH,0);
	  }
	  //always make w component 1
	  _values[LENGTH-1]=1;
     }

     Vec4::Vec4(float fx,float fy,float fz,float fw)
     {
	  _values[0]=fx;
	  _values[1]=fy;
	  _values[2]=fz;
	  _values[3]=fw;
     }


     float& Vec4::operator()(size_t idx)
     {
	  assert(idx<LENGTH);
	  return _values[idx];
     }

     float& Vec4::operator[](size_t idx)
     {return operator()(idx);}

     const float& Vec4::operator[](size_t idx)const 
     {return operator[](idx);}

     const float& Vec4::operator()(size_t idx) const 
     {
	  return const_cast<Vec4&>(*this)(idx);
     }

     Vec4& Vec4::operator=(const Vec4& rhs)
     {
	  copy_n(rhs._values,LENGTH,_values);
	  return *this;
     }

     const float* Vec4::values()const 
     {return _values;}

     float * Vec4::values()
     {return _values;}

     const float& Vec4::w()const
     {return _values[3];}

     const float& Vec4::x()const
     {return _values[0];}

     const float& Vec4::y()const
     {return _values[1];}

     const float& Vec4::z()const
     {return _values[2];}

     inline float sq(float value){return value*value;}

     void normalize(float * values)
     {
	  float lengthSq=sq(values[0])+sq(values[1])+sq(values[2]);

	  float length=sqrt(lengthSq);

	  for_each(values,values+3,bind(divides<float>(),_1,length));
     }

     void Vec4::operator*=(float scalar)
     {
	  for(float& component:_values)
	  {
	       component*=scalar;
	  }
     }

     Vec4 operator*(const Vec4& lhs,float scalar)
     {
	  Vec4 ret=lhs;
	  ret*=scalar;
	  return lhs;
     }

     Vec4 operator*(float scalar,const Vec4& rhs)
     {
	  return rhs*scalar;
     }

     void Vec4::operator/=(float scalar)
     {
	  (*this)*=1/scalar;
     }

     void Vec4::operator+=(const Vec4& rhs)
     {
	  transform(_values,_values+LENGTH,
		    rhs._values,_values,
		    plus<float>());
     }

     Vec4 operator+(const Vec4& lhs,const Vec4& rhs)
     {
	  Vec4 ret=lhs;
	  ret+=rhs;
	  return ret;
     }

     void perspectiveDivision(Vec4& vec4)
     {
	  assert(!isInfinit(vec4));
	  vec4/=vec4.w();
     }

     bool isInfinit(const Vec4& vec4)
     {
	  return vec4.w()==0;
     }

} /* my_gl */
