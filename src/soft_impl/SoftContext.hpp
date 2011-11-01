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
#include <vector>

#include <boost/ptr_container/ptr_array.hpp>

#include "common/Context.hpp"
#include "common/MatrixStack.hpp"
#include "shader/VertexAttributeBuffer.hpp"
#include "object/ObjectNameManager.hpp"
#include "object/ArrayBufferObjectManager.hpp"

#include "shader/Global.hpp"

#include "ElementIndexManager.hpp"
#include "ViewportParameter.hpp"

namespace my_gl {

     using std::unique_ptr;
     using std::vector;

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

     class SoftContext :public Context{
     public:
     	SoftContext (size_t width=600,size_t height=400);

     	virtual ~SoftContext ();

	//glFlush
	virtual void flush();

	//glGenBuffers
	virtual void genBuffers(size_t size,Name *names);
	//glDeleteBuffers
	virtual void deleteBuffers(size_t size,Name *names);
	//glIsBuffer
	virtual bool isBuffer(Name name) const ;

	//glBindBuffer
	virtual void bindBuffer(BufferTarget target,Name name);

	//glBufferData
	virtual void bufferData(BufferTarget target,size_t size,
		    const void* data, DataUsage usage);

	//glBufferSubData
	virtual void bufferSubData(BufferTarget target,ptrdiff_t offset,
		    size_t size,const void* data);

	//glEnableClient
	virtual void enableClientState(BindState bindState);
	//glDisableClient
	virtual void disableClientState(BindState bindState);

	//glVertexPointer
	virtual void vertexPointer(int componentSize,DataType type, 
		  size_t stride, const void* pointer);

	//glNormal3f
	virtual void normal3f(float nx,float ny,float nz);

	//glNormalPointer
	virtual void normalPointer(DataType type,
		  size_t stride,const void *pointer);
	//glColor4f
	virtual void color4f(float red,float green,
		  float blue,float alpha) ;

	//glColor4ub
	virtual void color4ub(uint8_t red,uint8_t green,
		  uint8_t blue,uint8_t alpha) ;

	//glColorPointer
	virtual void colorPointer(int componentSize,DataType type,
		  size_t stride,const void *pointer);

	//glTexCoordPointer
	virtual void texCoordPointer(int componentSize, 
		  DataType type, size_t stride, const void* pointer);

	//glMatrixMode
	virtual void matrixMode(MatrixMode matrixMode);

	//glPushMatrix
	virtual void pushMatrix();

	//glPopMatrix
	virtual void popMatrix();

	//glTranlatef
	virtual void translatef(float x,float y,float z);

	//glScalef
	virtual void scalef(float x,float y,float z);

	//glRotatef
	virtual void rotatef(float angle,float x,float y,float z);

	//glMultMatrixf
	virtual void multMatrixf(const float* matrix);

	//glDrawArrays 
	virtual void drawArrays(PrimitiveMode primitiveMode,
		  int first,size_t count);

	//glDrawElements TODO
	virtual void drawElements(PrimitiveMode primitiveMode,
		  size_t count,DataType dataType,const void* indices);

	//glFrustumf
	virtual void frustumf(float left,float right,
		  float bottom,float top,float near,float far);

	//glOrtho
	virtual void orthof(float left,float right,
		  float bottom,float top,
		  float near,float far);

	//glViewport
	virtual void viewport(int x,int y,
		  size_t width,size_t height);

	//glLoadIdentity
	virtual void loadIdentity();

	//glClearColor
	virtual void clearColor(float r,float g,float b,float a);

	virtual void clear(FrameBufferMask frameBufferMask);

	ObjectNameManager& getObjectNameManager();

	static SoftContext& getInstance();
     
     private:

	size_t _height;

	size_t _width;

	ObjectNameManager _objectNameManager;

	ArrayBufferObjectManager _arrayBufferObjectManager;

	ptr_array<Vec4Manager,4> _allVec4Manager;

	ElementIndexManager _elementIndexManager;

	template<typename T>
	     T& getVec4Manager();

	MatrixMode _matrixMode;

	MatrixStack _matrixStacks[3];

	void multMatrixf(const Matrix& matrix);

	MatrixStack& currentMatrixStack() ;

	/** 
	 * @brief global uniform values
	 */
	Global _global;

	unique_ptr<VertexShader> _vertexShaderPtr;

	unique_ptr<ClippedPrimitiveGroup> _clippedPrimitiveGroupPtr;

	unique_ptr<FragmentShader> _fragmentShaderPtr;

	unique_ptr<FragmentAttributeBuffer> _fragmentAttributeBufferPtr;

	unique_ptr<Interpolator> _interpolatorPtr;

	unique_ptr<ColorBuffer> _frameBufferPtr;

	unique_ptr<PixelDrawer> _pixelDrawerPtr;

	ptr_array<Clipper,3> _clippers;

	ptr_array<Rasterizer,3> _rasterizers;
	/** 
	 * @brief after vertex transform,store vertex attribute
	 * here
	 */
	VertexAttributeBuffer _vertexAttributeBuffer;

	ViewportParameter _viewportParameter;

	vector<BindState> _activeStreams;
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

	void clipPrimitive
	     (const PrimitiveIndex& primitiveIndex,
		  PrimitiveMode catalog);

	/** 
	 * @brief rasterize the clipped primitive
	 */
	void rasterizePrimitive(PrimitiveMode catalog);


	/** 
	 * @brief common route of drawArrays/drawElements
	 */
	void enterPipeline(PrimitiveMode primitiveMode,
		  size_t vertexNumber,
		  const IndexProvider& indexProvider);

	/** 
	 * @brief construct necessary uniform matrix
	 */
	void prepareGlobalUniform();

     };


} /* my_gl */


#endif /* end of include guard: SOFT_CONTEXT_HPP */
