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
#include <unordered_set>
#include <memory>

#include "ArrayBufferObject.hpp"

namespace my_gl {

     using std::unordered_map;
     using std::unordered_set;
     using std::unique_ptr;

     class ArrayBufferObjectManager {
     public:

	  ArrayBufferObjectManager()noexcept;

	  void genBuffers(size_t size,Name *names) ;

	  void bindBuffer(BufferTarget target,Name name)noexcept;

	  void bufferData(BufferTarget target,size_t size,
		    const void* data, DataUsage usage);

	  ArrayBufferObject* getArrayBuffer()const noexcept;

	  ArrayBufferObject* getElementsBuffer() const noexcept;

	  bool isBuffer(Name name)const noexcept;
     
     private:


	  void bindNewObject(BufferTarget target,size_t size,
		    const void* data, DataUsage usage);

	  ArrayBufferObject *_arrayAndElements[2];

	  Name _currentName;

	  BufferTarget _currentTarget;

	  typedef unique_ptr<ArrayBufferObject> UniquePointer;

	  unordered_map<Name,UniquePointer> _objects;

	  unordered_set<Name> _objectNames;

     };
	
} /* my_gl */


#endif /* end of include guard: ARRAY_BUFFER_OBJECT_MANAGER_HPP */
