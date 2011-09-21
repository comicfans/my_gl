/*
 * =====================================================================================
 *
 *       Filename:  UniqueVectorProvider.hpp
 *
 *    Description:  unique value vector provider
 *
 *        Version:  1.0
 *        Created:  2011-9-19 12:58:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef UNIQUE_VECTOR_PROVIDER_HPP

#define UNIQUE_VECTOR_PROVIDER_HPP

#include "VectorProvider.hpp"

namespace my_gl {

     class UniqueVectorProvider :public VectorProvider{
     public:
     	UniqueVectorProvider (const Vector& value=Vector())noexcept;

	virtual Vector value()noexcept;

	virtual void next(size_t steps=1)noexcept;

	void setValue(const Vector& value)noexcept;
     
     private:
	Vector _value;
     };
	
} /* my_gl */


#endif /* end of include guard: UNIQUE_VECTOR_PROVIDER_HPP */
