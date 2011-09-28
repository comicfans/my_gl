/*
 * =====================================================================================
 *
 *       Filename:  Vec4SizeTest.cpp
 *
 *    Description:  test sizeof Vec4
 *
 *        Version:  1.0
 *        Created:  2011-9-28 9:57:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>

#include "common/Vec4.hpp"


using std::cout;
using std::endl;

using my_gl::Vec4;

class Vec4Class
{
	       float _values[4];
 

};

int main(int argc, const char *argv[])
{
	
     cout<<sizeof(Vec4)<<" "<<sizeof(Vec4Class)<<endl;
}
