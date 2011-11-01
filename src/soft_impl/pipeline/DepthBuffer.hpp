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

#include "FrameBuffer.hpp"

#include <boost/multi_array.hpp>
namespace my_gl {

     using boost::multi_array;

     class WinCoord;

     class DepthBuffer :public FrameBuffer{
     public:

	  DepthBuffer(size_t width,size_t height);

	  void clearDepth(float depth);
	  virtual void clear();

	  size_t width()const;
	  size_t height()const;

	  float operator()(const WinCoord& winCoord)const;
	  float& operator()(const WinCoord& winCoord);

     	virtual ~DepthBuffer ();
     
     private:

	multi_array<float,2> _impl;

	float _clearDepth;

     };
	
} /* my_gl */


#endif /* end of include guard: DEPTH_BUFFER_HPP */
