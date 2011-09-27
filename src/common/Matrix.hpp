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
	  Matrix(bool fillZero=true) noexcept;

	  Matrix(const float* values,bool rowFirst=true) noexcept;

	  Matrix& operator=(const Matrix& rhs) noexcept;

	  void operator*=(const Matrix& rhs) noexcept;

	  float& operator()(size_t rowIdx,size_t columnIdx) noexcept;

	  float const& operator()(size_t rowIdx,size_t columnIdx) 
	       const noexcept;

	  const float* values()const noexcept;

	  static Matrix identity() noexcept;

	  static Matrix translate(float x,float y,float z) noexcept;

	  static Matrix scale(float x,float y,float z) noexcept;

	  //TODO 
	  static Matrix rotate(float angle,float x,float y,float z) noexcept;

	  void swap(Matrix& rhs) noexcept;

	  const static int LENGTH=4;

	  const static int ELEMENTS_NUMBER=LENGTH*LENGTH;

     private:
	  float _rowFirstArray[ELEMENTS_NUMBER];

     };

     void inplaceMultiVector(const Matrix& lhs,float *pointer) noexcept;

     struct Vector;

     void inplaceMultiVector(const Matrix& lhs,Vector& vector) noexcept;

     void multiVectorTo(const Matrix& lhs,const Vector& vector,float *result) noexcept;

     void multiVectorTo(const Matrix& lhs,const float* vector,float * result)noexcept;

     void multiVectorTo(const Matrix& lhs,const Vector& vector, Vector& result) noexcept;

} /* my_gl */



#endif /* end of include guard: MATRIX_HPP */
