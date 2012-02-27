/*
 * =====================================================================================
 *
 *       Filename:  OpenCLFragmentAttributeBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-28 20:25:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLFragmentAttributeBuffer.hpp"

namespace my_gl {

     OpenCLFragmentAttributeBuffer::OpenCLFragmentAttributeBuffer 
	  (size_t width,size_t height,size_t attributeNumber,cl::Context CLContext)
	  :FragmentAttributeBuffer(width,height,attributeNumber),_CLContext(CLContext){}


     OpenCLFragmentAttributeBuffer::~OpenCLFragmentAttributeBuffer(){}

	  
     int OpenCLFragmentAttributeBuffer::bindToKernel(cl::Kernel kernel,int idx)
     {
	  const void *temp=&(*this)(0,0)[0];
	  void *nonConstP=const_cast<void*>(temp);
 
	  //bind FragmentAttributeBuffer
	  size_t fragmentAttributeBufferSize=width() *height()
	       * attributeNumber() *  sizeof(Vec4);

	  
	  _fragmentAttributeCLBuffer=cl::Buffer(_CLContext,
		    CL_MEM_WRITE_ONLY|CL_MEM_USE_HOST_PTR,
		    fragmentAttributeBufferSize, nonConstP);
	  kernel.setArg(idx++,_fragmentAttributeCLBuffer);

	  //bind active fragments
	  size_t activeFragmentsBufferSize=_activeFragCoordsNumber*2*sizeof(cl_int);

	  _activeFragCoordsCLBuffer=cl::Buffer(_CLContext,
		    CL_MEM_WRITE_ONLY,activeFragmentsBufferSize,nullptr);

	  kernel.setArg(idx++,_activeFragCoordsCLBuffer);

	  return idx;
     }

     void OpenCLFragmentAttributeBuffer::setActiveFragCoordsNumber(int number)
     {
	  _activeFragCoordsNumber=number;
     }

     /** 
      * @brief struct for read OpenCL WinCoord back
      */
     struct ActiveFragmentCoord
     {
	  cl_int x;
	  cl_int y;
     };
     void OpenCLFragmentAttributeBuffer::storeActiveFragCoords(cl::CommandQueue commandQueue)
     {
	  void *mappedBuffer=commandQueue.enqueueMapBuffer(_activeFragCoordsCLBuffer,true,
		    CL_MAP_READ,0,_activeFragCoordsNumber);

	  ActiveFragmentCoord* pActiveFragmentCoord=
	       reinterpret_cast<ActiveFragmentCoord*>(mappedBuffer);

	  for(int i=0;i<_activeFragCoordsNumber;++i)
	  {
	       _activeFragWinCoords.push_back(WinCoord(pActiveFragmentCoord[i].x,
			      pActiveFragmentCoord[i].y));

	  }

	  commandQueue.enqueueUnmapMemObject(_activeFragCoordsCLBuffer,mappedBuffer);
	
     }

} /* my_gl */
