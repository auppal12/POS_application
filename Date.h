//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Error.h"

namespace sdds {
	class Date
	{
		int year, month, day, hour, minute;
		bool date_only;
		Error err;

		void validate();

	public:

		//void set(int y, int m, int d, int h, int min);

		Date();

		//Date(int y, int m, int d, int h);

		//Date(int y, int m, int d);


		Date(int y, int m, int d, int h = 0 , int min = 0);		//my friend, RAM GROVER helped me with this

		Date& dateOnly(bool flag);

		bool operator==(const Date& d) const;

		bool operator!=(const Date& d) const;

		bool operator<(const Date& d) const;

		bool operator>(const Date& d) const;

		bool operator<=(const Date& d) const;

		bool operator>=(const Date& d) const;

		operator bool() const;

		const Error& error() const;

		void display(std::ostream& ostr) const;

		void read(std::istream& istr);

	};
	std::ostream& operator<<(std::ostream& ostr, const Date& d);
	std::istream& operator>>(std::istream& istr, Date& right);

}
#endif