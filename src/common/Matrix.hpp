/*
 * =====================================================================================
 *
 *       Filename:  MatrixBase.hpp
 *
 *    Description:  simple float 4x4 3x3 matrix impl
 *    in OpenGL ,matrix is column-priority  
 *
 *        Version:  1.0
 *        Created:  2011-9-13 15:42:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef MATRIX_HPP

#define MATRIX_HPP


#include <cstddef>

#include "VecFwd.hpp"

namespace my_gl {


     template<size_t L=4>
     class MatrixBase {
     public:

	  /** 
	   * @brief construct a matrix with zero (but w coord is 1)
	   * 
	   * @param fillZero
	   */
	  MatrixBase(bool fillZero=true) ;

	  MatrixBase(const float* values,bool rowFirst=false) ;

	  MatrixBase& operator=(const MatrixBase& rhs) ;

	  void operator*=(const MatrixBase& rhs) ;

	  float& operator()(size_t columnIdx,size_t rowIdx) ;

	  float const& operator()(size_t columnIdx,size_t rowIdx) 
	       const ;
     
	  MatrixBase operator*(const MatrixBase& rhs)const;

     
	  VecBase<L> operator*(const VecBase<L>& rhs)const;


	  const float* values()const ;

	  static MatrixBase identity() ;

	  	  void swap(MatrixBase& rhs) ;

	  const static int LENGTH=L;

	  MatrixBase inverse()const;

	  MatrixBase transpose()const;

	  const static int ELEMENTS_NUMBER=LENGTH*LENGTH;

     private:
	  float _columnPriorityValues[ELEMENTS_NUMBER];

     };


     /** 
      * @brief Matrix 4x4
      */
     typedef MatrixBase<4> Matrix4;

     /** 
      * @brief Matrix 3x3
      */
     typedef MatrixBase<3> Matrix3;

     /** 
      * @brief Matrix 2x2
      */
     typedef MatrixBase<2> Matrix2;


     extern template class MatrixBase<3>;
     extern template class MatrixBase<4>;
     extern template class MatrixBase<2>;

     /** 
      * @brief return upper-left 3x3 matrix of matrix4
      * 
      * @param matrix4
      * 
      * @return 
      */
     Matrix3 upperLeft(const Matrix4& matrix4);

     Matrix4 translate(float x,float y,float z) ;

     Matrix4 scale(float x,float y,float z) ;

     Matrix4 rotate(float angle,float x,float y,float z) ;

     template<size_t L>
     void inplaceMultiVec(const MatrixBase<L>& lhs,float *pointer) ;

     template<size_t L>
     void inplaceMultiVec(const MatrixBase<L>& lhs,VecBase<L>& vector) ;

     template<size_t L>
     void multiVecTo(const MatrixBase<L>& lhs,const VecBase<L>& vector,float *result) ;

     template<size_t L>
     void multiVecTo(const MatrixBase<L>& lhs,const float* vector,float * result);

     template<size_t L>
     void multiVecTo(const MatrixBase<L>& lhs,const VecBase<L>& vector, VecBase<L>& result) ;

     template<size_t L>
     float rowColumnExprValue(const MatrixBase<L>& matrix);

     template<size_t L>
         float inverseMod(const MatrixBase<L>& matrix,
	       int column,int row);
} /* my_gl */



#endif /* end of include guard: MATRIX_HPP */
