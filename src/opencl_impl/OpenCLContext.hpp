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

#include <memory>

#include "soft_impl/SoftContext.hpp"
namespace cl
{
        class Context;
}

namespace my_gl {

     class OpenCLContext :public SoftContext{
     public:
     	OpenCLContext (size_t width=600,size_t height=400);

     	virtual ~OpenCLContext ();

     protected:
	virtual void clipPrimitive
	     (const PrimitiveIndex& primitiveIndex,
		  GLenum catalog) ;

	virtual void fragmentShaderStage();

     private:

	std::unique_ptr<cl::Context> _CLContext;

         void initOpenCL();
     	/* data */
     };

} /* my_gl */


#endif /* end of include guard: OPENCL_CONTEXT_HPP */
