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

#include <boost/ptr_container/ptr_vector.hpp>

#include "Context.hpp"
#include "object/ObjectNameManager.hpp"
#include "object/ArrayBufferObjectManager.hpp"


namespace my_gl {

     using boost::ptr_vector;

     class BufferObject;
     class VectorManager;


     class SoftContext :public Context{
     public:
     	SoftContext ();

     	virtual ~SoftContext ();


	//glGenBuffers
	void genBuffers(size_t size,Name *names);
	//glDeleteBuffers
	void deleteBuffers(size_t size,Name *names);
	//glIsBuffer
	bool isBuffer(Name name) const noexcept;

	void normal(float nx,float ny,float nz);

	ObjectNameManager& getObjectNameManager();

	static SoftContext& getInstance();
     
     private:

	ObjectNameManager _objectNameManager;

	ArrayBufferObjectManager _arrayBufferObjectManager;

	ptr_vector<VectorManager> _allVectorManager;

	template<typename T>
	     T& getVectorManager(BindState bindState);

     };
	
} /* my_gl */


#endif /* end of include guard: SOFT_CONTEXT_HPP */
