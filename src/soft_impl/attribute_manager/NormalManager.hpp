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

#include "common/VectorProvider.hpp"
#include "common/VectorManager.hpp"

#include "Enum.hpp"

namespace my_gl{

     using std::unique_ptr;
     class NormalManager :public VectorManager{
     public:

	  NormalManager();

	  //glNormal3f
	  void normal(float nx,float ny,float nz);

	  //glNormalPointer
	  void normalPointer(DataType type,size_t stride,
		    const void* pointer);

	  virtual VectorProvider& getProvider()noexcept;
     
     private:

	  unique_ptr<VectorProvider> _pImpl;

	  bool _normalArrayEnabled;
     };
	
} /* my_gl */


#endif /* end of include guard: NORMAL_MANAGER_HPP */
