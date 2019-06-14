#pragma once
#include<iostream>
#include<exception>
//#include"User.h"
using namespace std;
class OverDrawnCreditLimit : public exception
{
public:
	const char * what() const throw ();
	//User us;

};