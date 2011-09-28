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

     inline float sq(float value){return value*value;}

     void normalize(float * values)
     {
	  float lengthSq=sq(values[0])+sq(values[1])+sq(values[2]);

	  float length=sqrt(lengthSq);

	  for_each(values,values+3,bind(divides<float>(),_1,length));
     }


} /* my_gl */
