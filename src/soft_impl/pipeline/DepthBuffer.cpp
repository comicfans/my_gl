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
#include <unordered_map>
#include <functional>

#include <boost/assign/list_of.hpp>

#include "common/CheckEnum.hpp"
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
     static const std::unordered_map<GLenum,ActualDepthFunc> DEPTH_FUNCTIONS=
	  boost::assign::map_list_of<GLenum,ActualDepthFunc>(GL_NEVER,never)(GL_ALWAYS,always)
	  (GL_LESS,less<double>())(GL_LEQUAL,less_equal<double>())
	  (GL_EQUAL,equal_to<double>())(GL_GREATER,greater<double>())
	  (GL_GEQUAL,greater_equal<double>())(GL_NOTEQUAL,not_equal_to<double>());


     DepthBuffer::DepthBuffer(size_t width,size_t height)
	  :_impl(extents[height][width])
     {
	  //glspec default GL_DEPTH_CLEAR_VALUE
	  _clearDepth=1;
	  _func=GL_ALWAYS;
     }

     DepthBuffer::~DepthBuffer()
     {}

     void DepthBuffer::clearDepth(double depth)
     {
	  _clearDepth=depth;
     }

     void DepthBuffer::depthFunc(GLenum func)
     {
	  checkDepthFunc(func);
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
	
     bool DepthBuffer::outOfRange(const my_gl::WinCoord &winCoord)const
     {
	  return (winCoord.x()<0) ||
	       (winCoord.x()>=width()) ||
	       (winCoord.y()<0) ||
	       (winCoord.y()>=height());
     }
	  
     bool DepthBuffer::testAndUpdate(const WinCoord& winCoord)
     {
	  //if pixel out of range ,always makes it not passed
	  if (outOfRange(winCoord))
	  {
	       return false;
	  }

	  double& originValue=_impl[winCoord.y()][winCoord.x()];

	  auto it=DEPTH_FUNCTIONS.find(_func);

	  auto& testFunc=it->second;

	  if (testFunc(winCoord.z(),originValue))
	  {
	       originValue=winCoord.z();
	       return true;
	  }
	  return false;
     }
} /* my_gl */
