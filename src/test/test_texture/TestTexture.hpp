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
#include <cstdlib>

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

	       glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	       glEnable(GL_TEXTURE_2D);


	       glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	       glGenTextures(1,&textureName);

	       glBindTexture(GL_TEXTURE_2D,textureName);

       
	       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);


	       const int segment=64;

	       GLubyte check[segment*segment][3];

	       for (int i=0; i<segment; ++i)
	       {
		    for (int j=0; j<segment; ++j)
		    {

			 bool flag=!(((i&8)==0)^((j&8)==0));
			 GLubyte color=flag*255;

			 float value=255*((i+j)/2.0/segment);

			 check[i*segment+j][0]=color;
			 check[i*segment+j][1]=color;
			 check[i*segment+j][2]=color;
		    }
	       }

	       glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
			 segment,segment,0,
			 GL_RGB,GL_UNSIGNED_BYTE,check);

	  }

	  static void initTexCoord()
	  {

	       glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	       glGenBuffers(1,&texCoordName);	       

	       GLfloat texCoord[3][2]={{0,0},{1,0},{0.5,1}};
	       glBindBuffer(GL_ARRAY_BUFFER,texCoordName);

	       glBufferData(GL_ARRAY_BUFFER,sizeof(texCoord),
			 texCoord,GL_STATIC_DRAW);
	  }

	  static void render()
	  {

	       glBindTexture(GL_TEXTURE_2D,textureName);

	       glMatrixMode(GL_MODELVIEW);
	       glLoadIdentity();

	       glBindBuffer(GL_ARRAY_BUFFER,
			 TestArrayBufferObject::triangleVertexName);
	       glVertexPointer(2,GL_FLOAT,0,0);

	       glBindBuffer(GL_ARRAY_BUFFER,texCoordName);
	       glTexCoordPointer(2,GL_FLOAT,0,0);

	       glDrawArrays(GL_TRIANGLES,0,3);

	  }
     
	  static GLuint texCoordName;
	  static GLuint textureName;
     };

     GLuint TestTexture::texCoordName;
     GLuint TestTexture::textureName;
	
} /* my_gl */


#endif /* end of include guard: TEST_TEXTURE_HPP */
