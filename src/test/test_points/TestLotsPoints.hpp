/*
 * =====================================================================================
 *
 *       Filename:  TestLotsPoints.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/2/29 18:24:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_LOTS_POINTS_HPP

#define TEST_LOTS_POINTS_HPP

#include <cstdlib>

#include "TestPoints.hpp"

namespace my_gl {

     using std::rand;

     class TestLotsPoints :public TestPoints{
     public:

	  static void init()
	  {
	       TestClassBase::init();

	       createBuffer();
	  }

	  static void render()
	  {

	       glColor4f(1,0.2,0.4,1);

	       glBindBuffer(GL_ARRAY_BUFFER,pointsVertexName);

	       glVertexPointer(2,GL_FLOAT,0,0);

	       glDrawArrays(GL_POINTS,0,pointNumber);
	  }

	  static void createBuffer()
	  {
	       glEnableClientState(GL_VERTEX_ARRAY);

	       pointNumber=100000;

	       GLfloat gridPoints[pointNumber*2];

	       for(int i=0;i<pointNumber;++i)
	       {
		    gridPoints[i*2]=rand()%DEFAULT_WIDTH;
		    gridPoints[i*2+1]=rand()%DEFAULT_HEIGHT;
	       }

	       glGenBuffers(1,&pointsVertexName);

	       glBindBuffer(GL_ARRAY_BUFFER,pointsVertexName);

	       glBufferData(GL_ARRAY_BUFFER,pointNumber*sizeof(float)*2,
			 gridPoints,GL_STATIC_DRAW);
	       
	  }
	

     };
	
} /* my_gl */


#endif /* end of include guard: TEST_LOTS_POINTS_HPP */
