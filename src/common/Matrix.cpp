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
using std::swap;
namespace my_gl {

     Matrix::Matrix(bool fillZero)noexcept
     {
	  if (fillZero)
	  {
	  fill_n(_rowFirstArray,ELEMENTS_NUMBER,0);
	  }
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
	  ::swap(_rowFirstArray,rhs._rowFirstArray);
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
	  for (int i=0; i<LENGTH; ++i)
	  {
	       ret(i,i)=1;
	  }
	  return ret;
     }
	
} /* my_gl */
