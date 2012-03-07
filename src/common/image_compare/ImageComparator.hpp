/*
 * =====================================================================================
 *
 *       Filename:  ImageComparator.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 9:51:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef IMAGE_COMPARATOR_HPP

#define IMAGE_COMPARATOR_HPP

#include <cstdint>

namespace my_gl {

     struct Image;

     class ImageComparator {
	  public:
	       /** 
		* @brief a simple compare method
		* 
		* @param width width of image
		* @param height height of image
		* @param image1 image1 byte data,store as RGB (with padding)
		* @param image2 image2 byte data,store as RGB (with padding)
		* 
		* @return similar percent 1=the same 0=not same at all
		*/
	       virtual double compare(Image& image1,Image& image2)=0;

	       virtual ~ImageComparator ();

     };

} /* my_gl */


#endif /* end of include guard: IMAGE_COMPARATOR_HPP */
