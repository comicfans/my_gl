/*
 * =====================================================================================
 *
 *       Filename:  test2.cpp
 *
 *    Description:  main
 *
 *        Version:  1.0
 *        Created:  2011-9-20 16:01:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>

using std::cout;
class Base {
public:

     virtual ~Base() {};
};

class Div:public Base
{
public:
	virtual ~Div (){cout<<"div destructor";}

private:
};

int main(int argc, const char *argv[])
{
     Base *p=new Div();

     delete p;
	
}
