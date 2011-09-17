/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-17 11:06:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <typeinfo>
#include <iostream>

using std::type_info;
using std::cout;
class Base{
public:

     virtual void call()
     {
	  cout<<"base";
     }

private:
	/* data */
};

class Div
{
public:
	Div ()
	{
	     cout<<typeid(this).name()<<'\n';
	     call();
	}

	virtual void call()
	{
	     cout<<"div\n";
	}

private:
	/* data */
};

int main(int argc, const char *argv[])
{
	
     Div div;
	return 0;
}
