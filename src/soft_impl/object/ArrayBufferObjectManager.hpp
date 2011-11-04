/*
 * =====================================================================================
 *
 *       Filename:  ArrayBufferObjectManager.hpp
 *
 *    Description:  object to manager multi ArrayBufferObject
 *
 *        Version:  1.0
 *        Created:  2011-9-14 17:39:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ARRAY_BUFFER_OBJECT_MANAGER_HPP

#define ARRAY_BUFFER_OBJECT_MANAGER_HPP


#include <unordered_map>
#include <memory>
#include <cstddef>

#include "Enum.hpp"
#include "Typedef.hpp"

namespace my_gl {

     using std::unordered_map;
     using std::unique_ptr;

     class ArrayBufferObject;
     class ObjectNameManager;
     class ArrayBufferObjectManager {
     public:

	  ArrayBufferObjectManager(ObjectNameManager& 
		    objectNameManager);

	  void genBuffers(size_t size,Name *names) ;

	  void deleteBuffers(size_t size, Name *names) ;

	  void bindBuffer(BufferTarget target,Name name);

	  void bufferData(BufferTarget target,size_t size,
		    const void* data, DataUsage usage);

	  void bufferSubData(BufferTarget target,ptrdiff_t offset,
		    size_t size,const void* data);

	  ArrayBufferObject* getArrayBuffer()const ;

	  ArrayBufferObject* getElementsBuffer() const ;

	  bool isBuffer(Name name)const ;
     
     private:

	  ArrayBufferObject *_arrayAndElements[2];

	  typedef unique_ptr<ArrayBufferObject> UniquePointer;

	  unordered_map<Name,UniquePointer> _objects;

	  ObjectNameManager & _objectNameManager;

     };
	
} /* my_gl */


#endif /* end of include guard: ARRAY_BUFFER_OBJECT_MANAGER_HPP */
