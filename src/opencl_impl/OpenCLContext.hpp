/*
 * =====================================================================================
 *
 *       Filename:  OpenCLContext.hpp
 *
 *    Description:  use opencl to do hard work
 *
 *        Version:  1.0
 *        Created:  2012-1-5 16:03:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENCL_CONTEXT_HPP

#define OPENCL_CONTEXT_HPP

#include "soft_impl/SoftContext.hpp"

namespace my_gl {

     class OpenCLContext :public SoftContext{
     public:
     	OpenCLContext (size_t width=600,size_t height=400);

     	virtual ~OpenCLContext ();
     
     private:
     	/* data */
     };
	
} /* my_gl */


#endif /* end of include guard: OPENCL_CONTEXT_HPP */
