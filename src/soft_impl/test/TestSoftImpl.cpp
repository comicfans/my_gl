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

extern "C"
{

int main(int argc, char **argv)
{
     int width=400,
	 height=300;

     SoftContext softContext(width,height);
	Context & context =softContext;


	context.viewport(0,0,width,height);

	context.enableClientState(BindState::VERTEX);

	static const float  vertex[][2]={{0,2},{2,203},{204,204},{205,3}};

	context.matrixMode(MatrixMode::PROJECTION);

	context.loadIdentity();

	context.orthof( 0,width,0,height,-1,1);

	context.vertexPointer(2, DataType::FLOAT, 0, &vertex[0][0]);

	context.color4f(0.5, 0.5, 0.5, 0.5);

	context.matrixMode(MatrixMode::MODEL_VIEW);

	context.loadIdentity();

	context.drawArrays(PrimitiveMode::LINE_LOOP, 0, 4);

	context.flush();

	SDL_Delay(2000);

	return 0;
}
}
