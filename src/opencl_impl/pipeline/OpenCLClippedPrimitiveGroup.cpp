/*
 * =====================================================================================
 *
 *       Filename:  OpenCLClippedPrimitiveGroup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-6 19:28:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "OpenCLClippedPrimitiveGroup.hpp"

namespace my_gl {

     OpenCLClippedPrimitiveGroup::OpenCLClippedPrimitiveGroup
	     (const VertexAttributeBuffer& originalVertexAttribute,
	      GLenum primitiveMode)
	     :ClippedPrimitiveGroup(originalVertexAttribute,primitiveMode){}


     OpenCLClippedPrimitiveGroup::~OpenCLClippedPrimitiveGroup(){}

     int OpenCLClippedPrimitiveGroup::bindToKernel(cl::Kernel kernel,int idx) 
     {
	  // these data will almost change per-call
	  // so no need to do lazy change

	  /*  OpenCL side argument:
	   *  global uint* primitiveIndex,
	   *  const uint attributeNumber,
	   *  const uint originalSize,
	   *  global float4* originalVertexAttributes,
	   *  global float4* clipGeneratedAttributes,
	   */

	  cl::Context CLContext;
	  kernel.getInfo(CL_KERNEL_CONTEXT,&CLContext);

	  size_t primitiveIndexSize=getPrimitiveIndex().size()*sizeof(uint32_t);

	  _primitiveIndexBuffer=cl::Buffer(CLContext,
		    CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
		    primitiveIndexSize,
		    const_cast<uint32_t*>(&*(getPrimitiveIndex().begin())));

	  kernel.setArg(idx++,_primitiveIndexBuffer);

	  kernel.setArg(idx++,cl_uint(attributeNumber()));

	  size_t originalVertexNumber=
	       getRefVertexAttributeBuffer().elementNumber();

	  kernel.setArg(idx++,cl_uint(originalVertexNumber));


	  //workaround originalVertexAttributes null condition
	  if (originalVertexNumber)
	  {
	       size_t originalVertexAttributesSize=originalVertexNumber*
		    attributeNumber()*sizeof(Vec4);

	       void* ptr=const_cast<Vec4*>(&(*this)[0][0]);

	       assert((size_t(ptr)%sizeof(Vec4)==0)|| "memory not alignmened");

	       _originalVertexAttributesBuffer=cl::Buffer(CLContext,
			 CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
			 originalVertexAttributesSize,ptr);
	  }
	  else
	  {
	       size_t dummyNullArraySize=sizeof(decltype(_dummyNullArray));
	       void * ptr=&_dummyNullArray;
	       _originalVertexAttributesBuffer=cl::Buffer(CLContext,
			 CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
			 dummyNullArraySize,ptr);
	  }
	       
	  kernel.setArg(idx++,_originalVertexAttributesBuffer);

	  //workaround clipGeneratedAttributes null condition
	  size_t clipGeneratedVertexNumber=
	       getClipGeneratedElementNumber();

	  if (clipGeneratedVertexNumber)
	  {
	       size_t clipGeneratedVertexAttributeSize=clipGeneratedVertexNumber
		    *attributeNumber()*sizeof(Vec4);

	       void *ptr=const_cast<Vec4*>(&(*this)[originalVertexNumber][0]);

	       assert((size_t(ptr)%sizeof(Vec4)==0)|| "memory not alignmened");

	       _clipGeneratedAttributesBuffer=cl::Buffer(CLContext,
			 CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
			 clipGeneratedVertexAttributeSize,ptr);
	  }
	  else
	  {
	       size_t dummyNullArraySize=sizeof(decltype(_dummyNullArray));
	       void * ptr=&_dummyNullArray;
	       _clipGeneratedAttributesBuffer=cl::Buffer(CLContext,
			 CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
			 dummyNullArraySize,ptr);
	  }
	       
	  kernel.setArg(idx++,_clipGeneratedAttributesBuffer);

	  return idx;

     }

} /* my_gl */

