/*
 * =====================================================================================
 *
 *       Filename:  NaturalOrderIndexProvider.hpp
 *
 *    Description:  index value is just the index 
 *
 *        Version:  1.0
 *        Created:  2011-10-10 16:44:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef NATURAL_ORDER_INDEX_PROVIDER_H

#define NATURAL_ORDER_INDEX_PROVIDER_H

#include "IndexProvider.hpp"

namespace my_gl {
     class NaturalOrderIndexProvider :public IndexProvider{
     public:

	  NaturalOrderIndexProvider(size_t jump=0);

     	virtual ~NaturalOrderIndexProvider ();
	virtual size_t getIndex(size_t index)const;
     private:
	const size_t _jump;
     };
	
} /* my_gl */

#endif /* end of include guard: NATURAL_ORDER_INDEX_PROVIDER_H */
