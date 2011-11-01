/*
 * =====================================================================================
 *
 *       Filename:  TestSoftImpl.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-28 23:47:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "SoftContext.hpp"
#include "SDL.h"

using namespace my_gl;

     int width=400,
	 height=300;

     SoftContext softContext(width,height);
	Context & context =softContext;


	static const float  quodVertex[][2]={{0,2},{2,203},{204,204},{205,3}};
     
static const float directLines[][2]={{10,10},{10,200},{200,200},{200,10},{150,5}};

	static const float  stripVertex[][2]={{5,2},{10,203},{205,16},{204,204}};

void testLines()
{
     context.matrixMode(MatrixMode::MODEL_VIEW);

     context.loadIdentity();

     context.clear(COLOR_BUFFER_BIT);

     context.vertexPointer(2, DataType::FLOAT, 0, quodVertex);

	context.color4f(0.5, 0.5, 0.5, 0.5);

	context.drawArrays(PrimitiveMode::LINE_LOOP, 0, 4);

	context.flush();

	SDL_Delay(2000);


}

void testSpecialLine()
{

     context.matrixMode(MatrixMode::MODEL_VIEW);

     context.loadIdentity();
     context.clear(COLOR_BUFFER_BIT);

     context.vertexPointer(2, DataType::FLOAT, 0, directLines);

	context.color4f(0.5, 0.5, 0.5, 0.5);

	context.drawArrays(PrimitiveMode::LINE_LOOP, 0, 5);

	context.flush();

	SDL_Delay(2000);

}

void init()
{
	context.viewport(0,0,width,height);

	context.enableClientState(BindState::VERTEX);

	context.matrixMode(MatrixMode::PROJECTION);

	context.loadIdentity();

	context.orthof( 0,width,0,height,-1,1);

	context.matrixMode(MatrixMode::MODEL_VIEW);

	context.loadIdentity();

	context.clearColor(0.5,0,0,0);
}

void testTriangles()
{

     context.matrixMode(MatrixMode::MODEL_VIEW);
	  
     context.color4f(0.0, 0.0, 0.0, 0.0);
     for (int i=0; i<10; ++i)
     {
	  context.clear(COLOR_BUFFER_BIT);

	  context.loadIdentity();

	  context.translatef(-10*i,-10*i,0);
	  //context.rotatef(12,0,0,1);

	  context.vertexPointer(2,DataType::FLOAT,0,&stripVertex[0][0]);


	  context.drawArrays(PrimitiveMode::TRIANGLE_STRIP,1,3);
	
	  context.flush();

	  SDL_Delay(200);

     }

}

void testLineClip()
{

     context.matrixMode(MatrixMode::MODEL_VIEW);

     context.loadIdentity();
     context.clear(COLOR_BUFFER_BIT);

     context.vertexPointer(2, DataType::FLOAT, 0, directLines);

	context.color4f(0.5, 0.5, 0.5, 0.5);

	context.translatef(0,-30,0);

	context.drawArrays(PrimitiveMode::LINE_LOOP, 0, 5);

	context.flush();

	SDL_Delay(2000);


}

extern "C"
{

int main(int argc, char **argv)
{

     init();

    testTriangles();
    testLines();
    testLineClip();
    testSpecialLine();

     return 0;
}
}
