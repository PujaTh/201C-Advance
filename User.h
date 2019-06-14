#pragma once
#include<string>
#include<iostream>
#include"SwipingSystem.h"
class SwipingSystem;
using namespace std;
class User 
{
public:
	string m_strUserName;
	int    m_intCreditCardNumber;
	float  m_fCreditLimit;
	float m_fbalanceAmount;
	//SwipingSystem m_sm;

public:

	User();
	User(string userName, int creditCardNumber, float creditLimit, float balanceAmount);
	User(const User& other);
	~User();
	bool operator==(User &rhs);
	void display();
	
void transaction(SwipingSystem sp);
};