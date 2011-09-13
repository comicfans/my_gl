/*
 * =====================================================================================
 *
 *       Filename:  Matrix.cpp
 *
 *    Description:  implementation of Matrix float 4x4
 *
 *        Version:  1.0
 *        Created:  2011-9-13 15:58:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Matrix.hpp"

#include <algorithm>
#include <utility>

using std::fill_n;
using std::copy;

namespace my_gl {

     Matrix::Matrix(bool fillZero)noexcept
     {
	  if (fillZero)
	  {
	  fill_n(_rowFirstArray,ELEMENTS_NUMBER,0);
	  }
	  //init w to 1
	  (*this)(LENGTH-1,LENGTH-1)=1;
     }

     Matrix & Matrix::operator=(const Matrix &rhs)noexcept
     {
	  copy(rhs._rowFirstArray,rhs._rowFirstArray+ELEMENTS_NUMBER,
		    _rowFirstArray);
	  return *this;
     }

     void Matrix::operator*=(const my_gl::Matrix &rhs)noexcept
     {
	  Matrix temp;

	  for(int row=0;row<LENGTH;++row)
	  {
	       for(int column=0;column<LENGTH;++column)
	       {
		    for (int i=0; i<LENGTH; ++i)
		    {
			 temp(row,column)+=
			      (*this)(row,i)*rhs(i,column);
		    }
	       }
	  }

	  this->swap(temp);
     }

     void Matrix::swap(my_gl::Matrix &rhs)noexcept
     {
	  std::swap(_rowFirstArray,rhs._rowFirstArray);
     }

     float& Matrix::operator()(size_t rowIdx,  size_t columnIdx)noexcept
     {
	  return _rowFirstArray[rowIdx*LENGTH+columnIdx];
     }

     float const& Matrix::operator()
	  (size_t rowIdx,size_t columnIdx)const  noexcept
	  {
	       return const_cast<Matrix&>(*this)(rowIdx,columnIdx);
	  }

     Matrix Matrix::identity()noexcept
     {
	  Matrix ret;
	  for (int i=0; i<LENGTH-1; ++i)
	  {
	       ret(i,i)=1;
	  }
	  return ret;
     }

     Matrix Matrix::translate(float x,  float y,  float z)noexcept
     {
	  Matrix ret=identity();

	  ret(0,3)=x;
	  ret(1,3)=y;
	  ret(2,3)=z;

	  return ret;
     }

     Matrix Matrix::scale(float x,float y,float z)noexcept
     {
	  Matrix ret=identity();

	  ret(0,0)=x;
	  ret(1,1)=y;
	  ret(2,2)=z;

	  return ret;
     }

     void inplaceMultiVector(const Matrix& lhs,float *pointer)
     {


	  float temp[Matrix::LENGTH]={0,0,0,0};
	  for (int i=0; i<Matrix::LENGTH; ++i)
	  {
	       for (int j=0; j<Matrix::LENGTH; ++j)
	       {
		    temp[i]+=lhs(i,j)*pointer[j];
	       }
	  }

	  copy(temp,temp+Matrix::LENGTH,pointer);
     }
	
} /* my_gl */
