// ProJect1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<vector>
#include"User.h"
#include"SwipingSystem.h"
using namespace std;
class User;
//class SwipingSystem;
using namespace std;
vector <User> g_registeredUser;
vector<SwipingSystem> g_vSwipedDetails;

void registration(User user)
{
	g_registeredUser.push_back(user);
	cout << "Registered Successfully" << endl;
}

void unRegisterUser(User user)
{
	int i = 0;
	for (auto v : g_registeredUser)
	{

		if (v == user)
		{
			g_registeredUser.erase(g_registeredUser.begin() + i);
			cout << "unRegistered successfull" << endl;
			break;
		}
		else
			i++;

	}
}

void ConvertStringToDate(std::string  strDate, time_t & time)
{
	int nPos = 0;
	int nPrevPos = 0;
	int nDate[3] = { 0 };
	int nPlace = 0;
	while (nPos != string::npos)
	{
		nPos = strDate.find(("/"), nPrevPos);
		string strParamVal = strDate.substr(nPrevPos, nPos - nPrevPos);
		int i_dec = std::stoi(strParamVal, nullptr, 10);
		nDate[nPlace] = i_dec;
		nPlace++;
		nPrevPos = nPos + 1;
	}
	time_t rawtime;
	struct tm * timeinfo;
	std::time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = nDate[2] - 1900;
	timeinfo->tm_mon = nDate[1] - 1;
	timeinfo->tm_mday = nDate[0];
	time = mktime(timeinfo);
}

void main()
{
	vector <User> registeredUser;
	//Users are hardCoded
	 User u1("xyz1", 1233, 0, 10002.59);
	User u2("xyz2", 1234, 0, 2229.19);
	User u3("xyz3", 1235, 0, 2789.20);
	User u4("xyz4", 1236, 0, 3000);
	registration(u1);
	registration(u2);
	registration(u3);
	registration(u4);
	unRegisterUser(u3);
	cout << "\nxyz1, xyz2, xyz3, xyz4 register and out of which xyz3 got unregistered so finaly following user left\n" << endl;
	cout << "UserName" << "\t" << "Card number" << "\t" << "Remaining balance" << endl;
	for (User v : g_registeredUser)
	{
		v.display();
		cout << endl;
	}

	//All Swipes Are hardcoded below
	//swipes of user "xyz" are hardcoded here
	time_t timeS1;
	ConvertStringToDate("03/29/2018", timeS1);
	SwipingSystem s1("xyza", "subxyza", 100,u1, timeS1);
	g_vSwipedDetails.push_back(s1);
	u1.transaction(s1);

	SwipingSystem s2("xyza", "subxyza", 500,u1,time(0));
	g_vSwipedDetails.push_back(s2);
	u1.transaction(s2);

	SwipingSystem s3("xyza", "subxyzb", 10000,u1, time(0));//throwing Excetion if limit got crossed and generate alert(to Showing exception handling)
	g_vSwipedDetails.push_back(s3);
	u1.transaction(s3);

	SwipingSystem s4("xyzb", "subxyza", 500, u1, time(0));
	g_vSwipedDetails.push_back(s4);
	u1.transaction(s4);

	//Swipes of User xyz2 are hardcoded 
	SwipingSystem s5("xyzc", "subxyzc", 500, u2, time(0));
	g_vSwipedDetails.push_back(s5);
	u2.transaction(s5);


	//Swipes of User xyz4 are hardcoded 
	SwipingSystem ss1("xyza", "subxyza", 570,u4, time(0));
	g_vSwipedDetails.push_back(ss1);
	u4.transaction(ss1);

	SwipingSystem ss2("xyza", "subxyza", 1000,u4, time(0));
	g_vSwipedDetails.push_back(ss2);
	u4.transaction(ss2);

	SwipingSystem ss3("xyza", "subxyza", 50,u4, time(0));
	g_vSwipedDetails.push_back(ss3);
	u4.transaction(ss3);

	cout << endl << "All user records" << endl;
	cout << "userName\t cardNumber\t BalanceAmount" << endl;
	for (User v : g_registeredUser)
	{
		v.display();
		cout << endl;
	}

	cout << "\t All Transactions \t" << endl;
	cout << "Amount \t catogry \t subcatogery\tUserName" << endl;
	for (SwipingSystem v : g_vSwipedDetails)
	{
		v.displayTransaction();
		cout << endl;
	}
	cout << "****************************************************************************";
	SwipingSystem::ReportGeneration::ReportBetweenRange(g_vSwipedDetails, 50, 600, "xyz4");
	cout << "****************************************************************************";
	SwipingSystem::ReportGeneration::ReportUnderName(g_vSwipedDetails, "xyz1");
	cout << "****************************************************************************";
	SwipingSystem::ReportGeneration::SortedReport(g_vSwipedDetails, "xyz4");
	cout << "****************************************************************************";
	SwipingSystem::ReportGeneration::ReportUnderCategory(g_vSwipedDetails, "xyz1", "xyza");
	cout << "****************************************************************************";
	SwipingSystem::ReportGeneration::ReportBetweenDates(g_vSwipedDetails, "10/10/2017", "04/29/2017", "xyz1");
	getchar();
}

