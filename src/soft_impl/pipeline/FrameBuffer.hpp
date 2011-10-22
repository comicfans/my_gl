/*
 * =====================================================================================
 *
 *       Filename:  FrameBuffer.hpp
 *
 *    Description:  which final pixel is reached
 *
 *        Version:  1.0
 *        Created:  2011-10-22 16:08:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef FRAME_BUFFER_HPP

#define FRAME_BUFFER_HPP

#include <boost/multi_array.hpp>

#include "common/Vec4.hpp"

namespace my_gl {


     using boost::multi_array;

     class WindowCoordinates;

     class FrameBuffer :protected multi_array<Vec4,2>{
     public:

	  typedef multi_array<Vec4,2> SuperType;

	  FrameBuffer (size_t heigt,size_t width);

	  Vec4& operator()(const WindowCoordinates& winCoord);

	  const Vec4& operator()(const WindowCoordinates& winCoord)const;

     };
	
} /* my_gl */


#endif /* end of include guard: FRAME_BUFFER_HPP */
