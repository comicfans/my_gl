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

#include "soft_impl/shader/FragmentAttributeBuffer.hpp"

namespace my_gl
{
     class OpenCLFragmentAttributeBuffer :public FragmentAttributeBuffer{
     public:
	  OpenCLFragmentAttributeBuffer 
	     (size_t width,size_t height,size_t attributeNumber);

	  virtual ~OpenCLFragmentAttributeBuffer ();

	  void* getRawData();

	  /** 
	   * @brief when use opencl rasterizer(currently only point rasterizer) ,win coord is stored
	   * in float format (cut down to int), and only ClippedPrimitiveGroup has information
	   * about which fragment is generated ,so we need this interface to iterate over ClippedPrimitiveGroup
	   * to insert activeFragment
	   * 
	   */
	  void insertActiveFragment(const Vec4& winCoordVec4);
     };
	
} /* my_gl */


#endif /* end of include guard: OPENCL_FRAGMENT_ATTRIBUTE_BUFFER_HPP */
