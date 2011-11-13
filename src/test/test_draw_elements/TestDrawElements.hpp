/*
 * =====================================================================================
 *
 *       Filename:  TestDrawElements.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-11 9:47:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_DRAW_ELEMENTS_HPP

#define TEST_DRAW_ELEMENTS_HPP

#include "TestClassBase.hpp"
#include <cmath>
#include <algorithm>


namespace my_gl {

     using std::copy_n;
     using std::max;

     static float CUBE_VERTEX[8][4]={
	  {1,1,1,0},{-1,1,1,0},{-1,-1,1,0},{1,-1,1,0},
	  {1,1,-1,0},{-1,1,-1,0},{-1,-1,-1,0},{1,-1,-1,0}};

     static float CUBE_COLOR[8*4];

     static unsigned short CUBE_INDEX[]={
	  0,1,3,3,1,2,
	  3,2,7,7,2,6,
	  7,6,4,4,6,5,
	  4,5,0,0,5,1,
	  5,6,1,1,6,2,
	  7,4,3,3,4,0};

     class TestDrawElements :public TestClassBase{
     public:

	  static void generateColor()
	  {
	       copy_n(&CUBE_VERTEX[0][0],8*4,CUBE_COLOR);

	       for(float &value:CUBE_COLOR)
	       {
		    value=max<float>(value,0);
	       }

	  }

	  static void init()
	  {
	       TestClassBase::init();

	       generateColor();

	       genCube();

	       glClearColor(0,0,0,0);
	  }

	  static void drawCube()
	  {
	       glClear(GL_COLOR_BUFFER_BIT);

	       glBindBuffer(GL_ARRAY_BUFFER,cubeVertexName);
	       glVertexPointer(3,GL_FLOAT,sizeof(GL_FLOAT)*4,0);
	       

	       glBindBuffer(GL_ARRAY_BUFFER,cubeColorName);
	       glColorPointer(4,GL_FLOAT,0,0);

	       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,cubeIndexName);

	       glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_SHORT,0);

	  }

	  static void transformPosition()
	  {
	       static int counter=0;

	       static const int loop=100;

	       glTranslatef(DEFAULT_WIDTH/2,DEFAULT_HEIGHT/2,0);

	       
	       glRotatef(360.0/loop*counter,0,1,0);

	       glRotatef(45,0,0,1);

	       glRotatef(45,1,0,0);

	       glScalef(80,80,80);

	       counter=(counter+1)%loop;

	  }

	  static void render()
	  {


	       glMatrixMode(GL_MODELVIEW);

	       glLoadIdentity();

	       transformPosition();

	       drawCube();
	       	       
	  }

	  static void genCube()
	  {

	       glEnableClientState(GL_VERTEX_ARRAY);

	       glEnableClientState(GL_COLOR_ARRAY);

	       glGenBuffers(1,&cubeIndexName);
	       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,cubeIndexName);
	       glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			 sizeof(CUBE_INDEX),CUBE_INDEX,GL_STATIC_DRAW);


	       glGenBuffers(1,&cubeVertexName);
	       glBindBuffer(GL_ARRAY_BUFFER,cubeVertexName);
	       glBufferData(GL_ARRAY_BUFFER,
			 sizeof(CUBE_VERTEX),CUBE_VERTEX,GL_STATIC_DRAW);

	       glGenBuffers(1,&cubeColorName);
	       glBindBuffer(GL_ARRAY_BUFFER,cubeColorName);
	       glBufferData(GL_ARRAY_BUFFER,
			 sizeof(CUBE_COLOR),CUBE_COLOR,GL_STATIC_DRAW);


	  }


	  static GLuint cubeIndexName;

	  static GLuint cubeVertexName;

	  static GLuint cubeColorName;

     };
	
     GLuint TestDrawElements::cubeVertexName;
     GLuint TestDrawElements::cubeIndexName;
     GLuint TestDrawElements::cubeColorName;
} /* my_gl */

#endif /* end of include guard: TEST_DRAW_ELEMENTS_HPP */
