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

#include <cstddef>

#include "Typedef.hpp"

namespace my_gl {

     class Context {
     public:

	//glIsBuffer
	virtual bool isBuffer(Name name) const noexcept=0;
	//glGenBuffers
     	virtual void genBuffers(size_t size,Name *names)=0;
	//glDeleteBuffers
	virtual void deleteBuffers(size_t size,Name *names)=0;
	//glNormal3f/x
	virtual void normal3f(float nx,float ny,float nz)=0;
	
	virtual ~Context()noexcept;
     };
	
} /* my_gl */



#endif /* end of include guard: CONTEXT_HPP */
