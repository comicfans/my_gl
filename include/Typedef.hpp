/*
 * =====================================================================================
 *
 *       Filename:  Typedef.hpp
 *
 *    Description:  typedef header
 *
 *        Version:  1.0
 *        Created:  2011-9-14 17:45:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TYPEDEF_HPP

#define TYPEDEF_HPP

namespace my_gl {
	
     typedef unsigned Name;

     typedef unsigned FrameBufferMask;

     const FrameBufferMask COLOR_BUFFER_BIT=1;

     const FrameBufferMask DEPTH_BUFFER_BIT=2;

    const Name RESERVED=0;

    const float HALF_PIXEL=0.5;
} /* my_gl */


#endif /* end of include guard: TYPEDEF_HPP */
