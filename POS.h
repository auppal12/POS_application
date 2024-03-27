//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 13th April, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef POS_H
#define POS_H

const double TAX = 0.13;
const int MAX_SKU_LEN = 7;

const int MIN_HOUR = 0;
const int MAX_HOUR = 23;

const int MIN_MIN = 0;
const int MAX_MIN = 59;

const int MIN_DAY = 1;

const int MIN_MONTH = 1;
const int MAX_MON = 12;

const int MIN_YEAR = 2000;
const int MAX_YEAR = 2030;

const int MAX_STOCK_NUMBER = 99;
const int MAX_NO_ITEMS = 200;


const int MAX_NAME_LEN = 40;

const int POS_LIST = 1;
const int POS_FORM = 2;

const char ERROR_POS_SKU[13] = "SKU too long";
const char ERROR_POS_NAME[19] = "Item name too long";
const char ERROR_POS_PRICE[20] = "Invalid price value";
const char ERROR_POS_TAX[19] = "Invalid tax status";
const char ERROR_POS_QTY[23] = "Invalid quantity value";
const char ERROR_POS_STOCK[18] = "Item out of stock";
const char ERROR_POS_EMPTY[19] = "Invalid Empty Item";

#endif // !POS_H