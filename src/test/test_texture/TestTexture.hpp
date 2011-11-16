/*
 * =====================================================================================
 *
 *       Filename:  TestTexture.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-15 22:41:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_TEXTURE_HPP

#define TEST_TEXTURE_HPP

#include "test_array_buffer_object/TestArrayBufferObject.hpp"

namespace my_gl {

     class TestTexture {
     public:

	  static void init()
	  {
	       TestArrayBufferObject::init();
	       initTexCoord();
	       loadTexture();
	  }

	  static void loadTexture()
	  {
	       glEnable(GL_TEXTURE_2D);

//	       glGenTextures(1,&textureName);

	       glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,
			 GL_REPLACE);

//	       glBindTexture(GL_TEXTURE_2D,textureName);

	       const int segment=10;

	       GLubyte check[segment*segment][4];

	       for (int i=0; i<segment; ++i)
	       {
		    for (int j=0; j<segment; ++j)
		    {
			 bool flag=((i+j)%2==0);

			 check[i*segment+j][0]=255;//(flag?128:0);
			 check[i*segment+j][1]=0;//(flag?64:255);
			 check[i*segment+j][2]=0;//(flag?32:8);
		    }
	       }

	       glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
			 segment,segment,0,
			 GL_RGBA,GL_UNSIGNED_BYTE,check);

	  }

	  static void initTexCoord()
	  {

	       glEnableClientState(GL_VERTEX_ARRAY);
	       glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	       glGenBuffers(1,&texCoordName);	       


	       GLfloat texCoord[3][2]={{0,0},{1,0},{0.5,0.5}};
	       glBindBuffer(GL_ARRAY_BUFFER,texCoordName);

	       glBufferData(GL_ARRAY_BUFFER,sizeof(texCoord),
			 texCoord,GL_STATIC_DRAW);
	  }

	  static void render()
	  {
	       const int segment=10;

	       GLubyte check[segment*segment][4];

	       for (int i=0; i<segment; ++i)
	       {
		    for (int j=0; j<segment; ++j)
		    {
			 bool flag=((i+j)%2==0);

			 check[i*segment+j][0]=255;//(flag?128:0);
			 check[i*segment+j][1]=0;//(flag?64:255);
			 check[i*segment+j][2]=0;//(flag?32:8);
		    }
	       }

	       glBindTexture(GL_TEXTURE_2D,0);
	       glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
			 segment,segment,0,
			 GL_RGBA,GL_UNSIGNED_BYTE,check);



	       glMatrixMode(GL_MODELVIEW);
	       glLoadIdentity();

	       glBindBuffer(GL_ARRAY_BUFFER,
			 TestArrayBufferObject::triangleVertexName);
	       glVertexPointer(2,GL_FLOAT,0,0);

	       GLfloat texCoord[3][2]={{0,0},{1,0},{0.5,0.5}};

	       glBindBuffer(GL_ARRAY_BUFFER,0);
	       glTexCoordPointer(2,GL_FLOAT,0,texCoord);

	       glDrawArrays(GL_TRIANGLES,0,3);

	  }
     
	  static GLuint texCoordName;
	  static GLuint textureName;
     };

     GLuint TestTexture::texCoordName;
     GLuint TestTexture::textureName;
	
} /* my_gl */


#endif /* end of include guard: TEST_TEXTURE_HPP */
