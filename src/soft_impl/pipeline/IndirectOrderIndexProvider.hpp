/*
 * =====================================================================================
 *
 *       Filename:  IndirectOrderIndexProvider.hpp
 *
 *    Description:  read index value from a predefined index
 *
 *        Version:  1.0
 *        Created:  2011-10-10 16:47:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef INDIRECT_ORDER_INDEX_PROVIDER_HPP

#define INDIRECT_ORDER_INDEX_PROVIDER_HPP

#include "IndexProvider.hpp"
namespace my_gl {

     class IndirectOrderIndexProvider :public IndexProvider{
     public:


	  IndirectOrderIndexProvider(DataType dataType,const void *indices);

     	virtual ~IndirectOrderIndexProvider ();
     
	  
	virtual size_t getIndex(size_t index)const;
     private:

	const DataType _dataType;

	const void * _indices;

	template<DataType dataType>
	     size_t castRead(size_t index)const;
     };
	
} /* my_gl */


#endif /* end of include guard: INDIRECT_ORDER_INDEX_PROVIDER_HPP */
