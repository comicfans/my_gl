/*
 * =====================================================================================
 *
 *       Filename:  ArrayIndexProvider.hpp
 *
 *    Description:  provide index from client array
 *    		    or array buffer object
 *    		    treate array as a index array
 *    		    get a integer index from this array with
 *    		    a index(index of index)
 *    		    used in glDrawElements 
 *
 *    		    glDrawElements is a final drawing command 
 *    		    so array buffer object binded to 
 *    		    GL_ELEMENTS_ARRAY_BUFFER will not changed 
 *    		    before entering pipeline,client array or 
 *    		    array buffer object based glDrawElements 
 *    		    can use the same ArrayIndexProvider
 *    		    (no need to store a ArrayBufferObject reference,
 *    		    store the internal pointer is just OK)
 *
 *
 *        Version:  1.0
 *        Created:  2011-10-22 20:57:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ARRAY_INDEX_PROVIDER_HPP

#define ARRAY_INDEX_PROVIDER_HPP

#include "IndexProvider.hpp"


namespace my_gl {

     class ArrayIndexProvider :public IndexProvider{
     public:

	  ArrayIndexProvider
	       (DataType dataType,const void* indices);

	  virtual ~ArrayIndexProvider ();

	  virtual size_t getIndex(size_t index)const;
     private:

	  template<DataType dataType>
	       size_t castRead(size_t index)const;
	
	  const DataType _dataType;

	  const void *_indices;


     };
	
} /* my_gl */


#endif /* end of include guard: ARRAY_INDEX_PROVIDER_HPP */
