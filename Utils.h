//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

namespace sdds {
	//this function retrieves the current date and time of the system and returns them through the argument list.
	void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);

	// this function assigns a unique integer value to a date-time value.
	int uniqueDateValue(int year, int mon, int day, int hour, int min);

	// this function finds out what is the maximum valid value for a calendar day in a month.
	int daysOfMonth(int year, int month);
}
#endif