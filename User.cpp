#include "stdafx.h"
#include"User.h"
#include"OverDrawnCreditLimit.h"
User::User()
{
	m_strUserName = "";
	m_intCreditCardNumber = 0;
	m_fCreditLimit = 0;
	m_fbalanceAmount = 0;
}

User::User(string userName, int creditCardNumber, float creditLimit, float balanceAmount) :m_strUserName(userName), m_intCreditCardNumber(creditCardNumber), m_fCreditLimit(creditLimit), m_fbalanceAmount(balanceAmount)
{

}

User::User(const User& other)
{
	m_strUserName = other.m_strUserName;
	m_intCreditCardNumber = other.m_intCreditCardNumber;
	m_fCreditLimit = other.m_fCreditLimit;
	m_fbalanceAmount = other.m_fbalanceAmount;
}

User::~User()
{

}

void User::display()
{
	//cout << "Transaction done by " << m_strUserName << " having card number " << m_intCreditCardNumber << " balance left " << m_fbalanceAmount;
	
	cout << m_strUserName << " \t\t" << m_intCreditCardNumber << "\t\t" << m_fbalanceAmount;
}

bool User:: operator==(User &rhs)
{
	return(this->m_fCreditLimit == rhs.m_fCreditLimit && this->m_strUserName == rhs.m_strUserName && this->m_intCreditCardNumber == rhs.m_intCreditCardNumber);

}

void User::transaction(SwipingSystem sm)
{
	try {
		m_fbalanceAmount = m_fbalanceAmount - sm.getAmountTransacted();
		cout << "transaction of " << sm.getAmountTransacted() << "\t done by " << this->m_strUserName << "\t[credit left --> " << m_fbalanceAmount << " ]" << endl;
		if (m_fbalanceAmount < m_fCreditLimit) throw OverDrawnCreditLimit();
	}
	catch (OverDrawnCreditLimit ex)
	{
		std::cout << ex.what() << std::endl;
		cout << "************Notiication Alert!!!!!************" << endl;
		cout << " Name:\t" << m_strUserName << "\n Card Number:\t" << m_intCreditCardNumber << "\n Balance Amount:\t"<<m_fbalanceAmount << endl;
		cout << "**********************************************" << endl;
	}
}
