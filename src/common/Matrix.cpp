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

#include "Vector.hpp"

using std::fill_n;
using std::copy_n;

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
	  copy_n(rhs._rowFirstArray,ELEMENTS_NUMBER,
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

     void multiVectorTo(const Matrix& lhs, const float* vector, float *result) noexcept
     {
	  fill_n(result,Matrix::LENGTH,0);

	  for (int i=0; i<Matrix::LENGTH; ++i)
	  {
	       for (int j=0; j<Matrix::LENGTH; ++j)
	       {
		    result[i]+=lhs(i,j)*vector[j];
	       }
	  }
     }
	

     void inplaceMultiVector(const Matrix& lhs,float *pointer) noexcept
     {

	  float temp[Matrix::LENGTH];

	  multiVectorTo(lhs,pointer,temp);

	  copy_n(temp,Matrix::LENGTH,pointer);
     }

     void inplaceMultiVector(const Matrix& lhs,Vector& vector) noexcept
     {
	  inplaceMultiVector(lhs,&vector[0]);
     }

     void multiVectorTo(const Matrix& lhs, const Vector& vector, Vector& result) noexcept
     {
	  multiVectorTo(lhs,&vector[0],&result[0]);
     }

     void multiVectorTo(const Matrix& lhs, const Vector& vector, float *result) noexcept
     {
	  multiVectorTo(lhs,vector,result);
     }



} /* my_gl */
