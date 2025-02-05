#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Stock.h"
#include "Item.h"
#include <string>

using namespace std;

class Admin :public User
{
private:
	string username;
	string password;
	Stock stock;

public:
	
	Admin();
	
	bool check();
	void changePassword();
	void displayAdminMenu();
	
	int getAdminChoice();

	void adminAccess();
	
	void pauseAndClear();

};

#endif 
