/*
 * =====================================================================================
 *
 *       Filename:  Matrix.hpp
 *
 *    Description:  simple float 4x4 matrix vector impl
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

namespace my_gl {


     class Matrix {
     public:

	  /** 
	   * @brief construct a matrix with zero (but w coord is 1)
	   * 
	   * @param fillZero
	   */
	  Matrix(bool fillZero=true) ;

	  Matrix(const float* values,bool rowFirst=true) ;

	  Matrix& operator=(const Matrix& rhs) ;

	  void operator*=(const Matrix& rhs) ;

	  float& operator()(size_t rowIdx,size_t columnIdx) ;

	  float const& operator()(size_t rowIdx,size_t columnIdx) 
	       const ;

	  const float* values()const ;

	  static Matrix identity() ;

	  static Matrix translate(float x,float y,float z) ;

	  static Matrix scale(float x,float y,float z) ;

	  //TODO 
	  static Matrix rotate(float angle,float x,float y,float z) ;

	  void swap(Matrix& rhs) ;

	  const static int LENGTH=4;

	  Matrix inverse()const;

	  Matrix transpose()const;

	  const static int ELEMENTS_NUMBER=LENGTH*LENGTH;

     private:
	  float _rowFirstArray[ELEMENTS_NUMBER];

     };

     void inplaceMultiVec4(const Matrix& lhs,float *pointer) ;

     struct Vec4;

     void inplaceMultiVec4(const Matrix& lhs,Vec4& vector) ;

     void multiVec4To(const Matrix& lhs,const Vec4& vector,float *result) ;

     void multiVec4To(const Matrix& lhs,const float* vector,float * result);

     void multiVec4To(const Matrix& lhs,const Vec4& vector, Vec4& result) ;

} /* my_gl */



#endif /* end of include guard: MATRIX_HPP */
