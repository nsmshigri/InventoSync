#ifndef STOCK_H
#define STOCK_H

#include <string>
#include "Item.h"
#include <iostream>
#include <fstream>

using namespace std;

class Stock
{

private:
	Item* items;
	int size;
	int capacity;
	void resize();

public:
	Stock(int capacity = 1);
	Stock(const Stock& stock);
	~Stock();

	const Item* getItems() const;
	Item getItem(int) const;
	int getSize() const;
	int getCapacity() const;

	void setItems(Item*);
	void setSize(int);
	void setCapacity(int);
	void setItem(Item, int);

	void saveStock();
	void loadStock();

	void addItem(Item);
	void removeItem(string);
	int updateItem(string);
	void updateItem(int, string);
	int searchItem(string);
	int searchItemName(string);
	void printStock();

	char getValidChoice();

	Stock operator=(const Stock& stock);

	//overload index operator
	Item& operator[](const int index) const;

};

#endif 
