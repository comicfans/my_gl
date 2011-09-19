/*
 * =====================================================================================
 *
 *       Filename:  ArrayVectorProvider.hpp
 *
 *    Description:  abstract class to read vector from pointer
 *
 *        Version:  1.0
 *        Created:  2011-9-19 13:10:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ARRAY_VECTOR_PROVIDER_HPP

#define ARRAY_VECTOR_PROVIDER_HPP

#include <algorithm>
#include <cstddef>

#include "VectorProvider.hpp"
#include "TypeTraits.hpp"

namespace my_gl {
	
     using std::copy_n;
     class ArrayVectorProvider :public VectorProvider{
     public:
	  ArrayVectorProvider(DataType type,int componentNumber,
		    size_t stride,bool normalize);

     protected:

	  Vector castRead(const void* pointer)
	       const noexcept;

	  const DataType _dataType;
	  const int _componentNumber;
	  const size_t _blockSize;
	  const bool _normalize;
     private:
	  template<DataType dataType>
	       Vector copyToFloats(const void* p)
	       const noexcept
	       {
		    typedef typename 
			 DataTypeTraits<dataType>::underlineType type;
		    type const *tp=static_cast<type const*>(p);
		    Vector ret;
		    copy_n(tp,_componentNumber,&ret.x);

		    if (_normalize)
		    {
			 for (int i=0; i<_componentNumber; ++i)
			 {
			      ret(i)=DataTypeTraits<dataType>::
				   normalize(ret(i));
			 }
		    }

		    return ret;
	       }

     };
} /* my_gl */

#endif /* end of include guard: ARRAY_VECTOR_PROVIDER_HPP */
