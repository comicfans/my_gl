/*
 * =====================================================================================
 *
 *       Filename:  OpenCLClippedPrimitiveGroup.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-6 19:23:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef OPENCL_CLIPPED_PRIMITIVE_GROUP_HPP

#define OPENCL_CLIPPED_PRIMITIVE_GROUP_HPP

#include "soft_impl/pipeline/ClippedPrimitiveGroup.hpp"

#include "opencl_impl/CLParameterBinder.hpp"
namespace my_gl {
	

class OpenCLClippedPrimitiveGroup :public ClippedPrimitiveGroup,CLParameterBinder{
public:

	OpenCLClippedPrimitiveGroup
	     (const VertexAttributeBuffer& originalVertexAttribute,
	      PrimitiveMode primitiveMode); 

	virtual ~OpenCLClippedPrimitiveGroup ();

	virtual int bindToKernel(cl::Kernel kernel,int idx) ;

private:

	cl::Buffer _primitiveIndexBuffer;
	cl::Buffer _originalVertexAttributesBuffer;
	cl::Buffer _clipGeneratedAttributesBuffer;
	cl_uint _dummyNullArray;


};

} /* my_gl */

#endif /* end of include guard: OPENCL_CLIPPED_PRIMITIVE_GROUP_HPP */
