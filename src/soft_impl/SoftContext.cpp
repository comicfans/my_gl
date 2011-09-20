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

#include "attribute_manager/NormalManager.hpp"
namespace my_gl {

     void SoftContext::genBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.genBuffers(size,names);
     }

     void SoftContext::deleteBuffers(size_t size,  Name *names)
     {
	  _arrayBufferObjectManager.deleteBuffers(size,names);
     }

     bool SoftContext::isBuffer(Name name) const noexcept
     {
	  return _arrayBufferObjectManager.isBuffer(name);
     }

     void SoftContext::normal(float nx,float ny,float nz)
     {
	  getVectorManager<NormalManager>(BindState::NORMAL).normal(nx,ny,nz);
     }


     template<typename T>
	  T& SoftContext::getVectorManager(BindState bindState)
	  { return static_cast<T&>(_allVectorManager[int(bindState)]);}
	
} /* my_gl */
