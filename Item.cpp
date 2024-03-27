#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Item.h"

using namespace std;

namespace sdds
{
	Item::Item()
	{
		//done{}
	}

	Item::Item(const Item& cons)
	{
		*this = cons;
	}

	Item::~Item()
	{
		//if (m_ItemName != nullptr)
		//{
		delete[] m_ItemName;
		m_ItemName = nullptr;
		//}
	}

	Item& Item::operator=(const Item& assignment)
	{
		if (this != &assignment)
		{
			strncpy(m_sku, assignment.m_sku, MAX_SKU_LEN);

			delete[] m_ItemName;
			m_ItemName = nullptr;

			if (assignment.m_ItemName != nullptr)
			{
				m_ItemName = new char[strlen(assignment.m_ItemName) + 1];
				strcpy(m_ItemName, assignment.m_ItemName);
			}

			m_price = assignment.m_price;
			m_tax = assignment.m_tax;
			m_quantity = assignment.m_quantity;
			m_displayType = assignment.m_displayType;
			m_errorState = assignment.m_errorState;
		}
		return *this;
	}

	bool Item::operator==(const char* sku) const
	{
		if (strcmp(m_sku, sku) == 0)
		{
			return true;
		}
		else
			return false;
	}

	bool Item::operator>(const Item& other) const
	{
		if (strcmp(m_ItemName, other.m_ItemName) > 0)
		{
			return true;
		}
		else
			return false;
	}

	int Item::operator+=(int count)
	{
		m_quantity = m_quantity + count;
		return m_quantity;

		if ((m_quantity + count) > MAX_STOCK_NUMBER)
		{
			m_quantity = MAX_STOCK_NUMBER;
			m_errorState = Error(ERROR_POS_QTY);
		}
	}

	int Item::operator-=(int count)
	{
		m_quantity = m_quantity - count;
		return m_quantity;

		if ((m_quantity - count) > m_quantity)
		{
			m_quantity = 0;
			m_errorState = Error(ERROR_POS_STOCK);
		}
	}

	Item::operator bool() const
	{
		if (m_errorState == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Item& Item::displayType(int pos)
	{
		if (pos == POS_LIST || pos == POS_FORM)
		{
			m_displayType = pos;
		}
		return *this;
	}

	double Item::cost() const
	{
		double total = m_price;
		if (m_tax)
		{
			total = total + (total * TAX);
		}
		return total;
	}

	int Item::quantity() const
	{
		return m_quantity;
	}

	Item& Item::clear()
	{
		m_errorState.clear();
		return *this;
	}

	std::ostream& Item::write(std::ostream& os) const
	{
		if (m_errorState)
		{
			os << m_errorState;
		}
		else
			switch (m_displayType)
			{
			case POS_LIST:
				os << setw(7) << left << m_sku << "|";
				if (strlen(m_ItemName) > 20)
					os.write(m_ItemName, 20);
				else
					os << setw(20) << m_ItemName;
				os << "|" << setw(7) << right << fixed
					<< setprecision(2) << m_price << "|"
					<< setw(3);
				if (m_tax)
					os << " X |";
				else
					os << "   |";
				os
					<< setw(4) << right << m_quantity << "|"
					<< setw(9) << fixed << setprecision(2)
					<< cost() * m_quantity << "| ";
				break;
			case POS_FORM:
				os << "=============v" << endl
					<< setw(13) << left << "Name:" << m_ItemName << endl
					<< setw(13) << left << "Sku:" << m_sku << endl
					<< setw(13) << left << "Price:" << m_price << endl
					<< setw(13) << left << fixed << setprecision(2) << "Price + tax:";
				if (m_tax)
					os << cost();
				else
					os << "N/A";
				os << endl << setw(13) << left << "Stock Qty:"
					<< m_quantity << endl;
				break;
			}
		os << std::left;	//My friend Daniel helped me with this
		return os;
	}

	std::ofstream& Item::save(std::ofstream& ofs) const
	{
		if (m_errorState)
		{
			cerr << m_errorState << endl;
		}
		else {
			ofs << itemType() << "," << m_sku << "," << m_ItemName << "," << fixed << setprecision(2) << m_price << "," << (int)m_tax << "," << m_quantity;
		}
		return ofs;
	}

	std::istream& Item::read(std::istream& is)
	{
		bool valid = true;
		char sku[MAX_SKU_LEN * 3]{};
		char name[MAX_NAME_LEN * 3]{};
		double cost{};
		char taxed[10]{};
		int count = 0;

		cout << "Sku" << endl;
		while (valid)
		{
			cout << "> ";
			is >> sku;
			if (strlen(sku) > MAX_SKU_LEN)
			{
				cout << ERROR_POS_SKU << endl;
			}
			else
			{
				valid = false;
				strcpy(m_sku, sku);
			}
			is.clear();
			is.ignore(99, '\n');
		}

		cout << "Name" << endl;
		valid = true;
		while (valid)
		{
			cout << "> ";
			is.get(name, MAX_NAME_LEN * 3, '\n');
			if (strlen(name) > MAX_NAME_LEN)
			{
				cout << ERROR_POS_NAME << endl;
			}
			else
			{
				valid = false;
				delete[] m_ItemName;
				m_ItemName = new char[strlen(name) + 1];
				strcpy(m_ItemName, name);
			}
			is.clear();
			is.ignore(99, '\n');
		}

		cout << "Price" << endl;
		valid = true;
		while (valid)
		{
			cout << "> ";
			if (is >> cost && cost >= 0.00)
			{
				valid = false;
			}
			else
			{
				valid = true;
				cout << ERROR_POS_PRICE << endl;
			}
			if (!valid)
			{
				m_price = cost;
			}
			/*else
			{
				cost{};
			}*/
			is.clear();
			is.ignore(99, '\n');
		}

		cout << "Taxed?" << endl;
		cout << "(Y)es/(N)o: ";
		valid = true;
		while (valid)
		{
			is >> taxed;
			if (!strcmp(taxed, "y") || !strcmp(taxed, "n"))
			{
				valid = false;
			}
			else
			{
				valid = true;
			}

			if (!valid && !strcmp(taxed, "y"))
			{
				m_tax = true;
			}

			if (valid)
			{
				cout << "Only 'y' and 'n' are acceptable: ";
			}
			is.clear();
			is.ignore(99, '\n');
		}

		cout << "Quantity" << endl;
		valid = true;
		while (valid)
		{
			cout << "> ";
			if (is >> count && count > 0 && count < MAX_STOCK_NUMBER)
			{
				m_quantity = count;
				valid = false;
			}
			else
			{
				valid = true;
				cout << ERROR_POS_QTY << endl;
			}
			is.clear();
			is.ignore(99, '\n');
		}
		return is;
	}

	std::ifstream& Item::load(std::ifstream& ifs)
	{
		char SKU[15]{};
		char Name[100]{};
		double cost{};
		int Taxed{}, count{};
		clear();

		ifs.getline(SKU, MAX_SKU_LEN * 2, ',');
		ifs.getline(Name, MAX_NAME_LEN * 2, ',');
		ifs >> cost;
		ifs.ignore();
		ifs >> Taxed;
		ifs.ignore();
		ifs >> count;

		if (!ifs.fail()) {
			if (strlen(SKU) > MAX_SKU_LEN)
			{
				m_errorState = ERROR_POS_SKU;
			}
			else if (strlen(Name) > MAX_NAME_LEN)
			{
				m_errorState = ERROR_POS_NAME;
			}
			else if (cost < 0.00)
			{
				m_errorState = ERROR_POS_PRICE;
			}
			else if (Taxed != 0 && Taxed != 1)
			{
				m_errorState = ERROR_POS_TAX;
			}
			else if (count < 0 || count > MAX_STOCK_NUMBER)
			{
				m_errorState = ERROR_POS_QTY;
			}
		}

		if (!m_errorState)
		{
			strcpy(m_sku, SKU);

			delete[] m_ItemName;
			//	m_ItemName = nullptr;
			m_ItemName = new char[strlen(Name) + 1];
			strcpy(m_ItemName, Name);

			m_price = cost;
			m_tax = Taxed;
			m_quantity = count;
		}
		return ifs;
	}

	std::ostream& Item::bprint(std::ostream& os) const
	{
		os << "| " << left;
		if ((strlen(m_ItemName) > 20))
		{
			os.write(m_ItemName, 20);
		}
		else
			os << setw(20) << m_ItemName;
		os << "|" << setw(10) << right << fixed << setprecision(2)
			<< cost() << " |" << "  " << (m_tax ? "T" : " ") << "  |" << endl;
		return os;
	}

	double operator+=(double& cost, const Item& item)
	{
		cost += item.cost() * item.quantity();
		return cost;
	}

	int Item::operator--()
	{
		int update = m_quantity - 1;

		if (update < 0)
		{
			m_errorState = Error("Item out of stock");
			update = 0;
		}

		m_quantity = update;
		return m_quantity;
	}
}