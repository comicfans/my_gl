/*
 * =====================================================================================
 *
 *       Filename:  OpenCLImageComparator.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/6 17:18:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENCL_IMAGE_COMPARATOR_HPP

#define OPENCL_IMAGE_COMPARATOR_HPP

#include <CL/cl.hpp>

#include "common/image_compare/ImageComparator.hpp"

namespace my_gl {

     class OpenCLImageComparator :public ImageComparator{
     public:

	  OpenCLImageComparator();

	  virtual double compare(Image& image1,Image& image2);

	  virtual ~OpenCLImageComparator ();
     
     private:

     
	  void imagePreprocess(Image& image,cl::Buffer& grayValueBuffer,double& averageGray);
	  double clBufferFloatSum(cl::Buffer buffer,int floatElementNumber);

	  cl::Context _context;
	  cl::CommandQueue _commandQueue;
	  cl::Program _program;

	  cl::Kernel _RGBPreprocessKernel;
	  cl::Kernel _recursionAverageKernel;
	  cl::Kernel _calculateSimilarKernel;
	  cl::Kernel _recursionSumKernel;
     };
	
} /* my_gl */


#endif /* end of include guard: OPENCL_IMAGE_COMPARATOR_HPP */
