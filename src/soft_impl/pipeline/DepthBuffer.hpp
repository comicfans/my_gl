/*
 * =====================================================================================
 *
 *       Filename:  DepthBuffer.hpp
 *
 *    Description:  OpenGL depth buffer , which can be used
 *    in z-buffer hidden surface remove. store final 
 *    z value in double format (scaled by DepthRange parameter)
 *    also known as z-buffer
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

	  /** 
	   * @brief depth value used to clear whole buffer
	   * 
	   * @param depth
	   */
	  void clearDepth(double depth);

	  /** 
	   * @brief depth function decide 
	   * which type value can pass depth buffer test
	   * 
	   * @param func
	   */
	  void depthFunc(DepthFunc func);
	  virtual void clear();

	  size_t width()const;
	  size_t height()const;

	  /** 
	   * @brief check winCoord.z() can be passed
	   * depth test . if passed ,new value is stored
	   * in depth buffer. (OpenGL can only test depth
	   * value ,but disable update, but not implemented )
	   *
	   * in multi thread updating ,pixel operated on should be 
	   * a atomic action
	   * 
	   * @param winCoord
	   * 
	   * @return 
	   */
	  bool testAndUpdate(const WinCoord& winCoord);

     	virtual ~DepthBuffer ();

	static const int ORDER_INDEX=1;
     
     private:

	multi_array<double,2> _impl;

	double _clearDepth;

	DepthFunc _func;

	bool outOfRange(const WinCoord& winCoord)const;

     };
	
} /* my_gl */


#endif /* end of include guard: DEPTH_BUFFER_HPP */
