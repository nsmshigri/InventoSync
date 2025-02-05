#include <string>
#include <iostream>
#include "Item.h"

using namespace std;

Item::Item()
{
	itemName = "";
	itemCode = "";
	quantity = 0;
	price = 0;
	totalPrice = 0;
}

Item::Item(string itemName, string itemCode, int quantity, double price)
{
	this->itemName = itemName;
	this->itemCode = itemCode;
	this->quantity = quantity;
	this->price = price;
	this->totalPrice = quantity * price;
}

void Item::setItemName(string itemName)
{
	this->itemName = itemName;
}

void Item::setItemCode(string itemCode)
{
	this->itemCode = itemCode;
}

void Item::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Item::setPrice(double price)
{
	this->price = price;
}

void Item::setTotalPrice()
{
	this->totalPrice = quantity * price;
}

string Item::getItemName() const
{
	return itemName;
}

string Item::getItemCode() const
{
	return itemCode;
}

int Item::getQuantity() const
{
	return quantity;
}

long double Item::getPrice() const
{
	return price;
}

long double Item::getTotalPrice() const
{
	return totalPrice;
}