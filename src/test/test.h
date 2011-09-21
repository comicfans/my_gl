/*
 * =====================================================================================
 *
 *       Filename:  test.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-20 15:59:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef TEST_H

#define TEST_H

class tpl{
public:
     void call();

private:
     template<typename T>
	  T get();

     int value;
};



#endif /* end of include guard: TEST_H */
