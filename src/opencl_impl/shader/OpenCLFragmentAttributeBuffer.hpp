/*
 * =====================================================================================
 *
 *       Filename:  OpenCLFragmentAttributeBuffer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-28 20:20:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENCL_FRAGMENT_ATTRIBUTE_BUFFER_HPP

#define OPENCL_FRAGMENT_ATTRIBUTE_BUFFER_HPP

#include <CL/cl.hpp>

#include "opencl_impl/CLParameterBinder.hpp"
#include "soft_impl/shader/FragmentAttributeBuffer.hpp"

namespace my_gl
{
     class OpenCLFragmentAttributeBuffer :public FragmentAttributeBuffer ,CLParameterBinder{
     public:
	  OpenCLFragmentAttributeBuffer 
	     (size_t width,size_t height,size_t attributeNumber,cl::Context CLContext);

	  void setActiveFragCoordsNumber(int number);

	  void storeActiveFragCoords(cl::CommandQueue commandQueue);

	  virtual ~OpenCLFragmentAttributeBuffer ();

	  virtual int bindToKernel(cl::Kernel kernel,int idx);

	  struct ReadLock
	  {
	       ReadLock(OpenCLFragmentAttributeBuffer& toLock,cl::CommandQueue commandQueue,void *p);
	       ~ReadLock();
	       private:
	       OpenCLFragmentAttributeBuffer & _toLock;
	       cl::CommandQueue _commandQueue;
	       void *_p;
	  };

	  friend struct ReadLock;

	  void *beginRead(cl::CommandQueue commandQueue);

	  void endRead(cl::CommandQueue commandQueue,void *p);


     private:

	  int _activeFragCoordsNumber;

	  cl::Context _CLContext;
	  cl::Buffer _fragmentAttributeCLBuffer;
	  cl::Buffer _activeFragCoordsCLBuffer;


     };
	
} /* my_gl */


#endif /* end of include guard: OPENCL_FRAGMENT_ATTRIBUTE_BUFFER_HPP */
