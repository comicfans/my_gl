/*
 * =====================================================================================
 *
 *       Filename:  CLParameterBinder.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-5 10:36:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CL_PARAMETER_BINDER_HPP

#define CL_PARAMETER_BINDER_HPP

#include <CL/cl.hpp>

namespace my_gl
{
     /** 
      * @brief interface to bind parameter 
      * memory or value to OpenCL kernel.
      * this interface is designed to standard bind to kernel 
      * function , in real use,bind to kernel can be complex
      * (one time bind,bind per call,or bind on change),so 
      * only to be used internal (int class self),not for public
      * call,no virtual destructor,
      * not use this interface to store pointer
      */
     class CLParameterBinder {
     protected:
	  /** 
	   * @brief 
	   * 
	   * @param kernel kernel to bind to
	   */
	  virtual void bindToKernel(cl::Kernel kernel)=0;
     };
	
} /* my_gl */



#endif /* end of include guard: CL_PARAMETER_BINDER_HPP */
