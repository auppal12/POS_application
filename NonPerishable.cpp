#include <iostream>
#include "NonPerishable.h"

using namespace std;
namespace sdds {
	char NonPerishable::itemType() const
	{
		return 'N';
	}
	std::ostream& NonPerishable::write(std::ostream& ostr) const
	{
		Item::write(ostr);
		if (ostr.good())
		{
			switch (m_displayType)
			{
			case POS_LIST:
				ostr << "    N / A   |";
				break;
			case POS_FORM: {
				if (!m_errorState)
					ostr << "=============^" << endl;
				}
				break;
			}
		}
		return ostr;
	}
}