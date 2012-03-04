/*
 * =====================================================================================
 *
 *       Filename:  TestOpenCLCPPKernel.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/3/4 18:25:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <CL/cl.hpp>
#include "opencl_impl/CLSource.hpp"

int main(int argc, const char *argv[])
{

     cl::Context context(CL_DEVICE_TYPE_DEFAULT);


     my_gl::CLSource clSource("CPPKernel.cl");


     cl::Program
	       program(context,clSource.getSources());

	  std::vector<cl::Device> devices= 
	       context.getInfo<CL_CONTEXT_DEVICES>();


     
	  cl::CommandQueue queue(context,devices[0]);

	  cl_int err=CL_SUCCESS;


	  std::string options;

	  options.append("-x clc++ ");

	  err=program.build(devices,options.c_str());

	  cl::Kernel kernel(program,"cppKernelFunc1");

	  kernel.setArg(0,cl_int(3));

	  queue.enqueueNDRangeKernel(kernel,cl::NDRange(),cl::NDRange(100),cl::NDRange(1));

	
     return 0;
}
