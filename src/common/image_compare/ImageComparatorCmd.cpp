/*
 * =====================================================================================
 *
 *       Filename:  ImageComparatorCmd.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 13:30:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <boost/assert.hpp>

#include "EasyBmp/EasyBMP.h"
#include "soft_impl/image_compare/SoftImageComparator.hpp"
#include "opencl_impl/image_compare/OpenCLImageComparator.hpp"

#include "ImageComparator.hpp"
#include "Image.hpp"

using std::cout;
int main(int argc, const char *argv[])
{
     BMP bmp1,bmp2;

     bmp1.ReadFromFile("1.bmp");
     bmp2.ReadFromFile("2.bmp");

     my_gl::Image image1(bmp1.TellWidth(),bmp1.TellHeight());
     my_gl::Image image2(bmp2.TellWidth(),bmp2.TellHeight());
    
     BOOST_ASSERT_MSG(image1.width==image2.width,"width not equal");
     BOOST_ASSERT_MSG(image1.height==image2.height,"height not equal");
     

     for(int y=0;y<image1.height;++y)
     {
	  for (int x=0; x<image1.width; ++x)
	  {
	       my_gl::RGBARef ref1=image1(y,x),
		       ref2=image2(y,x);

	       RGBApixel *data1=bmp1(x,y),
			 *data2=bmp2(x,y);

	       ref1.R=data1->Red;
	       ref1.G=data1->Green;
	       ref1.B=data1->Blue;

	       ref2.R=data2->Red;
	       ref2.G=data2->Green;
	       ref2.B=data2->Blue;
	  }
     }

     cout<<"bmp load ok\n";

     cout<<"soft float compare begin\n";
     my_gl::SoftFloatImageComparator softFloatImageComparator;
     cout<<"result is "<<softFloatImageComparator.compare(image1,image2)<<"\n";
     cout<<"soft float compare end\n";

     cout<<"soft double compare begin\n";
     my_gl::SoftDoubleImageComparator softDoubleImageComparator;
     cout<<"result is "<<softDoubleImageComparator.compare(image1,image2)<<"\n";
     cout<<"soft double compare end\n";


     cout<<"opencl compare begin\n";
     my_gl::OpenCLImageComparator openCLImageComparator;
     cout<<"result is "<<openCLImageComparator.compare(image1,image2)<<"\n";
     cout<<"opencl compare end\n";


     return 0;
}
