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
#include "ArrayBufferObject.hpp"

namespace my_gl {

     using std::move;
     using std::inserter;
     using std::fill_n;

     ArrayBufferObjectManager::ArrayBufferObjectManager
	  (ObjectNameManager& objectNameManager):
	       _objectNameManager(objectNameManager)
     {
	  fill_n(_arrayAndElements,2,nullptr);
     }

     ArrayBufferObject* ArrayBufferObjectManager::
	  getArrayBuffer()const 
     {
	  auto p=_arrayAndElements[int(GL_ARRAY_BUFFER)];
	  //if 0 is bind
	  // 
	  // null is returned
	  return p;
     }

     void ArrayBufferObjectManager::bindBuffer
	  (GLenum target,Name name) 
     {

	  //if zero is binded, no buffer is used

	  if (name==RESERVED)
	  {
	       _arrayAndElements[int(target)]=nullptr;
	       return;
	  }
	  

	  auto pos=_objects.find(name);

	  //this name should be resturned by genBuffers(in map)
	  assert(pos!=_objects.end());

	  //no data binded,
	  if (!pos->second)
	  {
	       pos->second.reset(new ArrayBufferObject(name));
	  }

	  //already has data, to bind
	  _arrayAndElements[int(target)]=pos->second.get();
     }

     void ArrayBufferObjectManager::deleteBuffers(size_t size,const Name *names)
     {
	  for (size_t i= 0; i < size; i++) {
	       auto thisName=*(names+i);

	       //OpenGL programming guide said that
	       //if a name is not buffer ,no error is generated
	       //if a binding array buffer object is deleted
	       //corresponding buffer will be reset ,as 
	       //zero is binded to this buffer

	       auto pos=_objects.find(thisName);

	       if(pos->second)
	       {

		    if (pos->second.get()==_arrayAndElements
			      [int(GL_ARRAY_BUFFER)])
		    {
			 bindBuffer(GL_ARRAY_BUFFER,0);
		    }
		    
		    else if (pos->second.get()==_arrayAndElements
			      [int(GL_ELEMENT_ARRAY_BUFFER)]){
			 bindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		    }
		    _objects.erase(pos);
		    _objectNameManager.recycleName(thisName);
	       }

	  }
     }

     void ArrayBufferObjectManager::bufferData
	  (GLenum target,size_t size,
	   const void* data, DataUsage usage)
	  {

	       ArrayBufferObject *pBuffer=_arrayAndElements[int(target)];
	       assert(pBuffer);
	       pBuffer->bindData(size,data);

	  }

     void ArrayBufferObjectManager::bufferSubData
	  (GLenum target,ptrdiff_t offset,
		    size_t size,const void* data)
     {
	       ArrayBufferObject *pBuffer=_arrayAndElements[int(target)];
	       assert(pBuffer);
	       pBuffer->subData(offset,size,data);
     }


     ArrayBufferObject * ArrayBufferObjectManager::
	  getElementsBuffer() const 
	  {
	       auto p=_arrayAndElements
		    [int(GL_ELEMENT_ARRAY_BUFFER)];
	       assert(p);

	       return p;
	  }

     void ArrayBufferObjectManager::genBuffers(size_t size,Name *names)
     {
	  _objectNameManager.generateNames(size,names);

	  for (size_t i = 0; i < size; i++) {
	       Name thisName=*(names+i);

	       //should not in
	       assert(_objects.find(thisName)==_objects.end());

	       //only makes a stub
	       _objects[thisName];
	  }
     }

     bool ArrayBufferObjectManager::isBuffer(Name name) const 
     {
	  auto pos=_objects.find(name);

	  if (pos==_objects.end())
	  {
	       return false;
	  }

	  //if a name is generated by 
	  return bool(pos->second);
     }

} /* my_gl */
