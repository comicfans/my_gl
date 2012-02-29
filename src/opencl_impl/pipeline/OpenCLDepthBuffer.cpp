/*
 * =====================================================================================
 *
 *       Filename:  OpenCLDepthBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-8 15:50:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLDepthBuffer.hpp"

#include <algorithm>
#include <numeric>

using std::fill_n;
namespace my_gl {

     static float orderInitValue()
     {
	  int intValue=-INT_MAX;
	  void *p=&intValue;
	  float *pFloat=reinterpret_cast<float*>(p);

	  return *pFloat;
     }

     const float OpenCLDepthBuffer::ORDER_INIT_VALUE=orderInitValue();

     OpenCLDepthBuffer::OpenCLDepthBuffer
	  (size_t width,size_t height)
	  :DepthBuffer(width,height){}

     OpenCLDepthBuffer::~OpenCLDepthBuffer(){}

     void * OpenCLDepthBuffer::getRawData()
     {
	  return &_impl[0][0];
     }

     void OpenCLDepthBuffer::orderClear()
     {
	  //TODO currently store double value,but OpenCL fp64 is a 
	  //optional extension
	  //now only use first half of memory as float data
	  //need refactor
	  float* toFill=reinterpret_cast<float*>(getRawData());

	  int fillSize=width()*height();

	  fill_n(toFill,fillSize,ORDER_INIT_VALUE);

     }

} /* my_gl */
