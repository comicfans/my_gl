/*
 * =====================================================================================
 *
 *       Filename:  Context.hpp
 *
 *    Description:  whole state of a draw context
 *
 *        Version:  1.0
 *        Created:  2011-9-13 15:16:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef CONTEXT_HPP

#define CONTEXT_HPP

#include "Typedef.hpp"

namespace my_gl {

     class Context {
     public:
     	Context ();
     	virtual ~Context ();

	//glIsBuffer
	virtual bool isBuffer(Name name) const noexcept;
	//glGenBuffers
     	virtual void genBuffers(size_t size,Name *names);
	//glDeleteBuffers
	virtual void deleteBuffers(size_t size,Name *names);
	//glNormal3f/x
	virtual void normal(float nx,float ny,float nz);
	
     private:
     	/* data */
     };
	
} /* my_gl */



#endif /* end of include guard: CONTEXT_HPP */
