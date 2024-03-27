//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#include <iostream>
#include <fstream>

namespace sdds
{
	class PosIO
	{
	public:
		virtual ~PosIO() {};
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual std::ofstream& save(std::ofstream& ofs) const = 0;
		virtual std::ifstream& load(std::ifstream& ifs) = 0;
	};
	std::ostream& operator<<(std::ostream& os, const PosIO& obj);

	std::ofstream& operator<<(std::ofstream& ofs, const PosIO& obj);

	std::istream& operator>>(std::istream& is, PosIO& obj);

	std::ifstream& operator>>(std::ifstream& ifs, PosIO& obj);
}
#endif