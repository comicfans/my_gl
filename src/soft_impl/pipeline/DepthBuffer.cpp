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
#include <array>
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
     using std::array;

     using boost::extents;

     static inline bool always(double inValue,double originValue)
     {
	  return true;
     }

     static inline bool never(double inValue,double originValue)
     {
	  return false;
     }


     typedef function<bool(double,double)> ActualDepthFunc;

     //enum class DepthFunc{NEVER,ALWAYS,LESS,LEQUAL,
     //	  EQUAL,GREATER,GEQUAL,NOTEQUAL};
     static const ActualDepthFunc DEPTH_FUNCTIONS[]={never,always,
	  less<double>(),less_equal<double>(),
     equal_to<double>(),greater<double>(),
     greater_equal<double>(),not_equal_to<double>()};

     static const int SIDE_OFFSET=4;

     DepthBuffer::DepthBuffer(size_t width,size_t height)
	  :_impl(extents[height+SIDE_OFFSET*2][width+SIDE_OFFSET*2])
     {
	  //glspec default GL_DEPTH_CLEAR_VALUE
	  _clearDepth=1;
	  _func=DepthFunc::ALWAYS;

	  array<int,3> bases={-SIDE_OFFSET,-SIDE_OFFSET,0};

	  _impl.reindex(bases);
     }

     DepthBuffer::~DepthBuffer()
     {}

     void DepthBuffer::clearDepth(double depth)
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
	  double& originValue=_impl[winCoord.y()][winCoord.x()];

	  auto& testFunc=DEPTH_FUNCTIONS[int(_func)];

	  if (testFunc(winCoord.z(),originValue))
	  {
	       originValue=winCoord.z();
	       return true;
	  }
	  return false;
     }
} /* my_gl */
