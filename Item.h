#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include <iostream>
#include <fstream>
#include "POS.h"
#include "PosIO.h"
#include "Error.h"

namespace sdds
{
	class Item : public PosIO
	{
		char m_sku[MAX_SKU_LEN]{};
		char* m_ItemName{};
		double m_price{};
		bool m_tax{};
		int m_quantity{};

	protected:
		int m_displayType{};
		Error m_errorState;

	public:
		Item();
		~Item();
		Item(const Item& cons);
		Item& operator=(const Item& assignment);
		bool operator==(const char* sku) const;
		bool operator>(const Item& other) const;
		int operator+=(int count);
		int operator-=(int count);
		int operator --();
		operator bool()const;

		virtual char itemType() const = 0;
		Item& displayType(int pos);
		double cost() const;
		int quantity() const;
		Item& clear();

		std::ostream& write(std::ostream& os) const override;
		std::istream& read(std::istream& is) override;
		std::ofstream& save(std::ofstream& ofs) const override;
		std::ifstream& load(std::ifstream& ifs) override;
		std::ostream& bprint(std::ostream& os) const;
	};
	double operator+=(double& cost, const Item& item);
}
#endif