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

using namespace my_gl;


int main(int argc, const char *argv[])
{
     int width=400,
	 height=300;

     SoftContext softContext(width,height);
	Context & context =softContext;
	return 0;
}
