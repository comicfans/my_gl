/*
 * =====================================================================================
 *
 *       Filename:  WindowCoordinate.hpp
 *
 *    Description:  a simple typedef
 *
 *        Version:  1.0
 *        Created:  2011-10-20 11:56:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef WINDOW_COORDINATES_HPP

#define WINDOW_COORDINATES_HPP

#include <utility>


namespace my_gl {

     

     //first is y ,second is x
     struct WindowCoordinates :public std::pair<int,int>{
	  int& operator[](int index);
	  const int& operator[](int index)const;
     } /* optional variable list */;
	
} /* my_gl */

#endif /* end of include guard: WINDOW_COORDINATES_HPP */
