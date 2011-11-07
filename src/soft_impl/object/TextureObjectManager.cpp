/*
 * =====================================================================================
 *
 *       Filename:  TextureObjectManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-7 21:14:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TextureObjectManager.hpp"
#include "ObjectNameManager.hpp"
#include "common/UntypedArray.hpp"
#include "TextureObject.hpp"


namespace my_gl {

     TextureObjectManager::TextureObjectManager
	  (ObjectNameManager& objectNameManager)
	  :_objectNameManager(objectNameManager)
	  {
	       //texture is a set of data and parameter
	       //for convenience, makes a special  texture
	       //object whose name is ZERO 

	       _textureObjects[RESERVED].reset(
			 new TextureObject(RESERVED));
	  }

     bool TextureObjectManager::isTexture(Name name)const
     {
	  if (name)
	  {
	       return _textureObjects.find(name)!=
		    _textureObjects.end();
	  }
	  return false;
     }
	void TextureObjectManager::genTextures
	     (size_t n,Name * names)
	     {
		  _objectNameManager.generateNames(n,names);

		  for (int i=0; i<n; ++i)
		  {
		       Name name=names[i];
		       _textureObjects[name].reset(
				 new TextureObject(name));
		  }
	     }

	void TextureObjectManager::bindTexture
	     (TexTarget/* ignored*/,Name name)
	{
	     auto pos=_textureObjects.find(name);
	     assert(pos!=_textureObjects.end());

	     _activeTextureObject=pos->second.get();
	}

	void TextureObjectManager::deleteTextures
	     (size_t n,Name *names)
	{
	     for (int i=0; i<n; ++i)
	     {
		  Name name=names[i];
		  assert(isTexture(name));
		  _textureObjects.erase(name);
	     }
	     _objectNameManager.recycleNames(n,names);
	}

	void TextureObjectManager::texImage2D
	     (TexTarget/*ignored*/,int level/* ignored*/
		  ,int internalFormat/*ignored*/,size_t width,
		  //OpenGL ES 1.0 border must be 0
		  size_t height,int border/* ignored */,
		  ImageFormat imageFormat,StoreType storeType,
		  const void *texels)
	     {
		  assert(_activeTextureObject);

		  _activeTextureObject->
		       bindImage(width,height,imageFormat,
				 storeType,texels);
	     }

	void TextureObjectManager::texSubImage2D
	     (TexTarget/*ignored*/,
		  int level/* ignored*/,
		  int xoffset,int yoffset,
		  size_t width,size_t height,
		  ImageFormat imageFormat,
		  StoreType storeType,
		  const void *texels)
	     {
		  assert(_activeTextureObject);

		  _activeTextureObject->
		       subImage(xoffset,yoffset,
				 width,height,
				 imageFormat,storeType,
				 texels);

	     }

	void TextureObjectManager::
	     texParameter(TexTarget target/*ignored*/,
		  TexWrapName wrapName,
		  TexWrapMode texWrapMode)
	{
	     getActiveTextureObject()->
		  texParameter(wrapName,texWrapMode);
	}

	void TextureObjectManager::
	     texParameter(TexTarget target/*ignored*/,
		  TexFilterName filterName,
		  TexFilterMode texFilterMode)
	{
	     getActiveTextureObject()->
		  texParameter(filterName,texFilterMode);
	}
     

     TextureObject* TextureObjectManager::
	  getActiveTextureObject()
	  {
	       assert(_activeTextureObject);
	       return _activeTextureObject;
	  }
	
} /* my_gl */
