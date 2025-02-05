#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "User.h"
#include "Stock.h"
#include "Purchase.h"

using namespace std;

class Customer : public User
{
private:
	string address;
	string email;
	string CNIC;
	Stock obj;
	Purchase purchaseItem;

public:

	Customer();
	void setCustomer(string, string, string, string, string, string);

	void print();

	string getAddress();
	string getEmail();
	string getCNIC();

	void displayCustomerMenu();

	int getCustomerChoice();



	void saveReceipt();
	void customerAccess();
	void pauseAndClear();
};


#endif 
