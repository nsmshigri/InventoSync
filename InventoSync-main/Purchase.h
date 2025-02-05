#ifndef PURCHASE_H
#define PURCHASE_H

#include <string>
#include "Stock.h"
#include <iostream>
#include <fstream>
using namespace std;

class Purchase
{
private:
	Item* PurchaseItem;
	int purchaseSize;
	int currentSize;
	void resize();

public:
	Purchase();
	Purchase(const Purchase&);

	const Purchase& operator=(const Purchase&);
	
	Purchase(const Item*, int);
	
	int getPurchaseSize() const;
	int getCurrentSize() const;
	
	void setIndex(int);
	
	const Item* getPurchaseItemArray() const;
	
	~Purchase();

	void setItemPurshased(const Item*, int);
	
	void addPurshase(Stock&);
	bool updatePurchasedItem(string, Stock&);
	bool deletePurchasedItem(string, Stock&);
	int searchPurchasedItem(string name);
	
	void displayReceipt();

	//overload index operator
	Item& operator[](const int index) const;
	
	void printStock(Stock&);
	void pauseAndClear();

};

#endif 
