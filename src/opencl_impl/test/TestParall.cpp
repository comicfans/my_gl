/*
 * =====================================================================================
 *
 *       Filename:  TestParall.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-14 11:18:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <cassert>
#include <memory>
#include <iostream>

#include <CL/cl.hpp>
#include "opencl_impl/CLSource.hpp"


int main(int argc, const char *argv[])
{

     /* * 
     std::vector<cl::Platform> platforms;

     cl::Platform::get(& platforms);

     assert(platforms.size() || "no Platform found");

     cl_context_properties properties[] = 
     { CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};

     cl::Context _openCLContext(CL_DEVICE_TYPE_CPU,properties);
     */

     cl::Context _openCLContext(CL_DEVICE_TYPE_DEFAULT);

     my_gl::CLSource source("TestParall.cl");

     std::vector<cl::Device> devices= 
	  _openCLContext.getInfo<CL_CONTEXT_DEVICES>();

     assert(devices.size()||"no opencl device found");


     cl::Device defaultDevice=devices[0];

     std::vector<size_t> workItemSizes;

     defaultDevice.getInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES,&workItemSizes);

     assert(workItemSizes.size()>=2 || "device not support 2 dim ");

     cl::CommandQueue _commandQueue=
	  cl::CommandQueue(_openCLContext,defaultDevice);

     my_gl::CLSource clSource("TestParall.cl");

     cl::Program program(_openCLContext,clSource.getSources());

     cl_int buildResult=program.build(devices);

     assert(buildResult==CL_SUCCESS);

     cl::Kernel _expendKernel=cl::Kernel(program,"testParall");

     const int size=16;

     std::unique_ptr<float[]> buff(new float[size*size*4+4]);

     std::unique_ptr<float[]> input(new float[size*size*4+4]);


     void *addrBuf=buff.get();

     if (uint32_t(addrBuf)%16!=0)
     {
	  std::cout<<"output not aligned";

	  addrBuf=(void*)((uint32_t(addrBuf)+16)/16*16);

	  std::cout<<"align to "<<addrBuf<<'\n';

     }
     

     void *addrInput=input.get();

     if (uint32_t(addrInput)%16!=0)
     {
	  std::cout<<"input not aligned";

	  addrInput=(void*)((uint32_t(addrInput)+16)/16*16);

	  std::cout<<"align to "<<addrInput<<'\n';
     }

     cl::Buffer inputBuffer=cl::Buffer(_openCLContext,
	       CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
	       size*size*4*sizeof(float),addrInput);

     cl::Buffer _outputCLBuffer=cl::Buffer(_openCLContext,
	       CL_MEM_WRITE_ONLY|CL_MEM_USE_HOST_PTR,
	       size*size*4*sizeof(float),addrBuf);

     cl::NDRange _ndRange=cl::NDRange(size,size);

     _expendKernel.setArg(0,_outputCLBuffer);

     _expendKernel.setArg(1,inputBuffer);

     for (int i=0; i<10000000; ++i)
     {

	  cl_int result=
	  _commandQueue.enqueueNDRangeKernel(
		    _expendKernel,
		    cl::NullRange,
		    _ndRange,
		    cl::NDRange(1,1));

	  assert(result==CL_SUCCESS);

	  _commandQueue.finish();
     }

     return 0;
}
