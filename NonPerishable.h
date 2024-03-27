//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H
#include "Item.h"

namespace sdds
{
	class NonPerishable : public Item
	{
		virtual char itemType() const override;
		std::ostream& write(std::ostream& ostr) const override;
	};
}
#endif