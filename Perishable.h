//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"

namespace sdds
{
	class Perishable : public Item
	{
	public:
		Date date{};
		virtual char itemType() const override;
		
		std::ostream& write(std::ostream& os) const override;
		std::istream& read(std::istream& is) override;
		std::ofstream& save(std::ofstream& ofs) const override;
		std::ifstream& load(std::ifstream& ifs) override;
	};
}
#endif