/*
 * =====================================================================================
 *
 *       Filename:  TestPoints.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-2-8 18:31:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_POINTS_HPP

#define TEST_POINTS_HPP

#include <cstdlib>

#include "TestClassBase.hpp"



namespace my_gl {

     using std::rand;


     class TestPoints :public TestClassBase{

     public:
	  static void init()
	  {
	       TestClassBase::init();

	       createBuffer();

	  }

	  static GLuint pointsVertexName;

	  static void createBuffer()
	  {
	       glEnableClientState(GL_VERTEX_ARRAY);

	       glGenBuffers(1,&pointsVertexName);

	       glBindBuffer(GL_ARRAY_BUFFER,pointsVertexName);

	       GLfloat randomPoints[2000];

	       for(int i=0;i<1000;++i)
	       {
		    randomPoints[i]=rand()%DEFAULT_WIDTH;
		    randomPoints[i+1]=rand()%DEFAULT_HEIGHT;
	       }

	       glBufferData(GL_ARRAY_BUFFER,sizeof(randomPoints),
			 randomPoints,GL_STATIC_DRAW);

	  }

	  static void render()
	  {
	       glColor4f(1,0.2,0.1,1);

	       glVertexPointer(2,GL_FLOAT,0,0);

	       glDrawArrays(GL_POINTS,0,1000);
	  }

     };

     GLuint TestPoints::pointsVertexName;
	
} /* my_gl */


#endif /* end of include guard: TEST_POINTS_HPP */
