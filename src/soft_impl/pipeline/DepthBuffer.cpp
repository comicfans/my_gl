/*
 * =====================================================================================
 *
 *       Filename:  DepthBuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 10:23:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "DepthBuffer.hpp"

#include <algorithm>
#include <functional>

#include "pipeline/rasterizer/WinCoord.hpp"

namespace my_gl {

     using std::fill_n;
     using std::function;
     using std::less;
     using std::less_equal;
     using std::equal_to;
     using std::greater;
     using std::greater_equal;
     using std::not_equal_to;

     using boost::extents;

     static inline bool always(float inValue,float originValue)
     {
	  return true;
     }

     static inline bool never(float inValue,float originValue)
     {
	  return false;
     }


     typedef function<bool(float,float)> ActualDepthFunc;

     //enum class DepthFunc{NEVER,ALWAYS,LESS,LEQUAL,
     //	  EQUAL,GREATER,GEQUAL,NOTEQUAL};
     static const ActualDepthFunc DEPTH_FUNCTIONS[]={never,always,less<float>(),less_equal<float>(),
     equal_to<float>(),greater<float>(),greater_equal<float>(),not_equal_to<float>()};


     DepthBuffer::DepthBuffer(size_t width,size_t height)
	  :_impl(extents[height][width])
     {
	  //glspec default GL_DEPTH_CLEAR_VALUE
	  _clearDepth=1;
	  _func=DepthFunc::ALWAYS;
     }

     DepthBuffer::~DepthBuffer()
     {}

     void DepthBuffer::clearDepth(float depth)
     {
	  _clearDepth=depth;
     }

     void DepthBuffer::depthFunc(DepthFunc func)
     {
	  _func=func;
     }

     size_t DepthBuffer::width()const
     {
	  return _impl.shape()[1];
     }
	  size_t DepthBuffer::height()const
	  {
	       return _impl.shape()[0];

	  }

     void DepthBuffer::clear()
     {
	  fill_n(_impl.origin(),_impl.num_elements(),_clearDepth);
	  
     }
	
	  
     bool DepthBuffer::testAndUpdate(const WinCoord& winCoord)
     {
	  float& originValue=_impl[winCoord.y()][winCoord.x()];

	  auto& testFunc=DEPTH_FUNCTIONS[int(_func)];

	  if (testFunc(winCoord.z(),originValue))
	  {
	       originValue=winCoord.z();
	       return true;
	  }
	  return false;
     }
} /* my_gl */
