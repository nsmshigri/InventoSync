#include <string>
//#include "Item.h"
#include "Stock.h"
#include <iostream>
#include <fstream>

using namespace std;


Stock::Stock(int capacity)
{
	items = new Item[capacity];
	size = 0;
	
	this->capacity = capacity;

}

Stock::Stock(const Stock& stock)
{
	this->items = new Item[stock.capacity];
	this->size = stock.size;
	this->capacity = stock.capacity;

	for (int i = 0; i < capacity; i++)
	{
		if (i != capacity - 1)
		{
			this->items[i] = stock.items[i];
		}
	}
}

void Stock::resize()
{
	capacity = capacity + 1;

	Item* temp = new Item[capacity];

	for (int i = 0; i < capacity; i++)
	{
		if (i != capacity - 1)
		{
			temp[i] = items[i];
		}
		else
		{
			temp[i] = Item();
		}
	}

	delete[] items;
	items = temp;
}

Stock::~Stock()
{
	if (items != nullptr)
	{
		delete[] items;
		items = nullptr;
	}
}

const Item* Stock::getItems() const
{
	return items;
}

Item Stock::getItem(int index) const
{
	return items[index];
}

Item& Stock::operator[](const int index) const
{
	return items[index];
}

int Stock::getSize() const
{
	return size;
}

int Stock::getCapacity() const
{
	return capacity;
}

void Stock::setItem(Item item, int index)
{
	items[index] = item;
}

void Stock::setItems(Item* items)
{
	this->items = items;
}

void Stock::setSize(int size)
{
	this->size = size;
}

void Stock::setCapacity(int capacity)
{
	this->capacity = capacity;
}

Stock Stock::operator=(const Stock& rhs)
{
	if (this != &rhs)
	{
		//delete previous memory if any allocated
		if (items != nullptr)
		{
			delete[] items;
			items = nullptr;
		}

		this->items = new Item[rhs.capacity];
		this->size = rhs.size;
		this->capacity = rhs.capacity;

		for (int i = 0; i < capacity; i++)
		{
			if (i != capacity - 1)
			{
				this->items[i] = rhs.items[i];
			}
		}
	}

	return *this;
}

void Stock::saveStock()
{
	ofstream fout;
	fout.open("stock.txt");

	for (int i = 0; i < size; i++)
	{
		fout << "____________________________________________________\n";
		fout << "                   ITEM #" << i + 1 << endl;
		fout << "____________________________________________________\n";
		fout << "NAME: " << items[i].getItemName() << "\n";
		fout << "CODE: " << items[i].getItemCode() << "\n";
		fout << "QUANTITY: " << items[i].getQuantity() << "\n";
		fout << "PRICE: " << items[i].getPrice() << "\n";
	}
	fout.close();
}

// fnction to load data from file
void Stock::loadStock()
{
	ifstream fin;
	fin.open("stock.txt");
	if (fin.is_open())
	{
		string line, line1, line2, line3, line4, line5, line6, line7, name, code;
		while (getline(fin, line))
		{
			getline(fin, line1);
			getline(fin, line2);
			getline(fin, line3);
			
			name = line3.substr(6, line3.length() - 1);
			getline(fin, line4);
			
			code = line4.substr(6, line4.length() - 1);
			getline(fin, line5);
			
			int quantity = stoi(line5.substr(10, line5.length() - 1));
			getline(fin, line6);
			
			long double price = stold(line6.substr(7, line6.length() - 1));

			Item item(name, code, quantity, price);
			addItem(item);
		}
	}

	else
	{
		cout << "\n\n\tTHERE ARE NO RECORDS ON THE DATABASE!!!\n\n";
	}

	fin.close();
}

void Stock::addItem(Item item)
{
	if (size >= capacity)
	{
		resize();
	}

	//check if iteam already present in stock then don't add it
	for (int i = 0; i < size; i++)
	{
		if (items[i].getItemCode() == item.getItemCode() || items[i].getItemName() == item.getItemName())
		{
			cout << "\n\n\tITEM ALREADY PRESENT IN STOCK!!!\n\n";

			return;
		}
	}

	items[size] = item;
	//setItem(item, size);
	size++;
}

void Stock::removeItem(string itemCode)
{
	int index = -1;
	for (int i = 0; i < size; ++i)
	{
		if (items[i].getItemCode() == itemCode)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		cout << "Item not found. Please enter a valid item code: ";
		
		getline(cin, itemCode);
		removeItem(itemCode); // Recursively call to retry removing the item
	}
	else
	{
		for (int i = index; i < size - 1; ++i)
		{
			items[i] = items[i + 1];
		}

		size = size - 1;
	}
}

int Stock::updateItem(string itemCode)
{
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (items[i].getItemCode() == itemCode)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return index;
	}

	// Update quantity of the item
	cout << "Do you want to update the quantity of the item? (y/n): ";
	char choice;
	cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		int quantity;
		cout << "Enter the quantity: ";
		
		while (!(cin >> quantity) || quantity < 0)
		{
			cout << "Invalid input. Please enter a valid quantity: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		
		cout << "Do you want to add or remove quantity? (1. Add, 2. Remove): ";
		int choice1;
		while (!(cin >> choice1) || (choice1 != 1 && choice1 != 2))
		{
			cout << "Invalid input. Please enter a valid choice (1/2): ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		if (choice1 == 1)
		{
			items[index].setQuantity(items[index].getQuantity() + quantity);
			cout << "Quantity added successfully." << endl;
		}
		else
		{
			if (items[index].getQuantity() >= quantity)
			{
				items[index].setQuantity(items[index].getQuantity() - quantity);
				cout << "Quantity removed successfully." << endl;
			}
			else
			{
				cout << "Not enough quantity in stock." << endl;
			}
		}
	}

	// Update price of the item
	cout << "Do you want to update the price of the item? (y/n): ";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		long double cost;
		cout << "Enter the new price: ";
		while (!(cin >> cost) || cost < 0)
		{
			cout << "Invalid input. Please enter a valid price: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		
		items[index].setPrice(cost);
		items[index].setTotalPrice();
		
		cout << "Price updated successfully." << endl;
	}

	cin.clear();
	cin.ignore(1000, '\n');
	return index;
}



void Stock::updateItem(int quantity, string itemName)
{
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (items[i].getItemName() == itemName)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		items[index].setQuantity(items[index].getQuantity() - quantity);
		items[index].setTotalPrice();
	}

}


int Stock::searchItem(string itemCode)
{
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (items[i].getItemCode() == itemCode)
		{
			index = i;
			break;
		}
	}
	return index;
}

int Stock::searchItemName(string itemName)
{
	int index = -1;
	int flag = 1;
	for (int i = 0; i < size && flag; i++)
	{
		if (items[i].getItemName() == itemName)
		{
			index = i;
			flag = 0;
		}
	}
	if (flag)
	{
		index = -1;
	}
	return index;
}


void Stock::printStock()
{
	if (size == 0)
	{
		cout << "STOCK IS EMPTY!!" << endl;
	}
	else
	{
		cout << "ITEM # \tITEM NAME \tITEM CODE \tQUANTITY \tPRICE Rs." << endl;
		
		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << "\t" << items[i].getItemName() << "\t\t" << items[i].getItemCode() << "\t\t" << items[i].getQuantity() << "\t\t" << items[i].getPrice() << endl;
		}
	}
}

char Stock::getValidChoice()
{
	char choice;
	cin >> choice;
	
	while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
	{
		cout << "Invalid input. Please enter a valid choice (y/n): ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}

	return choice;
}
