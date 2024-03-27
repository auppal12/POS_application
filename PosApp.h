#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include<iostream>
#include"POS.h"
#include"Item.h"
#include"NonPerishable.h"
#include"Perishable.h"

namespace sdds
{
    class PosApp
    {
        char filename[128]{};

        Item* Iptr[MAX_NO_ITEMS];
        int nptr{};
        void action(const char* title);
        void sort();

        PosApp(const PosApp&) = delete;
        const PosApp& operator=(const PosApp&) = delete;

    public:
        PosApp(const char* NewName);

        ~PosApp();

        void Deallocate();

        bool menu();

        void addItem();

        void removeItem();

        void stockItem();

        void listItems(bool onOroff);

        void POS();

        void saveRecs();

        void loadRecs();

        void run();

        int selectItem();

        Item* search(const char* SKU);
    };
}

#endif