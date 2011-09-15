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

	virtual bool isBuffer(Name name) const noexcept;
     
     private:
     	/* data */
     };
	
} /* my_gl */



#endif /* end of include guard: CONTEXT_HPP */
