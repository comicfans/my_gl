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

#include <boost/ptr_container/ptr_array.hpp>

#include "common/Context.hpp"
#include "common/MatrixStack.hpp"
#include "object/ObjectNameManager.hpp"
#include "object/ArrayBufferObjectManager.hpp"

#include "shader/VertexAttributeBuffer.hpp"
#include "shader/Global.hpp"

#include "ElementIndexManager.hpp"
#include "ViewportParameter.hpp"

namespace my_gl {

     using std::unique_ptr;

     using boost::ptr_array;

     class BufferObject;
     class Vec4Manager;
     class VertexShader;

     class FragmentShader;

     class PrimitiveIndex;

     class SoftContext :public Context{
     public:
     	SoftContext ();

     	virtual ~SoftContext ();


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

	//glDrawArrays TODO
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

	ObjectNameManager& getObjectNameManager();

	static SoftContext& getInstance();
     
     private:

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

	unique_ptr<FragmentShader> _fragmentShaderPtr;

	/** 
	 * @brief after vertex transform,store vertex attribute
	 * here
	 */
	VertexAttributeBuffer _vertexAttributeBuffer;

	ViewportParameter _viewportParameter;

	unique_ptr<PrimitiveIndex> _primitiveIndexPtr;

	/** 
	 * @brief using VertexShader to process
	 * vertex (to _transformedVertexBuffer)
	 * 
	 * @param vertexNumber how many vertex shuld be processed
	 * @param offset jump some ahead vertex data(draw parts of data)
	 */
	void transformVertex(size_t vertexNumber,int offset=0);


	/** 
	 * @brief rasterize the clipped primitive
	 */
	void rasterizePrimitive();


	/** 
	 * @brief common route of drawArrays/drawElements
	 * only do post vertex shader stages
	 */
	void postVertexShaderProcess();

	/** 
	 * @brief construct necessary uniform matrix
	 */
	void prepareGlobalUniform();

     };
	
} /* my_gl */


#endif /* end of include guard: SOFT_CONTEXT_HPP */
