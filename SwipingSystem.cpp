#include "stdafx.h"
#include <algorithm>
#include"SwipingSystem.h"

void ConvertStringToDate(std::string & strDate, time_t & time)
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

SwipingSystem::SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted, time_t tCreditCardSwiped) :
	m_strCategory(strCategory), m_strSubCategory(strSubCategory), m_lAmountTransacted(lAmountTransacted), m_timeTransacted(tCreditCardSwiped)
{
};

SwipingSystem::SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted) :
	m_strCategory(strCategory), m_strSubCategory(strSubCategory), m_lAmountTransacted(lAmountTransacted)
{
};

SwipingSystem::SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted,User user) :
	m_strCategory(strCategory), m_strSubCategory(strSubCategory), m_lAmountTransacted(lAmountTransacted),m_cUser(user)
{
};

SwipingSystem::SwipingSystem(string strCategory, string strSubCategory, float lAmountTransacted, User user, time_t tCreditCardSwiped) :
	m_strCategory(strCategory), m_strSubCategory(strSubCategory), m_lAmountTransacted(lAmountTransacted), m_cUser(user),m_timeTransacted(tCreditCardSwiped)
{
};
SwipingSystem::SwipingSystem() :m_strCategory(""), m_strSubCategory(""), m_lAmountTransacted(0), /*m_swipedUser(),*/ m_timeTransacted(time(0))
{};

SwipingSystem::SwipingSystem(const SwipingSystem & SwipingSystem)
{
	m_strCategory = SwipingSystem.m_strCategory;
	m_strSubCategory = SwipingSystem.m_strSubCategory;
	m_lAmountTransacted = SwipingSystem.m_lAmountTransacted;
	//m_swipedUser = SwipingSystem.m_swipedUser;
	m_timeTransacted = SwipingSystem.m_timeTransacted;
	m_cUser = SwipingSystem.m_cUser;
};

float SwipingSystem::getAmountTransacted()
{
	return m_lAmountTransacted;
}

void SwipingSystem::displayTransaction()
{

	cout << m_lAmountTransacted << "\t " << m_strCategory << "\t \t" << m_strSubCategory << "\t\t " << m_cUser.m_strUserName << endl;

}

void SwipingSystem::ReportGeneration::ReportBetweenRange(vector<SwipingSystem> & vSwipingInfo, long lStartRange, long lEndRange, std::string strUserName)
{
	std::vector<SwipingSystem>::iterator itrSwipingInfo;
	bool bRecordExists = false;
	std::cout << "\nTransactions made by User " << strUserName << " between Range " << lStartRange << " to " << lEndRange << std::endl;
	std::cout/* << "Date" << "\t\t" */<< "Amount" << "\t" << "Category" << "\t" << "Sub - Category" << "\n";
	for (SwipingSystem itrSwipingInfo: vSwipingInfo)
	{
		if (itrSwipingInfo.m_cUser.m_strUserName.compare(strUserName) == 0)
		{
			if (itrSwipingInfo.m_lAmountTransacted >= lStartRange && itrSwipingInfo.m_lAmountTransacted <= lEndRange)
			{
				bRecordExists = true;
				std::time_t time(itrSwipingInfo.m_timeTransacted);
				std::tm * ptm = localtime(&time);
				char buffer[11];
				//Format: 15.06.2009 
				std::strftime(buffer, 11, "%d.%m.%Y", ptm);
				std::cout << buffer << "\t" << itrSwipingInfo.m_lAmountTransacted << "\t" << itrSwipingInfo.m_strCategory << "\t\t" << itrSwipingInfo.m_strSubCategory << std::endl;
			}
		}
	}
	if (!bRecordExists)
	{
		std::cout << "Record does not exists\n";
	}
}

void SwipingSystem::ReportGeneration::ReportUnderName(vector<SwipingSystem> & vSwipingInfo, std::string  strUserName)
{
	std::vector<SwipingSystem>::iterator itrSwipingInfo;
	std::cout << "\nTransactions made by User " << strUserName << std::endl;
	std::cout << "Date" << "\t\t" << "Amount" << "\t" << "Category" << "\t" << "Sub - Category" << "\n";
	bool bRecordExists = false;
	for (itrSwipingInfo = vSwipingInfo.begin(); itrSwipingInfo != vSwipingInfo.end(); itrSwipingInfo++)
	{
		if (itrSwipingInfo->m_cUser.m_strUserName.compare(strUserName) == 0)
		{
			bRecordExists = true;
			std::time_t time(itrSwipingInfo->m_timeTransacted);
			std::tm * ptm = std::localtime(&time);
			// size+1 for null character
			char buffer[11];
			// Format: 15.06.2009 
			std::strftime(buffer, 11, "%d.%m.%Y", ptm);
			std::cout << buffer << "\t" << itrSwipingInfo->m_lAmountTransacted << "\t" << itrSwipingInfo->m_strCategory << "\t\t" << itrSwipingInfo->m_strSubCategory << std::endl;
		}
	}
	if (!bRecordExists)
	{
		std::cout << "Record does not exists\n";
	}
}

void  SwipingSystem::ReportGeneration::SortedReport(vector<SwipingSystem> & vSwipingInfo, std::string  strUserName)
{
	vector<SwipingSystem> vUserSwipeInfo;
	std::vector<SwipingSystem>::iterator itrSwipingInfo;
	bool bRecordExists = false;
	for (itrSwipingInfo = vSwipingInfo.begin(); itrSwipingInfo != vSwipingInfo.end(); itrSwipingInfo++)
	{
		if (itrSwipingInfo->m_cUser.m_strUserName.compare(strUserName) == 0)
		{
			vUserSwipeInfo.push_back(*itrSwipingInfo);
		}
	}
	std::sort(vUserSwipeInfo.begin(), vUserSwipeInfo.end(), amountSorted());
	std::cout << "\nReport of user " << strUserName << " in sorted way according to the amount trnasacted " << std::endl;
	std::cout << "Date" << "\t\t" << "Amount" << "\t" << "Category" << "\t" << "Sub - Category" << "\n";
	for (itrSwipingInfo = vUserSwipeInfo.begin(); itrSwipingInfo != vUserSwipeInfo.end(); itrSwipingInfo++)
	{
		if (itrSwipingInfo->m_cUser.m_strUserName.compare(strUserName) == 0)
		{
			bRecordExists = true;
			std::time_t time(itrSwipingInfo->m_timeTransacted);
			std::tm * ptm = std::localtime(&time);
			char buffer[11];
			// Format: 15.06.2009 
			std::strftime(buffer, 11, "%d.%m.%Y", ptm);
			std::cout << buffer << "\t" << itrSwipingInfo->m_lAmountTransacted << "\t" << itrSwipingInfo->m_strCategory << "\t\t" << itrSwipingInfo->m_strSubCategory << std::endl;
		}
	}
	if (!bRecordExists)
	{
		std::cout << "Record does not exists\n";
	}
}

void  SwipingSystem::ReportGeneration::ReportUnderCategory(vector<SwipingSystem> & vSwipingInfo, std::string  strUserName, std::string  strCategory)
{
	std::vector<SwipingSystem>::iterator itrSwipingInfo;
	bool bRecordExists = false;
	std::cout << "\nTransactions made by User " << strUserName << " under category ";
	std::cout << strCategory << std::endl;
	std::cout << "Date" << "\t\t" << "Amount" << "\t" << "Category" << "\t" << "Sub - Category" << "\n";
	float amountSpentOnCat=0;
	for (itrSwipingInfo = vSwipingInfo.begin(); itrSwipingInfo != vSwipingInfo.end(); itrSwipingInfo++)
	{
		if (itrSwipingInfo->m_cUser.m_strUserName.compare(strUserName) == 0)
		{
			if (itrSwipingInfo->m_strCategory.compare(strCategory) == 0)
			{
				amountSpentOnCat = amountSpentOnCat + itrSwipingInfo->m_lAmountTransacted;
				bRecordExists = true;
				std::time_t time(itrSwipingInfo->m_timeTransacted);
				std::tm * ptm = std::localtime(&time);
				char buffer[11];
				// Format: 15.06.2009 
				std::strftime(buffer, 11, "%d.%m.%Y", ptm);
				std::cout << buffer << "\t" << itrSwipingInfo->m_lAmountTransacted << "\t" << itrSwipingInfo->m_strCategory << "\t\t" << itrSwipingInfo->m_strSubCategory << std::endl;
				
			}
		}
	}
	std::cout << "Total Amount spent on Category " << strCategory << " is " << amountSpentOnCat << endl;;
	if (!bRecordExists)
	{
		std::cout << "Record does not exists\n";
	}
}

void SwipingSystem::ReportGeneration::ReportBetweenDates(vector<SwipingSystem> & vSwipingInfo, std::string strStartDate, std::string strEndDate, std::string strUserName)
{
	//struct tm tm;
	time_t tStartDate;
	ConvertStringToDate(strStartDate, tStartDate);
	time_t tEndDate;
	ConvertStringToDate(strEndDate, tEndDate);

	if (tEndDate == -1 || tStartDate == -1)
	{
		throw std::exception("Invalid date");
	}
	bool bRecordExists = false;
	std::vector<SwipingSystem>::iterator itrSwipingInfo;
	std::cout << "\nTransactions made by User " << strUserName << " between dates ";
	std::cout << strStartDate << " to " << strEndDate << std::endl;
	std::cout << "Date" << "\t\t" << "Amount" << "\t" << "Category" << "\t" << "Sub - Category" << "\n";
	for (itrSwipingInfo = vSwipingInfo.begin(); itrSwipingInfo != vSwipingInfo.end(); itrSwipingInfo++)
	{
		if (itrSwipingInfo->m_cUser.m_strUserName.compare(strUserName) == 0)
		{
			if (difftime(itrSwipingInfo->m_timeTransacted, tStartDate) > 0 && difftime(itrSwipingInfo->m_timeTransacted, tEndDate) < 0)
			{
				bRecordExists = true;
				std::time_t time(itrSwipingInfo->m_timeTransacted);
				std::tm * ptm = std::localtime(&time);
				char buffer[11];
				std::strftime(buffer, 11, "%d.%m.%Y", ptm);
				std::cout << buffer << "\t" << itrSwipingInfo->m_lAmountTransacted << "\t" << itrSwipingInfo->m_strCategory << "\t\t" << itrSwipingInfo->m_strSubCategory << std::endl;
			}
		}
	}
	if (!bRecordExists)
	{
		std::cout << "Record does not exists\n";
	}
}

