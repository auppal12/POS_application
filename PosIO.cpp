//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <fstream>
#include "PosIO.h"

namespace sdds
{
	std::ostream& operator<<(std::ostream& os, const PosIO& obj)
	{
		return obj.write(os);
	}
	std::ofstream& operator<<(std::ofstream& ofs, const PosIO& obj)
	{
		return obj.save(ofs);
	}
	std::istream& operator>>(std::istream& is, PosIO& obj)
	{
		return obj.read(is);
	}
	std::ifstream& operator>>(std::ifstream& ifs, PosIO& obj)
	{
		return obj.load(ifs);
	}
}