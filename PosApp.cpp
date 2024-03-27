//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 16th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "PosApp.h"
#include "Item.h"
#include "Bill.h"

using namespace std;

namespace sdds {
	//PosApp::PosApp(const char* NewName)
	//{
	//	//this->filename = new char[256];
	//	strcpy(filename, NewName);
	//}

	/*PosApp::~PosApp()
	{
		delete[] filename;
	}*/
	PosApp::PosApp(const char* NewName)
	{
		if (NewName != nullptr && NewName[0] != '\0')
		{
			strncpy(filename, NewName, 127);
			filename[127] = 0;
		}

		else
		{
			filename[0] = '\0';
		}
		nptr = 0;
		for (auto i = 0; i < MAX_NO_ITEMS; i++)
		{
			Iptr[i] = nullptr;
		}
	}

	void PosApp::action(const char* title)
	{
		cout << ">>>> ";
		cout.width(72);
		cout.fill('.');
		cout << left << title << endl;
		cout.fill(' ');
	}

	bool PosApp::menu()
	{
		bool flag = true;
		int input{};

		cout << "The Sene-Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add item" << endl;
		cout << "3- Remove item" << endl;
		cout << "4- Stock item" << endl;
		cout << "5- POS" << endl;
		cout << "0- exit program" << endl;
		cout << "> ";

		do
		{
			cin >> input;
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid Integer, try again: ";
					input = -1;
				}
				else if (input < 0 || input > 5)
				{
					cout << "[0<=value<=5], retry: > ";
				}
			}
		} while (input < 0 || input > 5);

		switch (input)
		{
		case 0:
			saveRecs();
			cout << "Goodbye!\n";
			flag = false;
			break;
		case 1:
			listItems(true);
			break;
		case 2:
			addItem();
			break;
		case 3:
			removeItem();
			break;
		case 4:
			stockItem();
			break;
		case 5:
			POS();
			break;
		};
		return flag;
	}

	void PosApp::addItem() {
		action("Adding Item to the store");
		//cout << "Running addItem()\n";
		cout << "Is the Item perishable? (Y)es/(N)o: ";
		char type;
		cin >> type;
		cin.ignore();

		Item* item = nullptr;
		if (type == 'N' || type == 'n') {
			item = new NonPerishable();
		}
		else if (type == 'Y' || type == 'y') {
			item = new Perishable();
		}
		else {
			cout << ", try again..." << endl;
			return;
		}

		if (item->read(cin)) {
			if (nptr < MAX_NO_ITEMS) {
				Iptr[nptr] = item;
				nptr++;
				cout << ">>>> DONE!..................................................................." << endl;
			}
			else {
				cout << "Inventory Full!" << endl;
			}
		}
		else {
			//cout << "cannot read data" << endl;
			delete item;
		}
	}

	void PosApp::removeItem() {
		//cout << ">>>> Remove Item............................................................." << endl;
		//cout << "Running removeItem()\n";
		action("Remove Item");
		int row = selectItem();
		cout << "Removing...." << endl;
		cout << Iptr[row - 1]->displayType(POS_FORM);

		delete Iptr[row - 1];

		for (auto i = row; i < nptr; i++) {
			Iptr[i - 1] = Iptr[i];
		}
		nptr--;
		cout << ">>>> DONE!..................................................................." << endl;
	}

	void PosApp::stockItem() {
		//cout << ">>>> Select an item to stock................................................." << endl;
		//cout << "Running stockItem()\n";
		action("Select an item to stock");
		int row = selectItem();
		cout << "Selected Item:\n";
		Item* item = Iptr[row - 1];
		cout << Iptr[row - 1]->displayType(POS_FORM);

		cout << "Enter quantity to add: ";

		int add{};
		do
		{
			while (!(cin >> add))
			{
				cout << "Invalid Integer, try again: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}

			if (add < 1 || add > (abs(Iptr[row - 1]->quantity() - MAX_STOCK_NUMBER)))
			{
				cout << "[1<=value<=" << (abs(Iptr[row - 1]->quantity() - MAX_STOCK_NUMBER)) << "], retry: Enter quantity to add: ";
			}

		} while (add < 1 || add > (abs(Iptr[row - 1]->quantity() - MAX_STOCK_NUMBER)));
		//Iptr[row-1]->quantity() += add; NOT SURE
		*item += add;		//took help from my friend Daniel

		cout << ">>>> DONE!..................................................................." << endl;

	}

	void PosApp::listItems(bool onOroff) {
		bool flag = onOroff;
		action("Listing Items");
		//cout << "Running listItems()\n";
		double total_asset{};
		sort();
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
		cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;

		for (auto i = 0; i < nptr; i++)
		{
			cout << right << setw(4) << i + 1 << " | ";
			Iptr[i]->displayType(POS_LIST);
			cout << *(Iptr[i]) << endl;

			total_asset += Iptr[i]->cost() * Iptr[i]->quantity();
		}

		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		if (flag == true)
		{
			cout << "                               Total Asset: $  |       " << total_asset << "| " << endl;
			cout << "-----------------------------------------------^--------------^" << endl << endl;
		}
	}

	void PosApp::POS() {
		//cout << ">>>> Starting Point of Sale.................................................." << endl;
		//cout << "Running POS()\n";
		action("Starting Point of Sale");
		char SKU[MAX_SKU_LEN]{};
		bool flag = true;
		double totalcost{};
		Bill B;
		Item* item;


		cin.ignore(1000, '\n');
		while (flag != false && !cin.fail())
		{
			cout << "Enter SKU or <ENTER> only to end sale..." << endl;
			cout << "> ";
			cin.getline(SKU, MAX_SKU_LEN, '\n');

			if (SKU[0] == '\0')
			{
				flag = false;
			}
			else
			{
				item = search(SKU);

				if (item == nullptr)
				{
					cout << "!!!!! Item Not Found !!!!!" << endl;
				}
				else
				{
					-- *item;

					if (*item)
					{
						totalcost += item->cost();
					}

					item->displayType(POS_FORM);
					item->write(cout) << endl;

					if (*item)
					{
						cout << ">>>>> Added to bill\n";
						cout << ">>>>> Total: " << fixed << setprecision(2) << totalcost << endl;
						B.add(item);
						B.total();
					}

					else
					{
						item->clear();
					}
				}
				
					/*if (Iptr[*item]->quantity() > 0)
					{
						Iptr[*item]->displayType(POS_FORM);
						Iptr[*item]->write(cout);

						double total{};
						total += Iptr[*item]->cost() * Iptr[*item]->quantity();
					}*/
			}
		}
		B.print(cout);
	}
	
	void PosApp::saveRecs() {
		cout << ">>>> Saving Data............................................................." << endl;
		//cout << "Saving data in " << filename << endl;
		ofstream os(filename);

		for (auto i = 0; i < nptr; i++)
		{
			os << *Iptr[i] << endl;
		}
		os.close();
	}

	void PosApp::loadRecs() {
		//cout << ">>>> Loading Items..........................................................." << endl;
		//cout << "Loading data from " << filename << endl;
		action("Loading Items");
		ifstream input(filename);
		if (input.fail())
		{
			ofstream output(filename);
			output.close();
		}

		Deallocate();
		nptr = 0;

		while (input.good() && nptr < MAX_NO_ITEMS)
		{
			char type{};
			input >> type;
			if (input.good())
			{
				Item* item = nullptr;
				if (type == 'N')
				{
					item = new NonPerishable();
				}

				else if (type == 'P')
				{
					item = new Perishable();
				}

				if (item != nullptr)
				{
					input.ignore();
					item->load(input);
					Iptr[nptr] = item;
					nptr++;
				}
			}
		}
	}

	void PosApp::Deallocate()
	{
		for (auto i = 0; i < nptr; i++)
		{
			delete Iptr[i];
			Iptr[i] = nullptr;
		}
	}

	PosApp::~PosApp()
	{
		Deallocate();
	}

	void PosApp::run()
	{
		loadRecs();
		bool choice = true;
		while (choice)
		{
			choice = menu();
		}
	}

	int PosApp::selectItem()
	{
		// cout << ">>>> Item Selection by row number............................................" << endl;
		action("Item Selection by row number");
		cout << "Press <ENTER> to start....";
		cin.get();
		cin.ignore(10000, '\n');
		listItems(false);
		cout << "Enter the row number: ";

		int row_num{};
		do
		{
			while (!(cin >> row_num))
			{
				cout << "Invalid Integer, try again: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}

			if (row_num < 1 || row_num > nptr)
			{
				cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
			}

		} while (row_num < 1 || row_num > nptr);

		return row_num;
	}

	Item* PosApp::search(const char* SKU)
	{
		//bool flag = true;

		for (int i = 0; i < nptr; i++)
		{
			if (*Iptr[i] == SKU)
			{
				return Iptr[i];
			}
			//else
			//	//return nullptr;
			//	flag == false;
		}
		return nullptr;

		/*if (flag == false)
		{
			return nullptr;
		}*/
	}

	void PosApp::sort()
	{
		Item* temp;
		for (auto i = 0; i < nptr - 1; i++)
		{
			for (auto j = i + 1; j < nptr; j++)
			{
				if (*Iptr[i] > *Iptr[j])
				{
					temp = Iptr[i];
					Iptr[i] = Iptr[j];
					Iptr[j] = temp;
				}
			}
		}
	}
}