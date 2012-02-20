/*
 * =====================================================================================
 *
 *       Filename:  ArrayVec4Provider.hpp
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

#ifndef ARRAY_VEC4_PROVIDER_HPP

#define ARRAY_VEC4_PROVIDER_HPP

#include <algorithm>
#include <cstddef>

#include "Vec4Provider.hpp"
#include "TypeTraits.hpp"

namespace my_gl {
	
     using std::copy_n;
     class ArrayVec4Provider :public Vec4Provider{
     public:
	  ArrayVec4Provider(int componentNumber,GLenum type,
		    size_t stride,bool normalize);

     protected:

	  Vec4 castRead(const void* pointer,size_t index)
	       const ;

	  const GLenum _dataType;
	  const int _componentNumber;
	  const size_t _blockSize;
	  const bool _normalize;
     private:
	  template<GLenum dataType>
	       Vec4 copyToFloats(const void* p)
	       const ;
     };
} /* my_gl */

#endif /* end of include guard: ARRAY_VEC4_PROVIDER_HPP */
