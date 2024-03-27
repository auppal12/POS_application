//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Error.h"

namespace sdds {
	Error::Error()
	{
		ErrorMsg = nullptr;
	}

	Error::Error(const char* emsg)
	{
		if (emsg != nullptr)
		{
			ErrorMsg = new char[strlen(emsg) + 1];
			strcpy(ErrorMsg, emsg);
		}
		else
		{
			ErrorMsg = nullptr;
		}
	}

	Error::Error(const Error& other)
	{
		if (other.ErrorMsg != nullptr)
		{
			ErrorMsg = new char[strlen(other.ErrorMsg) + 1];
			strcpy(ErrorMsg, other.ErrorMsg);
		}
		else
		{
			ErrorMsg = nullptr;
		}
	}

	Error& Error::operator=(const Error& other)
	{
		if (this != &other)
		{
			if (ErrorMsg != nullptr)
			{
				delete[] ErrorMsg;
			}

			if (other.ErrorMsg != nullptr)
			{
				ErrorMsg = new char[strlen(other.ErrorMsg) + 1];
				strcpy(ErrorMsg, other.ErrorMsg);
			}

			else
			{
				delete[] ErrorMsg;
				ErrorMsg = nullptr;
			}
		}
		return *this;
	}

	Error::operator bool() const
	{
		if (ErrorMsg != nullptr && ErrorMsg[0] != '\0')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Error& Error::clear()
	{
		if (ErrorMsg != nullptr)
		{
			delete[] ErrorMsg;
			ErrorMsg = nullptr;
		}
		return *this;
	}

	Error::~Error()
	{
		//if (ErrorMsg != nullptr)
		//{
			delete[] ErrorMsg;
			ErrorMsg = nullptr;
		//}
	}

	const char* Error::get() const
	{
		return ErrorMsg;
	}

	std::ostream& operator<<(std::ostream& os, const Error& err)
	{
		if (err.get() != nullptr)
		{
			os << err.get();
		}
		return os;
	}
}