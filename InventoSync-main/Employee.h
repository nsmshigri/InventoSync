#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"
#include "Stock.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Employee :public User
{
private:
	string password;
	Stock object;
public:
	Employee();
	bool check();

	void changePasswordEmployee();
	void displayEmployeeMenu();
	int getEmployeeChoice();
	void employeeAccess();
	void pauseAndClear();

};


#endif 
