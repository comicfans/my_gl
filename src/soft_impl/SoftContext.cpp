/*
 * =====================================================================================
 *
 *       Filename:  SoftContext.cpp
 *
 *    Description:  implementation of SoftContext
 *
 *        Version:  1.0
 *        Created:  2011-9-15 12:56:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SoftContext.hpp"
namespace my_gl {

     void SoftContext::genBuffers(size_t size,  Name *names)
     {
	  _objectNameManager.generateNames(size, names);
     }

     void SoftContext::deleteBuffers(size_t size,  Name *names)
     {
	  //TODO release buffer object
     }
	
} /* my_gl */
