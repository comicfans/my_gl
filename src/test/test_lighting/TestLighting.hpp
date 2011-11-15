/*
 * =====================================================================================
 *
 *       Filename:  TestLighting.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-14 8:51:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_LIGHTING_HPP

#define TEST_LIGHTING_HPP

#include <cmath>
#include <algorithm>

#include "TestClassBase.hpp"

namespace my_gl {

     using std::max;
     using std::cos;
     using std::sin;
     using std::atan;
     using std::copy_n;

     const float PI=atan(1)*4;

     class TestLighting :public TestClassBase{
	  public:


	       /** 
		* @brief generate 1/8 sphere
		* 
		* @param segment
		*/
	       static void genSphere(int segment=1)
	       {
		    const int heightSegment=max(segment,1);

		    //generate a lot-lat sphere


		    const float radUnit=PI/2/heightSegment;

		    triangleNumber=heightSegment*(heightSegment*2-1);

		    //at top ,one side is triangle 
		    //the others is a square (two triangles)
		    float mixedData[triangleNumber]
			 //3 vertx * 3 component
			 [3][3];

		    bool top=true;


		    for (int i=0; i<heightSegment; ++i)
		    {
			 for (int j=0; j<heightSegment; ++j)
			 {
			      int triangleIndex=(top?j:(i*2-1)*heightSegment+j*2);

			      float roundRad1=radUnit*j,
				    roundRad2=radUnit*(j+1);

			      float heightRad1=radUnit*i,
				    heightRad2=radUnit*(i+1);

			      float pos1[3]={
				   sin(heightRad1)*cos(roundRad1),
				   sin(heightRad1)*sin(roundRad1),
				   cos(heightRad1)
			      };

			      float pos2[3]={
				   sin(heightRad2)*cos(roundRad1),
				   sin(heightRad2)*sin(roundRad1),
				   cos(heightRad2)
			      };

			      float pos3[3]={
				   sin(heightRad2)*cos(roundRad2),
				   sin(heightRad2)*sin(roundRad2),
				   pos2[2]
			      };

			      float pos4[3]={
				   sin(heightRad1)*cos(roundRad2),
				   sin(heightRad1)*sin(roundRad2),
				   pos1[2]
			      };


			      copy_n(pos1,3,&mixedData[triangleIndex][0][0]);
			      copy_n(pos2,3,&mixedData[triangleIndex][1][0]);
			      copy_n(pos3,3,&mixedData[triangleIndex][2][0]);

			      ++triangleIndex;

			      if (top)
			      {
				   continue;
			      }
			      
			      copy_n(pos1,3,&mixedData[triangleIndex][0][0]);
			      copy_n(pos3,3,&mixedData[triangleIndex][1][0]);
			      copy_n(pos4,3,&mixedData[triangleIndex][2][0]);
			      ++triangleIndex;
			 }

			 top=false;
		    }

		    glGenBuffers(1,&sphereName);		    

		    glBindBuffer(GL_ARRAY_BUFFER,sphereName);

		    glBufferData(GL_ARRAY_BUFFER,
			      triangleNumber*3*3*sizeof(GLfloat),mixedData,GL_STATIC_DRAW);
	       }

	       static void init()
	       {
		    TestClassBase::init();

		    glEnableClientState(GL_VERTEX_ARRAY);

		    glEnableClientState(GL_NORMAL_ARRAY);

		    glEnableClientState(GL_COLOR_ARRAY);

		    glEnable(GL_CULL_FACE);

		    initLighting();

		    genSphere(10);
	       }

	       static void initLighting()
	       {
		    glEnable(GL_LIGHTING);

		    glEnable(GL_LIGHT0);

		    GLfloat matSpecular[]={1,1,1,0};

		    GLfloat ambient[]={0.2,0.2,0.2,0};

		    GLfloat diffuse[]={0,1,0,0};

		    GLfloat lightPosition[]={1000,1000,1000,1};

		    GLfloat whiteLight[]={1,1,1,1};

		    GLfloat modelAmbient[]={0.2,0.2,0.2,1};

		    glMaterialfv(GL_FRONT_AND_BACK,
			      GL_SPECULAR,matSpecular);

		    glMaterialfv(GL_FRONT_AND_BACK,
			      GL_AMBIENT,ambient);

		    glMaterialfv(GL_FRONT_AND_BACK,
			      GL_DIFFUSE,diffuse);

		    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);

		    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);

		    glLightfv(GL_LIGHT0,GL_DIFFUSE,whiteLight);

		    glLightfv(GL_LIGHT0,GL_SPECULAR,whiteLight);

		    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,modelAmbient);

		    glEnable(GL_NORMALIZE);


	       }

	       static void drawPartSphere()
	       {
		    glBindBuffer(GL_ARRAY_BUFFER,sphereName);

		    glVertexPointer(3,GL_FLOAT,0,0);

		    glNormalPointer(GL_FLOAT,0,0);

		    glColorPointer(3,GL_FLOAT,0,0);

		    glDrawArrays(GL_TRIANGLES,0,triangleNumber*3);

	       }
	       static void drawSphere(float x,float y,float z,
			 float rotateY=0, float scale=80)
	       {

		    glMatrixMode(GL_MODELVIEW);

		    glLoadIdentity();

		    glTranslatef(x,y,z);

		    glRotatef(rotateY,0,1,0);

		    glScalef(scale,scale,scale);

		    for (int i=0; i<2; ++i)
		    {
			 glPushMatrix();
			 glRotatef(180*i,1,0,0);

			 for (int j=0; j<2; ++j)
			 {
			      glPushMatrix();
			      glRotatef(180*j,0,1,0);

			      for (int k=0; k<2; ++k)
			      {
				   glPushMatrix();
				   glRotatef(90*k,0,0,1);
				   drawPartSphere();

				   glPopMatrix();
			      }
			      
			      glPopMatrix();
			 }
			 glPopMatrix();
			 
		    }

	       }

	       static void render()
	       {
		    static int loop=100;

		    static int counter=1;

		    glClear(GL_COLOR_BUFFER_BIT);

		    drawSphere(DEFAULT_WIDTH/2,DEFAULT_HEIGHT/2,300,
			      360.0/loop*counter);

		    counter=(counter+1)%loop;
	       }

	       static GLuint sphereName;
	       static int triangleNumber;
     };

     GLuint TestLighting::sphereName;
     int TestLighting::triangleNumber;
	
} /* my_gl */

#endif /* end of include guard: TEST_LIGHTING_HPP */
