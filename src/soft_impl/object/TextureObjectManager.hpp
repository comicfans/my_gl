/*
 * =====================================================================================
 *
 *       Filename:  TextureObjectManager.hpp
 *
 *    Description:  class to manager active Texture
 *
 *    in OpenGL ES 1.0 ,only TARGET=TEXTURE_2D is supported
 *
 *        Version:  1.0
 *        Created:  2011-11-7 21:10:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEXTURE_OBJECT_MANAGER_HPP

#define TEXTURE_OBJECT_MANAGER_HPP

#include <memory>
#include <unordered_map>

#include "Enum.hpp"
#include "Typedef.hpp"


namespace my_gl {

     using std::unique_ptr;
     using std::unordered_map;

     class ObjectNameManager;
     class TextureObject;

     class TextureObjectManager {
     public:
     	TextureObjectManager 
	     (ObjectNameManager& objectNameManager);

	bool isTexture(Name name)const;

	TextureObject * getActiveTextureObject();

	void genTextures(size_t n,Name * names);

	void bindTexture(TexTarget/* ignored*/,Name texture);

	void deleteTextures(size_t n,const Name *names);

	void texImage2D(TexTarget/*ignored*/,int level/* ignored*/
		  ,int internalFormat/*ignored*/,size_t width,
		  //OpenGL ES 1.0 border must be 0
		  size_t height,int border/* ignored */,
		  GLenum imageFormat,GLenum storeType,
		  const void *texels);

	void texSubImage2D(TexTarget/*ignored*/,
		  int level/* ignored*/,
		  int xoffset,int yoffset,
		  size_t width,size_t height,
		  GLenum imageFormat,
		  GLenum storeType,
		  const void *texels);


	void texParameter(TexTarget target/*ignored*/,
		  TexWrapName wrapName,
		  TexWrapMode texWrapMode);

	void texParameter(TexTarget target/*ignored*/,
		  TexFilterName filterName,
		  TexFilterMode texFilterMode);
     private:

	ObjectNameManager & _objectNameManager;

	bool _texture2DEnabled;

	TextureObject * _activeTextureObject;

	typedef unique_ptr<TextureObject> UniquePtr;

	unordered_map <Name,UniquePtr> _textureObjects;

     };
	
} /* my_gl */


#endif /* end of include guard: TEXTURE_OBJECT_MANAGER_HPP */
