//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H

namespace sdds {
	class Error
	{
		char* ErrorMsg;

	public:
		Error();	// Default constructor

		Error(const char* emsg);		// Constructor with error message

		Error(const Error& other);		// copy constructor

		Error& operator=(const Error& other);	// Assignment operator

		operator bool() const;		// Boolean type conversion

		Error& clear();			// Clear method

		~Error();		// Destructor

		const char* get() const;	//return ErrorMsg

	};
	std::ostream& operator<<(std::ostream& os, const Error& err);	// Insertion operator for ostream
}
#endif