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

	       _activeTextureObject=_textureObjects[RESERVED].get();
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
		       
		  //should not in
		  assert(_textureObjects.find(name)==
			    _textureObjects.end());

		  //makes a stub
		  _textureObjects[name];

		  }
		  
	     }

	void TextureObjectManager::bindTexture
	     (TexTarget/* ignored*/,Name name)
	{
	     auto pos=_textureObjects.find(name);
	     assert(pos!=_textureObjects.end());

	     if (!(pos->second))
	     {
		  pos->second.reset(new TextureObject(name));
	     }

	     _activeTextureObject=pos->second.get();
	}

	void TextureObjectManager::deleteTextures
	     (size_t n,const Name *names)
	{
	     for (int i=0; i<n; ++i)
	     {
		  Name name=names[i];

		  if (name==0)
		  {
		       continue;
		  }

		  auto pos=_textureObjects.find(name);
		  if(pos!=_textureObjects.end())
		  {
		       if (pos->second)
		       {
			    if (_activeTextureObject==pos->second.get())
			    {
				 bindTexture(TexTarget::TEXTURE_2D,0);
			    }
			    _textureObjects.erase(pos);
			    _objectNameManager.recycleName(name);
		       }
		  }
	     }
	}

	void TextureObjectManager::texImage2D
	     (TexTarget/*ignored*/,int level/* ignored*/
		  ,int internalFormat/*ignored*/,size_t width,
		  //OpenGL ES 1.0 border must be 0
		  size_t height,int border/* ignored */,
		  GLenum imageFormat,GLenum storeType,
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
		  GLenum imageFormat,
		  GLenum storeType,
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
	       if (_texture2DEnabled)
	       {
		    assert(_activeTextureObject);
	       }

	       return _activeTextureObject;
	  }
	
} /* my_gl */
