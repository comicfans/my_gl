/*
 * =====================================================================================
 *
 *       Filename:  Inst.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-3 0:59:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Inst.hpp"


template<int T>
Inst<T>::Inst()
{}

template<int T>
void Inst<T>::call(){}

template class Inst<3>;
/*  
namespace {

     struct X
     {
	  Inst<int> abc;
     };

     X x;
}*/
