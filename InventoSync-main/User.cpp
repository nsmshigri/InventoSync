#include <string>
#include <iostream>
#include "User.h"

using namespace std;

User::User()
{
	name = " ";
	userid = " ";
	contact = " ";
}

void User::setUser(string n, string id, string p)
{
	name = n;
	userid = id;
	contact = p;
}

void User::print()
{
	cout << "Name : " << name << '\n';
	cout << "User Id : " << userid << '\n';
	cout << "Phone Number : " << contact << '\n';
}

string User::getName()
{
	return name;
}

string User::getPhone()
{
	return contact;
}

string User::getUserid()
{
	return userid;
}

