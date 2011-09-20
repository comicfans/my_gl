/*
 * =====================================================================================
 *
 *       Filename:  NormalManager.hpp
 *
 *    Description:  class to manager normal provider
 *
 *        Version:  1.0
 *        Created:  2011-9-19 15:51:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef NORMAL_MANAGER_HPP

#define NORMAL_MANAGER_HPP

#include <memory>

#include "TwoSourceVectorManager.hpp"

namespace my_gl{

     class NormalManager :public TwoSourceVectorManager{
     public:

	  NormalManager();

	  //glNormal3f
	  void normal(float nx,float ny,float nz);

	  //glNormalPointer
	  void normalPointer(DataType type,size_t stride,
		    const void* pointer);

     };
	
} /* my_gl */


#endif /* end of include guard: NORMAL_MANAGER_HPP */
