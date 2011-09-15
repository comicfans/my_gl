/*
 * =====================================================================================
 *
 *       Filename:  SoftContext.hpp
 *
 *    Description:  C++/thread impl of whole opengl pipeline
 *
 *        Version:  1.0
 *        Created:  2011-9-13 15:26:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SOFT_CONTEXT_HPP

#define SOFT_CONTEXT_HPP

#include "Context.hpp"
#include "object/ObjectNameManager.hpp"

namespace my_gl {

     class BufferObject;

     class SoftContext :public Context{
     public:
     	SoftContext ();

	BufferObject const* getActiveBufferObject()const;

     	virtual ~SoftContext ();


	//glGenBuffers
	void genBuffers(size_t size,Name *names);
	//glDeleteBuffers
	void deleteBuffers(size_t size,Name *names);
     
     private:

	ObjectNameManager _objectNameManager;
     	/* data */
     };
	
} /* my_gl */


#endif /* end of include guard: SOFT_CONTEXT_HPP */
