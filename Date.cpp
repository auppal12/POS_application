//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 16th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "POS.h"
#include "Error.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
	Date::Date()
	{
		getSystemDate(year, month, day, hour, minute, false);
		date_only = false;
		validate();
	}

	/*Date::Date(int year, int month, int day)
	{
		year = year;
		month = month;
		day = day;
		hour = 0;
		minute = 0;
		date_only = true;
		validate();
	}*/

	/*Date::Date(int y, int m, int d, int h, int min)
	{
		if (!h && !min)
		{
			date_only = true;
		}
		else
		{
			date_only = false;
			year = y;
			month = m;
			day = d;
			hour = h;
			minute = min;
			validate();
		}
		validate();
	}*/
	Date::Date(int y, int m, int d, int h, int min)
	{
		if (!h && !min)
		{
			date_only = true;
		}
		else
			date_only = false;
			year = y;
			month = m;
			day = d;
			hour = h;
			minute = min;
		validate();
	}

	void Date::validate()
	{
		if (year < MIN_YEAR || year > MAX_YEAR)
		{
			err = Error("Invalid Year");
		}
		else if (month < MIN_MONTH || month > MAX_MON)
		{
			err = Error("Invalid Month");
		}
		else if (day < MIN_DAY || day > daysOfMonth(year, month))
		{
			err = Error("Invalid Day");
		}
		else if (hour < MIN_HOUR || hour > MAX_HOUR)
		{
			err = Error("Invalid Hour");
		}
		else if (minute < MIN_MIN || minute > MAX_MIN)
		{
			err = Error("Invlid Minute");
		}
		else
		{
			err = Error("");
		}
	}

	Date& Date::dateOnly(bool flag)
	{
		date_only = flag;
		if (flag)
		{
			hour = 0;
			minute = 0;
		}
		return *this;
	}

	bool Date::operator==(const Date& d) const
	{
		if (uniqueDateValue(year, month, day, hour, minute) != uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Date::operator!=(const Date& d) const
	{
		if (uniqueDateValue(year, month, day, hour, minute) != uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator<(const Date& d) const
	{
		if (uniqueDateValue(year, month, day, hour, minute) < uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator>(const Date& d) const
	{
		if (uniqueDateValue(year, month, day, hour, minute) > uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator<=(const Date& d) const
	{
		if (uniqueDateValue(year, month, day, hour, minute) <= uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator>=(const Date& d) const
	{
		if (uniqueDateValue(year, month, day, hour, minute) >= uniqueDateValue(d.year, d.month, d.day, d.hour, d.minute))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Date::operator bool() const
	{
		return !err;
	}

	const Error& Date::error() const
	{
		return err;
	}

	void Date::display(std::ostream& ostr) const
	{
		if (!(*this))
		{
			ostr << err.get() << "(" << year << "/" << setfill('0') << setw(2) << month << "/" << setfill('0') << setw(2) << day;
			if (!date_only)
			{
				ostr << ", " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
			}
			ostr << ")";
		}
		else
		{
			ostr << std::right;		//My friend Daniel helped me with this
			ostr << year << "/" << setfill('0') << setw(2) << month << "/" << setfill('0') << setw(2) << day;
			if (!date_only)
			{
				ostr << err.get() << ", " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute;
			}
		}
		ostr << left;	//My friend Daniel helped me with this
		ostr << setfill(' ');
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& d)
	{
		d.display(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Date& right)
	{
		right.read(istr);
		return istr;
	}

	void Date::read(std::istream& istr)
	{
		err.clear();
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		bool valid = true;
		istr >> year;
		if (istr.fail())
		{
			err = Error("Cannot read year entry");
			valid = false;
		}
		if (valid)
		{
			istr.ignore();
			istr >> month;
			if (istr.fail())
			{
				err = Error("Cannot read month entry");
				valid = false;
			}
		}
		if (valid)
		{
			istr.ignore();
			istr >> day;
			if (istr.fail())
			{
				err = Error("Cannot read day entry");
				valid = false;
			}
		}
		if (!date_only)
		{
			if (valid)
			{
				istr.ignore();
				istr >> hour;
				if (istr.fail())
				{
					err = Error("Cannot read hour entry");
					valid = false;
				}
			}
			if (valid)
			{
				istr.ignore();
				istr >> minute;
				if (istr.fail())
				{
					err = Error("Cannot read minute entry");
					valid = false;
				}
			}
		}
		if (!err)
		{
			validate();
		}
	}
}