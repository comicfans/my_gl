/*
 * =====================================================================================
 *
 *       Filename:  MatrixBase<L>.cpp
 *
 *    Description:  implementation of MatrixBase float 4x4
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

#include "Vec.hpp"

using std::fill_n;
using std::copy_n;
using std::swap;
using std::cos;
using std::sin;

namespace my_gl {


     template<size_t L>
     MatrixBase<L>::MatrixBase(bool fillZero)
     {
	  if (fillZero)
	  {
	       fill_n(_columnPriorityValues,ELEMENTS_NUMBER,0);
	  }
     }

     template<size_t L>
     MatrixBase<L>::MatrixBase(const float* values,bool rowFirst)
     {
	  if (!rowFirst)
	  {
	       copy_n(values,ELEMENTS_NUMBER,_columnPriorityValues);
	  }
	  else
	  {
	       for (int column=0; column<LENGTH; ++column)
	       {
		    for (int row=0; row<LENGTH; ++row)
		    {
			 _columnPriorityValues[column*LENGTH+row]
			      =values[row*LENGTH+column];
		    }
	       }
	  }
     }



     template<size_t L>
     static void exclude(const MatrixBase<L>& matrix,int column,int row,
	       MatrixBase<L-1>& result)
     {
	  for (int columnFrom=0,columnTo=0; 
		    columnFrom<MatrixBase<L>::LENGTH; ++columnFrom)
	  {
	       if (columnFrom==column)
	       {
		    continue;
	       }
	       
	       for (int rowFrom=0,rowTo=0; 
			 rowFrom<MatrixBase<L>::LENGTH; ++rowFrom)
	       {
		    if (rowFrom==row)
		    {
			 continue;
		    }
		    result(columnTo,rowTo)=
			 matrix(columnFrom,rowFrom);
		    ++rowTo;
	       }
	       ++columnTo;
	  }

     }

     template<>
	  void exclude<2>(const MatrixBase<2>& matrix,int column,int row,
		    MatrixBase<1>& result)
	  {
	       result(0,0)=matrix(1-column,1-row);
	  }

     template<size_t L>
     float rowColumnExprValue(const MatrixBase<L>& matrix)
     {
	  float result=0;

	  for (int column=0; column<MatrixBase<L>::LENGTH; ++column)
	  {
	       int sign=(column%2==0?1:-1);

	       float product=matrix(column,0);

	       MatrixBase<L-1> tmp;

	       exclude(matrix,column,0,tmp);

	       product*=rowColumnExprValue(tmp);

	       result+=sign*product;
	  }

	  return result;
	  }

     template<>
	  float rowColumnExprValue<1>(const MatrixBase<1>& matrix)
	  {
	       return matrix(0,0);
	  }

     template<size_t L>
         float inverseMod(const MatrixBase<L>& matrix,
	       int column,int row)
     {

	  //remove row/column element to make a 3x3 matrix
	  MatrixBase<L-1> tmp;

	  exclude(matrix,column,row,tmp);

	  float result=rowColumnExprValue(tmp);

	  if ((row+column)%2)
	  {
	       result*=-1;
	  }

	  return result;
     }

     template<>
	  float inverseMod(const MatrixBase<1>& matrix,
		    int column,int row)
	  {
	       return matrix(0,0);
	  }

	 template<size_t L>
     MatrixBase<L> MatrixBase<L>::inverse() const 
     {
	  MatrixBase<L> ret;

	  float detValue=rowColumnExprValue(*this);

	  for (int row=0; row<LENGTH; ++row)
	  {
	       for (int column=0; column<LENGTH; ++column)
	       {
		    // det(Aij).transpose()/det(A)
		    ret(row,column)=
			 inverseMod(*this,column,row)/detValue;
	       }
	  }

	  return ret;

     }

	 template<size_t L>
     MatrixBase<L> & MatrixBase<L>::operator=(const MatrixBase<L> &rhs)
     {
	  copy_n(rhs._columnPriorityValues,ELEMENTS_NUMBER,
		    _columnPriorityValues);
	  return *this;
     }

	 template<size_t L>
     void MatrixBase<L>::operator*=(const MatrixBase<L>&rhs)
     {
	  MatrixBase<L> temp;

	  for(int column=0;column<LENGTH;++column)
	  {
	       for(int row=0;row<LENGTH;++row)
	       {
		    for (int i=0; i<LENGTH; ++i)
		    {
			 temp(column,row)+=
			      (*this)(i,row)*rhs(column,i);
		    }
	       }
	  }

	  this->swap(temp);
     }

	 template<size_t L>
	      void MatrixBase<L>::swap(MatrixBase<L> &rhs)
	      {
		   std::swap(_columnPriorityValues,rhs._columnPriorityValues);
	      }

	 template<size_t L>
	      float& MatrixBase<L>::operator()(size_t columnIdx,  size_t rowIdx)
	      {
		   return _columnPriorityValues[columnIdx*LENGTH+rowIdx];
	      }

	 template<size_t L>
	      float const& MatrixBase<L>::operator()
	      (size_t columnIdx,size_t rowIdx)const  
	      {
		   return _columnPriorityValues[columnIdx*LENGTH+rowIdx];
	      }

	 template<size_t L>
	      MatrixBase<L> MatrixBase<L>::identity()
	      {
		   MatrixBase<L> ret;
		   for (int i=0; i<LENGTH; ++i)
		   {
			ret(i,i)=1;
		   }
		   return ret;
	      }

	 Matrix4 rotate(float angle,float x,float y,float z)
	 {
	      Matrix4 ret=Matrix4::identity();

	      Vec3 rotateAxis={x,y,z};

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
	      ret(1,0)=xy*onePlusC-zs;
	      ret(2,0)=xz*onePlusC+ys;
	      ret(0,1)=xy*onePlusC+zs;
	      ret(1,1)=y*y*onePlusC+c;
	      ret(2,1)=yz*onePlusC-xs;
	      ret(0,2)=xz*onePlusC-ys;
	      ret(1,2)=yz*onePlusC+xs;
	      ret(2,2)=z*z*onePlusC+c;

	      return ret;
	 }

	 Matrix4 translate(float x,  float y,  float z)
	 {
	      Matrix4 ret=Matrix4::identity();

	      ret(3,0)=x;
	      ret(3,1)=y;
	      ret(3,2)=z;

	      return ret;
	 }

	 Matrix4 scale(float x,float y,float z)
	 {
	      Matrix4 ret=Matrix4::identity();

	      ret(0,0)=x;
	  ret(1,1)=y;
	  ret(2,2)=z;

	  return ret;
     }

	 template<size_t L>
	      void multiVecTo(const MatrixBase<L>& lhs, const float* vector, float *result) 
	      {
		   fill_n(result,MatrixBase<L>::LENGTH,0);

		   for (int row=0; row<MatrixBase<L>::LENGTH; ++row)
		   {
			for (int column=0; column<MatrixBase<L>::LENGTH; ++column)
			{
			     result[row]+=lhs(column,row)*vector[column];
			}
		   }
	      }

	 template<size_t L>
	      MatrixBase<L> MatrixBase<L>::transpose()const
	      {
		   MatrixBase<L> ret=*this;

		   for (int i=1; i<LENGTH; ++i)
		   {
			for (int j=0; j<i; ++j)
			{
			     ::swap(ret(i,j),ret(j,i));
			}
		   }

		   return ret;
	      }

	 template<size_t L>
	      const float* MatrixBase<L>::values()const 
	      {return _columnPriorityValues;}


	 template<size_t L>
	      void inplaceMultiVec(const MatrixBase<L>& lhs,float *pointer) 
	      {
		   float temp[MatrixBase<L>::LENGTH];

		   multiVecTo(lhs,pointer,temp);

		   copy_n(temp,MatrixBase<L>::LENGTH,pointer);
	      }

	 template<size_t L>
	      void inplaceMultiVec(const MatrixBase<L>& lhs,VecBase<L>& vec) 
	      {
		   inplaceMultiVec(lhs,vec.values());
	      }

	 template<size_t L>
	      void multiVecTo(const MatrixBase<L>& lhs, const VecBase<L>& vec, VecBase<L>& result) 
	      {
		   multiVecTo(lhs,vec.values(),result.values());
	      }

	 template<size_t L>
	      void multiVecTo(const MatrixBase<L>& lhs, const VecBase<L>& vec, float *result) 
	      {
		   multiVecTo(lhs,vec,result);
	      }

	 template<size_t L>
	      MatrixBase<L> MatrixBase<L>::operator*
	      (const MatrixBase<L>& rhs)const
	      {
		   MatrixBase<L> ret(*this);
		   ret*=rhs;
		   return ret;
	      }

	 template<size_t L>
	      VecBase<L> MatrixBase<L>::operator*
	      (const VecBase<L>& rhs)const
	      {
		   VecBase<L> ret(rhs);

		   multiVecTo(*this,rhs,ret);

		   return ret;
	      }

	 template struct MatrixBase<2>;
	 template struct MatrixBase<3>;
	 template struct MatrixBase<4>;

	 template void inplaceMultiVec(const MatrixBase<4>& lhs,float *pointer) ;
	 template void inplaceMultiVec(const MatrixBase<3>& lhs,float *pointer) ;

	 template void inplaceMultiVec(const MatrixBase<4>& lhs,VecBase<4>& vector) ;

	 template void multiVecTo(const MatrixBase<4>& lhs,const VecBase<4>& vector,float *result) ;

	 template void multiVecTo(const MatrixBase<4>& lhs,const float* vector,float * result);

	 template void multiVecTo(const MatrixBase<4>& lhs,const VecBase<4>& vector, VecBase<4>& result) ;


} /* my_gl */
