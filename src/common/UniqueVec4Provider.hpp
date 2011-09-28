/*
 * =====================================================================================
 *
 *       Filename:  UniqueVec4Provider.hpp
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

#ifndef UNIQUE_VEC4_PROVIDER_HPP

#define UNIQUE_VEC4_PROVIDER_HPP

#include "Vec4Provider.hpp"

namespace my_gl {

     class UniqueVec4Provider :public Vec4Provider{
     public:
     	UniqueVec4Provider (const Vec4& value=Vec4());

	virtual Vec4 value();

	virtual void next(size_t steps=1);

	void setValue(const Vec4& value);
     
     private:
	Vec4 _value;
     };
	
} /* my_gl */


#endif /* end of include guard: UNIQUE_VEC4_PROVIDER_HPP */
