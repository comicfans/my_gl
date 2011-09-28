/*
 * =====================================================================================
 *
 *       Filename:  TestLink.cpp
 *
 *    Description:  test if all link is ok
 *
 *        Version:  1.0
 *        Created:  2011-9-21 12:14:34
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
	
     SoftContext& instance=SoftContext::getInstance();

     instance.color4f(0, 0, 0, 0);
	return 0;
}
