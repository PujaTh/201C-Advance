#pragma once
#include<string>
#include<ctime>
#include<vector>
//#include<iostream>
//#include"User.h"
#include"User.h"
using namespace std;
class SwipingSystem
{

	//Member variables
public:
	User			m_cUser;
	float			m_lAmountTransacted;  /*amount transacted when swiped*/
	time_t          m_timeTransacted;     /*time of transaction*/
	std::string		m_strCategory;		  /*category of transaction*/
	std::string		m_strSubCategory;	  /*sub-category of transaction*/
	
	
	//Userhandler		m_swipedUser(new User(" ",0,0,0));			  /*user transacted*/
	//static void		CheckAmountLimit(Userhandler & cUser); /*check if notification is to be sent to the user*/
	//static void		GenerateAmountLimit(Userhandler & cUser); /*Generate teh notification*/

public:

	SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted, time_t tCreditCardSwiped);
	SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted,User user);
	SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted, User user, time_t tCreditCardSwiped);
	SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted);
	SwipingSystem();// :m_strCategory(""), m_strSubCategory(""), m_lAmountTransacted(0), m_swipedUser(), m_timeTransacted(time(0));
					//Copy Constructor
	SwipingSystem(const SwipingSystem & SwipingSystem);
	//void ReportGeneration::ReportBetweenRange(vector<SwipingSystem> & vSwipingInfo, long lStartRange, long lEndRange, std::wstring strUserName)
	float getAmountTransacted();
	void displayTransaction();
	//~SwipingSystem();

	class ReportGeneration
	{
	public:
		static void		ReportBetweenDates(vector<SwipingSystem> & vSwipingInfo, std::string strStartDate, std::string strEndDate, std::string strUserName);
		static void		ReportBetweenRange(vector<SwipingSystem> & vSwipingInfo, long lStartRange, long lEndRange, std::string strUserName);
		static void		ReportUnderName(vector<SwipingSystem> & vSwipingInfo, std::string  strUserName);
		static void     SortedReport(vector<SwipingSystem> & vSwipingInfo, std::string  strUserName);
		static void     ReportUnderCategory(vector<SwipingSystem> & vSwipingInfo, std::string  strUserName, std::string  strCategory);
	};

};

struct amountSorted
{
	inline bool operator() (const SwipingSystem& object1, const SwipingSystem& object2)
	{
		return (object1.m_lAmountTransacted < object2.m_lAmountTransacted);
	}
};
