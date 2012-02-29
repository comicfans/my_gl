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


#include "TestClassBase.hpp"



namespace my_gl {


     class TestPoints :public TestClassBase{

     public:
	  static void init()
	  {
	       TestClassBase::init();

	       createBuffer();

	  }

	  static GLuint pointsVertexName;
	  static GLuint pointsColorName;

	  static int factor;

	  static int pointNumber;

	  static void createBuffer()
	  {
	       glEnableClientState(GL_VERTEX_ARRAY);
	       glEnableClientState(GL_COLOR_ARRAY);

	       factor=100;

	       int yNumber=DEFAULT_HEIGHT/factor,
		   xNumber=DEFAULT_WIDTH/factor;

	       pointNumber=xNumber*yNumber;

	       GLfloat gridPoints[pointNumber*2];

	       GLfloat gridColors[pointNumber*3];

	       for (int y=0; y<yNumber; ++y)
	       {
		    for (int x=0; x<xNumber; ++x)
		    {
			 int index=y*xNumber+x;

			 gridPoints[index*2]=x*factor+50;
			 gridPoints[index*2+1]=y*factor+50;

			 gridColors[index*3]=float(index)/pointNumber;
			 gridColors[index*3+1]=float(index)/pointNumber;
			 gridColors[index*3+2]=float(index)/pointNumber;
		    }
		    
	       }
	
	       glGenBuffers(1,&pointsVertexName);

	       glBindBuffer(GL_ARRAY_BUFFER,pointsVertexName);

	       glBufferData(GL_ARRAY_BUFFER,pointNumber*sizeof(float)*2,
			 gridPoints,GL_STATIC_DRAW);

	       glGenBuffers(1,&pointsColorName);

	       glBindBuffer(GL_ARRAY_BUFFER,pointsColorName);

	       glBufferData(GL_ARRAY_BUFFER,pointNumber*sizeof(float)*3,
			 gridColors,GL_STATIC_DRAW);

	  }

	  static void render()
	  {

	       glBindBuffer(GL_ARRAY_BUFFER,pointsVertexName);

	       glVertexPointer(2,GL_FLOAT,0,0);

	       glBindBuffer(GL_ARRAY_BUFFER,pointsColorName);

	       glColorPointer(3,GL_FLOAT,0,0);

	       glDrawArrays(GL_POINTS,0,20);
	  }

     };

     GLuint TestPoints::pointsVertexName;
     GLuint TestPoints::pointsColorName;
     int TestPoints::factor;
     int TestPoints::pointNumber;
	
} /* my_gl */


#endif /* end of include guard: TEST_POINTS_HPP */
