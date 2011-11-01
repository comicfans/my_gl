/*
 * =====================================================================================
 *
 *       Filename:  DepthBuffer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 10:19:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef DEPTH_BUFFER_HPP

#define DEPTH_BUFFER_HPP


#include <boost/multi_array.hpp>

#include "FrameBuffer.hpp"
#include "Enum.hpp"
namespace my_gl {

     using boost::multi_array;

     class WinCoord;

     class DepthBuffer :public FrameBuffer{
     public:

	  DepthBuffer(size_t width,size_t height);

	  void clearDepth(float depth);

	  void depthFunc(DepthFunc func);
	  virtual void clear();

	  size_t width()const;
	  size_t height()const;

	  bool testAndUpdate(const WinCoord& winCoord,float value);

     	virtual ~DepthBuffer ();
     
     private:

	multi_array<float,2> _impl;

	float _clearDepth;

	DepthFunc _func;

     };
	
} /* my_gl */


#endif /* end of include guard: DEPTH_BUFFER_HPP */
