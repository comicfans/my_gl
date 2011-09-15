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
#include <iterator>

#include "ObjectNameManager.hpp"
#include "SoftContext.hpp"

namespace my_gl {

     using std::move;
     using std::inserter;

     ArrayBufferObjectManager::ArrayBufferObjectManager() noexcept
	  :_currentName(RESERVED),_currentTarget(BufferTarget::NONE)
     {
	  _arrayAndElements[0]=nullptr;
	  _arrayAndElements[1]=nullptr;

	  _objects.insert(make_pair(RESERVED,UniquePointer()));
	  _objectNames.insert(RESERVED);
     }

     ArrayBufferObject* ArrayBufferObjectManager::
	  getArrayBuffer()const noexcept
     {return _arrayAndElements[int(BufferTarget::ARRAY_BUFFER)];}

     void ArrayBufferObjectManager::bindBuffer
	  (BufferTarget target,Name name) noexcept
     {
	  //must be a BufferObject
	  assert(isBuffer(name));

	  if (_objects.find(name)==_objects.end())
	  {
	       //generated, but with no data
	       //wait for bufferData call to construct new 
	       //ArrayBufferObject
	       _currentName=name;
	       return;
	  }
	  
	  //already has data, to bind
	  _arrayAndElements[int(target)]=_objects[name].get();
     }

	  void ArrayBufferObjectManager::bufferData
	       (BufferTarget target,size_t size,
		const void* data, DataUsage usage)
	       {
		    assert(_currentName!=RESERVED && 
			      isBuffer(_currentName) &&
			      _currentTarget!= BufferTarget::NONE);

		    if (_arrayAndElements[int(_currentTarget)]==nullptr)
		    {
			 bindNewObject(target,size,data,usage);
		    }
		    else
		    {
			 bindNewObject(target,size,data,usage);
		    }
	       }
	  void ArrayBufferObjectManager::bindNewObject
	       (BufferTarget target,size_t size,
		const void* data, DataUsage usage)
	  {
	       auto posAndResult=_objects.insert(make_pair
			 (_currentName,UniquePointer(
				   new ArrayBufferObject(
					_currentName,target,
					size,data))));

	       //should be first insert;
	       assert(posAndResult.second);

	       _arrayAndElements[int(target)]=
		    posAndResult.first->second.get();
	  }

     ArrayBufferObject * ArrayBufferObjectManager::
	  getElementsBuffer() const noexcept
	  {
	       return _arrayAndElements
		    [int(BufferTarget::ELEMENT_ARRAY_BUFFER)];
	  }

     void ArrayBufferObjectManager::genBuffers(size_t size,Name *names)
     {
	  SoftContext::getInstance().getObjectNameManager()
	       .generateNames(size,names);

	  _objectNames.insert(names,names+size);
     }

     bool ArrayBufferObjectManager::isBuffer(Name name) const noexcept
     {
	  return _objectNames.find(name)!=_objectNames.end();
     }
	
} /* my_gl */
