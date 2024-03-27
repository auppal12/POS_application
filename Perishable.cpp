//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include "Perishable.h"

using namespace std;

namespace sdds 
{
	char Perishable::itemType() const
	{
		return 'P';
	}

	std::ostream& Perishable::write(std::ostream& os) const
	{
		Item::write(os);
		if (os.good())
		{
			switch (m_displayType)
			{
			case POS_LIST:
				os << " " << date << " |";
				break;
			case POS_FORM: {
				if(!m_errorState)
					os << "Expiry date: " << date << endl << "=============^" << endl;
				}
				break;
			}
		}
		return os;
	}

	std::ofstream& Perishable::save(std::ofstream& ofs) const
	{
		Item::save(ofs);
		if (ofs.is_open() && ofs.good())
		{
			ofs << "," << date;
		}
		return ofs;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		Item::read(is);

		if (is.good())
		{
			Date D;
			D.dateOnly(true);
			cout << "Expiry date (YYYY/MM/DD)" << endl << "> ";
			is >> D;

			if (is.good())
			{
				date = D;
			}
			else
			{
				Error(ERROR_POS_EMPTY);
			}
		}
		return is;
	}

	std::ifstream& Perishable::load(std::ifstream& ifs)
	{
		Item::load(ifs);
		if (ifs.is_open())
		{
			Date D;
			D.dateOnly(date);

			ifs.ignore(99, ',');
			ifs >> D;

			if (ifs.good())
			{
				date = D;
			}
			else
			{
				Error(ERROR_POS_EMPTY);
			}
		}
		return ifs;
	}
}
