/*
 * =====================================================================================
 *
 *       Filename:  OpenCLDepthBuffer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-8 15:48:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENCL_DEPTH_BUFFER_HPP

#define OPENCL_DEPTH_BUFFER_HPP

#include "soft_impl/pipeline/DepthBuffer.hpp"

namespace my_gl {
     class OpenCLDepthBuffer:public DepthBuffer {
     public:
	  
	  OpenCLDepthBuffer(size_t width,size_t height);
     	
	  virtual ~OpenCLDepthBuffer ();

	  void * getRawData();
     
     private:
     	/* data */
     };
	
} /* my_gl */


#endif /* end of include guard: OPENCL_DEPTH_BUFFER_HPP */
