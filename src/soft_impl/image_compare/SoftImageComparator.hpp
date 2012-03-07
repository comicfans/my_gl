/*
 * =====================================================================================
 *
 *       Filename:  SoftImageComparator.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 11:56:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SOFT_IMAGE_COMPARATOR_HPP

#define SOFT_IMAGE_COMPARATOR_HPP

#include "common/image_compare/ImageComparator.hpp"

namespace my_gl {
     template<class T>
     class SoftImageComparator :public ImageComparator{
     public:

	  virtual double compare(Image& image1,Image& image2);

	  virtual ~SoftImageComparator ();
     };

     typedef SoftImageComparator<float> SoftFloatImageComparator;
     typedef SoftImageComparator<double> SoftDoubleImageComparator;

     extern template class SoftImageComparator<float>;
     extern template class SoftImageComparator<double>;
	
} /* my_gl */



#endif /* end of include guard: SOFT_IMAGE_COMPARATOR_HPP */
