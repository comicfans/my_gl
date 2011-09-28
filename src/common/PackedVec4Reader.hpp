/*
 * =====================================================================================
 *
 *       Filename:  PackedVec4Reader.hpp
 *
 *    Description:  read vector from a packed value
 *
 *        Version:  1.0
 *        Created:  2011-9-17 12:07:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef PACKED_VEC4_READER_HPP

#define PACKED_VEC4_READER_HPP

#include "AbstractVec4Reader.hpp"
#include "Enum.hpp"

namespace my_gl {

     class PackedVec4Reader :public AbstractVec4Reader{
	  public:
	       PackedVec4Reader (const UntypedCowArray& array,size_t offset,
			 StoreType storeType,size_t stride);
	  private:
	       /* data */
     };
} /* my_gl */



#endif /* end of include guard: PACKED_VEC4_READER_HPP */
