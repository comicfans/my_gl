/*
 * =====================================================================================
 *
 *       Filename:  ArrayBufferObjectManager.cpp
 *
 *    Description:  implementation of ArrayBufferObjectManager
 *
 *        Version:  1.0
 *        Created:  2011-9-15 20:10:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "ArrayBufferObjectManager.hpp"

#include <utility>
#include <algorithm>
#include <iterator>

#include "common/UntypedArray.hpp"
#include "ObjectNameManager.hpp"
#include "SoftContext.hpp"
#include "ArrayBufferObject.hpp"

namespace my_gl {

     using std::move;
     using std::inserter;
     using std::fill_n;

     ArrayBufferObjectManager::ArrayBufferObjectManager() noexcept
     {
	  fill_n(_arrayAndElements,2,nullptr);
     }

     ArrayBufferObject* ArrayBufferObjectManager::
	  getArrayBuffer()const noexcept
     {
	  auto p=_arrayAndElements[int(BufferTarget::ARRAY_BUFFER)];
	  //0 is bind
	  assert(p);
	  return p;
     }

     void ArrayBufferObjectManager::bindBuffer
	  (BufferTarget target,Name name) noexcept
     {
	  //must be a ArrayBufferObject
	  assert(isBuffer(name));

	  //already has data, to bind
	  _arrayAndElements[int(target)]=_objects[name].get();
     }

     void ArrayBufferObjectManager::deleteBuffers(size_t size,Name *names)
	  noexcept
     {
	  for (int i= 0; i < size; i++) {
	       Name thisName=*(names+i);
	       assert(isBuffer(thisName));

	       _objects.erase(thisName);
	  }

	  SoftContext::getInstance().
	       getObjectNameManager().recycleNames(size,names);

     }

     void ArrayBufferObjectManager::bufferData
	  (BufferTarget target,size_t size,
	   const void* data, DataUsage usage)
	  {

	       ArrayBufferObject *pBuffer=_arrayAndElements[int(target)];
	       assert(pBuffer);
	       pBuffer->bindData(size,data);

	  }

     ArrayBufferObject * ArrayBufferObjectManager::
	  getElementsBuffer() const noexcept
	  {
	       auto p=_arrayAndElements
		    [int(BufferTarget::ELEMENT_ARRAY_BUFFER)];
	       assert(p);

	       return p;
	  }

     void ArrayBufferObjectManager::genBuffers(size_t size,Name *names)
     {
	  SoftContext::getInstance().getObjectNameManager()
	       .generateNames(size,names);

	  for (int i = 0; i < size; i++) {
	       Name thisName=*(names+i);
	  	_objects.insert(make_pair(thisName,UniquePointer(
				    new ArrayBufferObject(thisName))));
	  }
     }

     bool ArrayBufferObjectManager::isBuffer(Name name) const noexcept
     {
	  return _objects.find(name)!=_objects.end();
     }

} /* my_gl */
