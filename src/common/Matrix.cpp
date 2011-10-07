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
#include <cmath>
#include <utility>

#include "Vec4.hpp"

using std::fill_n;
using std::copy_n;
using std::swap;
using std::cos;
using std::sin;

namespace my_gl {

     Matrix::Matrix(bool fillZero)
     {
	  if (fillZero)
	  {
	  fill_n(_rowFirstArray,ELEMENTS_NUMBER,0);
	  }
	  //init w to 1
	  _rowFirstArray[ELEMENTS_NUMBER-1]=1;
     }

     Matrix::Matrix(const float* values,bool rowFirst)
     {
	  if (rowFirst)
	  {
	       copy_n(values,ELEMENTS_NUMBER,_rowFirstArray);
	  }
	  else
	  {
	       for (int column=0; column<LENGTH; ++column)
	       {
		    for (int row=0; row<LENGTH; ++row)
		    {
			 _rowFirstArray[row*LENGTH+column]
			      =values[column*LENGTH+row];
		    }
	       }
	  }
     }

     static float rowColumnExprValue(const float* rowFirstArray,
	       const int sideLength)
     {
	  float result=0;

	  for (int rowCounter=0; 
		    rowCounter<sideLength*2;
		    ++rowCounter)
	  {
	       int sign=(rowCounter<sideLength?1:-1);

	       float product=1;

	       for (int columnCounter=0; 
			 columnCounter<sideLength; 
			 ++columnCounter)
	       {
		    product*=rowFirstArray
			 [(rowCounter+sign*columnCounter)
			 %sideLength*sideLength+columnCounter];
	       }
	       result+=sign*product;
	  }

	  return result;
     }

     static float inverseMod(const Matrix& matrix,
	       const int row,const int column)
     {

	  //remove row/column element to make a 3x3 matrix
	  float tmp[3][3];
	  for (int rowFrom=0,rowTo=0; 
		    rowFrom<Matrix::LENGTH; ++rowFrom)
	  {
	       if (rowFrom==row)
	       {
		    continue;
	       }
	       
	       for (int columnFrom=0,columnTo=0; 
			 columnFrom<Matrix::LENGTH; ++columnFrom)
	       {
		    if (columnFrom==column)
		    {
			 continue;
		    }
		    tmp[rowTo][columnTo]=
			 matrix(rowFrom,columnFrom);
		    ++columnTo;
	       }
	       ++rowTo;
	  }

	  // get the value of this row/column expression

	  float result=rowColumnExprValue(&tmp[0][0],3);

	  if ((row+column)%2)
	  {
	       result*=-1;
	  }

	  return result;
     }

     Matrix Matrix::inverse() const 
     {
	  Matrix ret;

	  float exprValue=rowColumnExprValue
	       (_rowFirstArray,LENGTH);

	  for (int row=0; row<LENGTH; ++row)
	  {
	       for (int column=0; column<LENGTH; ++column)
	       {
		    ret(row,column)=
			 inverseMod(*this,row,column)/exprValue;
	       }
	  }

	  return ret;

     }

     Matrix & Matrix::operator=(const Matrix &rhs)
     {
	  copy_n(rhs._rowFirstArray,ELEMENTS_NUMBER,
		    _rowFirstArray);
	  return *this;
     }

     void Matrix::operator*=(const my_gl::Matrix &rhs)
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

     void Matrix::swap(my_gl::Matrix &rhs)
     {
	  std::swap(_rowFirstArray,rhs._rowFirstArray);
     }

     float& Matrix::operator()(size_t rowIdx,  size_t columnIdx)
     {
	  return _rowFirstArray[rowIdx*LENGTH+columnIdx];
     }

     float const& Matrix::operator()
	  (size_t rowIdx,size_t columnIdx)const  
	  {
	       return const_cast<Matrix&>(*this)(rowIdx,columnIdx);
	  }

     Matrix Matrix::identity()
     {
	  Matrix ret;
	  for (int i=0; i<LENGTH-1; ++i)
	  {
	       ret(i,i)=1;
	  }
	  return ret;
     }

     Matrix Matrix::rotate(float angle,float x,float y,float z)
     {
	  Matrix ret;

	  float rotateAxis[3]={x,y,z};

	  normalize(rotateAxis);

	  x=rotateAxis[0];
	  y=rotateAxis[1];
	  z=rotateAxis[2];

	  const float 
	       c=cos(angle),
	       onePlusC=1-c,
	       s=sin(angle),
	       xy=x*y,
	       xz=x*z,
	       yz=y*z,
	       xs=x*s,
	       ys=y*s,
	       zs=z*s;

	  ret(0,0)=x*x*onePlusC+c;
	  ret(0,1)=xy*onePlusC-zs;
	  ret(0,2)=xz*onePlusC+ys;
	  ret(1,0)=xy*onePlusC+zs;
	  ret(1,1)=y*y*onePlusC+c;
	  ret(1,2)=yz*onePlusC-xs;
	  ret(2,0)=xz*onePlusC-ys;
	  ret(2,1)=yz*onePlusC+xs;
	  ret(2,2)=z*z*onePlusC+c;

	  return ret;
     }

     Matrix Matrix::translate(float x,  float y,  float z)
     {
	  Matrix ret=identity();

	  ret(0,3)=x;
	  ret(1,3)=y;
	  ret(2,3)=z;

	  return ret;
     }

     Matrix Matrix::scale(float x,float y,float z)
     {
	  Matrix ret=identity();

	  ret(0,0)=x;
	  ret(1,1)=y;
	  ret(2,2)=z;

	  return ret;
     }

     void multiVec4To(const Matrix& lhs, const float* vector, float *result) 
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

     Matrix Matrix::transpose()const
     {
	  Matrix ret=*this;

	  for (int i=1; i<LENGTH; ++i)
	  {
	       for (int j=0; j<i; ++j)
	       {
		    ::swap(ret(i,j),ret(j,i));
	       }
	  }

	  return ret;
     }

     const float* Matrix::values()const 
     {return _rowFirstArray;}
	

     void inplaceMultiVec4(const Matrix& lhs,float *pointer) 
     {

	  float temp[Matrix::LENGTH];

	  multiVec4To(lhs,pointer,temp);

	  copy_n(temp,Matrix::LENGTH,pointer);
     }

     void inplaceMultiVec4(const Matrix& lhs,Vec4& vector) 
     {
	  inplaceMultiVec4(lhs,&vector[0]);
     }

     void multiVec4To(const Matrix& lhs, const Vec4& vector, Vec4& result) 
     {
	  multiVec4To(lhs,&vector[0],&result[0]);
     }

     void multiVec4To(const Matrix& lhs, const Vec4& vector, float *result) 
     {
	  multiVec4To(lhs,vector,result);
     }



} /* my_gl */
