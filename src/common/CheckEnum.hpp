/*
 * =====================================================================================
 *
 *       Filename:  CheckEnum.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/2/18 19:35:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CHECK_ENUM_HPP

#define CHECK_ENUM_HPP

#include "Enum.hpp"

namespace my_gl {

     bool checkDataType(GLenum value);
     bool checkPrimitiveMode(GLenum value);
     bool checkImageFormat(GLenum value);
     bool checkLightN(GLenum value);
	
} /* my_gl */


#endif /* end of include guard: CHECK_ENUM_HPP */
