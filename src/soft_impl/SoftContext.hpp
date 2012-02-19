/*
 * =====================================================================================
 *
 *       Filename:  SoftContext.hpp
 *
 *    Description:  C++/thread impl of whole opengl pipeline
 *
 *        Version:  1.0
 *        Created:  2011-9-13 15:26:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SOFT_CONTEXT_HPP

#define SOFT_CONTEXT_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/ptr_container/ptr_array.hpp>

#include "common/Context.hpp"
#include "common/MatrixStack.hpp"
#include "shader/VertexAttributeBuffer.hpp"
#include "object/ObjectNameManager.hpp"
#include "object/ArrayBufferObjectManager.hpp"
#include "object/TextureObjectManager.hpp"

#include "shader/MatrixParam.hpp"

#include "ElementIndexManager.hpp"
#include "Rectangle.hpp"
#include "DepthRange.hpp"
#include "lighting/GroupLightingParam.hpp"
#include "shader/TextureFunc.hpp"

namespace my_gl {

     using std::unique_ptr;
     using std::unordered_map;
     using std::vector;

     using boost::ptr_unordered_map;
     using boost::ptr_array;

     class BufferObject;
     class Vec4Manager;
     class VertexShader;

     class FragmentShader;

     class PrimitiveIndex;
     class ClippedPrimitiveGroup;
     class Interpolator;

     class IndexProvider;
     class Clipper;
     class Rasterizer;
     class FragmentAttributeBuffer;
     class ColorBuffer;
     class PixelDrawer;
     class FrameBuffer;

     class SoftContext :public Context{
     public:
     	SoftContext (size_t width=600,size_t height=400);

     	virtual ~SoftContext ();

	//glFlush
	virtual void flush();

	//glGenBuffers
	virtual void genBuffers(size_t size,Name *names);
	//glDeleteBuffers
	virtual void deleteBuffers(size_t size,const Name *names);
	//glIsBuffer
	virtual bool isBuffer(Name name) const ;

	//glBindBuffer
	virtual void bindBuffer(GLenum target,Name name);

	//glBufferData
	virtual void bufferData(GLenum target,size_t size,
		    const void* data, GLenum usage);

	//glBufferSubData
	virtual void bufferSubData(GLenum target,ptrdiff_t offset,
		    size_t size,const void* data);

	//glEnableClient
	virtual void enableClientState(GLenum bindState);
	//glDisableClient
	virtual void disableClientState(GLenum bindState);

	//glVertexPointer
	virtual void vertexPointer(int componentSize,GLenum type, 
		  size_t stride, const void* pointer);

	//glNormal3f
	virtual void normal3f(float nx,float ny,float nz);

	//glNormalPointer
	virtual void normalPointer(GLenum type,
		  size_t stride,const void *pointer);
	//glColor4f
	virtual void color4f(float red,float green,
		  float blue,float alpha) ;

	//glColor4ub
	virtual void color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) ;

	//glColorPointer
	virtual void colorPointer(int componentSize,GLenum type,
		  size_t stride,const void *pointer);

	//glTexCoordPointer
	/** 
	 * @brief OpenGL 1.2.1 add glClientActiveTexture command to 
	 * control which texture unit is enabled to be affected by
	 * glEnableClient and glTexCoordPointer, but all client 
	 * state related function is deprecated. so I decide not to
	 * impl this complex behavior, makes texCoordPointer function
	 * just as other array buffer pointer call
	 * 
	 * @param componentSize
	 * @param type
	 * @param stride
	 * @param pointer
	 */
	virtual void texCoordPointer(int componentSize, 
		  GLenum type, size_t stride, const void* pointer);

	//glGLenum
	virtual void matrixMode(GLenum matrixMode);

	//glPushMatrix
	virtual void pushMatrix();

	//glPopMatrix
	virtual void popMatrix();

	//glLoadMatrix
	virtual void loadMatrixf(const float m[16]);

	//gllMultiMatrix
	virtual void multiMatrixf(const float m[16]);

	//glTranlatef
	virtual void translatef(float x,float y,float z);

	//glScalef
	virtual void scalef(float x,float y,float z);

	//glRotatef
	virtual void rotatef(float angle,float x,float y,float z);

	//glMultMatrixf
	virtual void multMatrixf(const float* matrix);

	//glDrawArrays 
	virtual void drawArrays(GLenum primitiveMode,
		  int first,size_t count);

	//glDrawElements 
	virtual void drawElements(GLenum primitiveMode,
		  size_t count,GLenum dataType,const void* indices);

	//glFrustumf
	virtual void frustum(double left,double right,
		  double bottom,double top,double near,double far);


	//glOrtho
	/** 
	 * @brief OpenGL ES 1.0 single-precision extension
	 * can use float as argument
	 * 
	 * @param left
	 * @param right
	 * @param bottom
	 * @param top
	 * @param near
	 * @param far
	 */
	virtual void ortho(double left,double right,
		  double bottom,double top,
		  double near,double far);


	//glViewport
	virtual void viewport(int x,int y,
		  size_t width,size_t height);

	//glLoadIdentity
	virtual void loadIdentity();

	//glClearColor
	virtual void clearColor(float r,float g,float b,float a);

	//glClear
	virtual void clear(FrameBufferMask frameBufferMask);

	//glClearDepth
	virtual void clearDepth(double depth);

	//glDepthRange
	virtual void depthRange(double near,double far);

	//glDepthFunc
	virtual void depthFunc(GLenum func);

	//glLightf
	virtual void lightf(GLenum lightIndex,
		  GLenum paramName,float param);

	//glLightfv
	virtual void lightfv(GLenum lightIndex,
		  GLenum paramName,const float* param);

	//glMaterialf
	virtual void materialf
	     (GLenum face,GLenum paramName,float param);

	//glMaterialfv
	virtual void materialfv
	     (GLenum face,GLenum paramName,const float *param);

	//glLightModelfv
	virtual void lightModelfv(GLenum paramName,const float* param);

	//glLightModelf
	virtual void lightModelf(GLenum paramName,float param);

	//glGenTextures
	virtual void genTextures(size_t n,Name * names);

	//glFrontFace
	virtual void frontFace(GLenum faceMode);

	//glCullFace
	virtual void cullFace(GLenum face);

	//glTexEnvi
	/** 
	 * @brief OpenGL ES 1.0 support pname=TEXTURE_ENV_COLOR
	 * but this color is only used in COMBINE mode which ES 1.0
	 * not support,so this Function is only used for TEXTURE_ENV_MODE
	 * prototype of this function accept float value as last argument
	 * but here makes a little change
	 * 
	 * @param target
	 * @param pname
	 * @param texEnvMode
	 */
	virtual void texEnvf(int target/*ignored*/,
		  int pname/* ignored*/,TexEnvMode texEnvMode);

	//glBindTexture
	virtual void bindTexture(GLenum/* ignored*/,Name texture);

	//glDeleteTexture
	virtual void deleteTextures(size_t n,const Name *names);

	virtual bool isTexture(Name name);

	//glTexImage2D
	virtual void texImage2D(GLenum/*ignored*/,int level/* ignored*/
		  ,int internalFormat/*ignored*/,size_t width,
		  //OpenGL ES 1.0 border must be 0
		  size_t height,int border/* ignored */,
		  GLenum imageFormat,GLenum storeType,
		  const void *texels);

	//glTexSubImage2D
	virtual void texSubImage2D(GLenum/*ignored*/,
		  int level/* ignored*/,
		  int xoffset,int yoffset,
		  size_t width,size_t height,
		  GLenum imageFormat,
		  GLenum storeType,
		  const void *texels);


	//glTexParameter
	virtual void texParameteri(GLenum target/*ignored*/,
		  TexWrapName wrapName,
		  TexWrapMode texWrapMode);

	//glTexParameter
	virtual void texParameteri(GLenum target/*ignored*/,
		  TexFilterName filterName,
		  TexFilterMode texFilterMode);

	//glCopyTexImage2D
	virtual void copyTexImage2D(GLenum /*ignored*/,int level/* ignored*/,
		  GLenum internalFormat,
		  int x,int y,size_t width,size_t height,int border);
 
	//glCopyTexSubImage2D
	virtual void copyTexSubImage2D(
		  GLenum /*ignored*/,int level/* ignored*/,
		  int xoffset,int yoffset,
		  int x,int y,size_t width,size_t height);

	typedef std::pair<GLenum,int> BindStateAndIndex;

     protected:

	//glEnable lighting
	virtual void enableLighting();
	//glDisable lighting
	virtual void disableLighting();

	//glEnable  (LIGHTn override)
	virtual void enableLightN(GLenum lightIndex);
	//glDisable  (LIGHTn override)
	virtual void disableLightN(GLenum lightIndex);

	//glEnable (texture override)
	virtual void enableTexTarget(GLenum texTarget);
	//glDisable (texture override)
	virtual void disableTexTarget(GLenum texTarget);

	//glEnable (cullFace override)
	virtual void enableCullFace();
	//glDisable (cullFace override)
	virtual void disableCullFace();

	//glEnable (normlize override)
	virtual void enableNormal(GLenum normalizeNormal);
	       
	//glDisable (cullFace override)
	virtual void disableNormal(GLenum normalizeNormal);



	size_t _height;

	size_t _width;

	ObjectNameManager _objectNameManager;

	ArrayBufferObjectManager _arrayBufferObjectManager;

	TextureObjectManager _textureObjectManager;

	ptr_unordered_map<GLenum,Vec4Manager> _allVec4Manager;

	ElementIndexManager _elementIndexManager;

	template<typename T>
	     T& getVec4Manager();


	ptr_array<FrameBuffer,2> _allFrameBuffer;

	template<typename T>
	     T& getFrameBuffer();

	GLenum _matrixMode;

	unordered_map<GLenum,MatrixStack> _matrixStacks;

	void multMatrixf(const Matrix4& matrix);

	MatrixStack& currentMatrixStack() ;

	/** 
	 * @brief global uniform values
	 */
	MatrixParam _matrixParam;

	unique_ptr<VertexShader> _vertexShaderPtr;

	unique_ptr<ClippedPrimitiveGroup> _clippedPrimitiveGroupPtr;

	unique_ptr<FragmentShader> _fragmentShaderPtr;

	unique_ptr<FragmentAttributeBuffer> _fragmentAttributeBufferPtr;

	unique_ptr<Interpolator> _interpolatorPtr;

	unique_ptr<PixelDrawer> _pixelDrawerPtr;

	ptr_unordered_map<GLenum,Clipper> _clippers;

	ptr_unordered_map<GLenum,Rasterizer> _rasterizers;
	/** 
	 * @brief after vertex transform,store vertex attribute
	 * here
	 */
	VertexAttributeBuffer _vertexAttributeBuffer;

	ViewportParameter _viewportParameter;
	DepthRange _depthRange;

     

	vector<BindStateAndIndex> _activeStreams;


	/** 
	 * @brief if *pointer family function is called
	 * current Array Buffer Object is copy to corresponding
	 * Binding. if zero is binded as current Array Buffer,
	 * client vertex pointer is used
	 *
	 */
	void copyArrayBufferBind(GLenum bindState);

	/** 
	 * @brief using VertexShader to process
	 * vertex (to _transformedVertexBuffer)
	 *
	 * offset of *indices as offset in buffer object 
	 * is wrapped already in IndexProvider,
	 * because :
	 * the offset of drawArrays means how many vertex to skip
	 *
	 * but indices as offset in BufferObject of drawElements means
	 * how many machine units to skip in index array
	 * 
	 * 
	 * @param primitiveIndex which vertex is used to draw
	 */
	void vertexShaderStage(size_t vertexNumber,
		  const IndexProvider& indexProvider);

	void fragmentShaderStage();

	/** 
	 * @brief currently override this function to use custom 
	 *        ClippedPrimitiveGroup,need refactor (use factory ?)
	 * 
	 * @param primitiveIndex
	 * @param catalog
	 * 
	 * @return 
	 */
	virtual void clipPrimitive
	     (const PrimitiveIndex& primitiveIndex,
		  GLenum catalog);

	/** 
	 * @brief rasterize the clipped primitive
	 */
	void rasterizePrimitive(GLenum catalog);


	/** 
	 * @brief common route of drawArrays/drawElements
	 */
	void enterPipeline(GLenum primitiveMode,
		  size_t vertexNumber,
		  const IndexProvider& indexProvider);

	/** 
	 * @brief construct necessary uniform matrix
	 */
	void prepareGlobalUniform();

	GroupLightingParam _groupLightingParam;

	bool _lightingEnabled;

	bool _twoSideLightingEnabled;

	bool _textureEnabled;

	TextureFunc _textureFunc;

	/** 
	 * @brief switch vertex shader and fragment shader
	 *  depends on light and texture state
	 */
	void lightingStateChange();
	void textureStateChange();

     };


} /* my_gl */


#endif /* end of include guard: SOFT_CONTEXT_HPP */
