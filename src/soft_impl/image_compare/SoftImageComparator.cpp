/*
 * =====================================================================================
 *
 *       Filename:  SoftImageComparator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 12:02:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SoftImageComparator.hpp"
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <array>
#include <boost/multi_array.hpp>

#include "common/image_compare/Image.hpp"

namespace my_gl {


     template<class T>
     static T RGBToGray(const RGBARef& rgba)
     {
	  //comes from wiki ,these weights depend on the exact 
	  //choice of the RGB primaries, but are typical
	  T sum=rgba.R*30+rgba.G*59+rgba.B*11;
	  return sum/100/255;
     }



     template<class T>
     struct GrayImageType
     {
	  typedef typename boost::multi_array<T,2> GrayImage;
     };

     template<class T>
     void RGBImageToGrayImage(Image& rgbImage,
	       typename GrayImageType<T>::GrayImage& grayImage)
     {
	  for (int y=0; y<rgbImage.height; ++y)
	  {
	       for (int x=0; x<rgbImage.width; ++x)
	       {
		    grayImage[y][x]=RGBToGray<T>(rgbImage(y,x));
	       }
	  }
     }

     template<class T>
     double SoftImageComparator<T>::compare(Image& image1,Image& image2  )
     {
	  std::array<int ,2> heightWidth{image1.height,image1.width};

	  typename GrayImageType<T>::GrayImage 
	       grayImage1(heightWidth),
	       grayImage2(heightWidth);

	  RGBImageToGrayImage<T>(image1,grayImage1);
	  RGBImageToGrayImage<T>(image2,grayImage2);

	  int length=image1.height*image1.width;

	  T zero=0;

	  T average1=std::accumulate<T*,T>
	       (grayImage1.data(),grayImage1.data()+length,zero)/length,

		average2=std::accumulate<T*,T>(grayImage2.data(),
			  grayImage2.data()+length,zero)/length;


	  T numerator=0,
	    denominatorLeftSq=0,
	    denominatorRightSq=0;

	  for(int i=0;i<length;++i)
	  {
	       T &gray1=grayImage1.data()[i],
		     &gray2=grayImage2.data()[i];

	       numerator+=(gray1-average1)*(gray2-average2);
	       denominatorLeftSq+=std::pow<T>(gray1-average1,2);
	       denominatorRightSq+=std::pow<T>(gray2-average2,2);
	  }

	  T denominator=std::sqrt(denominatorLeftSq*denominatorRightSq);

	  if ((denominator==0 )&& (numerator==0))
	  {
	       return 1;
	  }

	  if (denominator==0)
	  {
	       return DBL_MAX;
	  }

	  return numerator/denominator;

     }
	  
     template<class T>
     SoftImageComparator<T>::~SoftImageComparator(){}

     template class SoftImageComparator<double>;
     template class SoftImageComparator<float>;
	
} /* my_gl */
