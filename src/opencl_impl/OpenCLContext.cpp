/*
 * =====================================================================================
 *
 *       Filename:  OpenCLContext.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-5 16:12:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *        Company:
 *
 * =====================================================================================
 */

#include "OpenCLContext.hpp"

#include <CL/cl.hpp>

#include "OpenCLPixelDrawer.hpp"

using std::vector;

namespace my_gl {


     OpenCLContext::OpenCLContext (size_t width,size_t height)
	  :SoftContext(width,height)
     {
         initOpenCL();
         SoftContext::_pixelDrawerPtr.reset(
                     new OpenCLPixelDrawer(*_CLContext.get()));

	 _pixelDrawerPtr->onInit(width,height);

         Context::setInstance(this);
     }

     OpenCLContext::~OpenCLContext()
     {}


     void OpenCLContext::initOpenCL()
     {

	  _CLContext.reset(new cl::Context(CL_DEVICE_TYPE_DEFAULT));
     }



} /* my_gl */
