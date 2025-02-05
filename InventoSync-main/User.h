#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
private:
	string name;
	string userid;
	string contact;
public:

	User();
	void setUser(string, string, string);
	void print();
	string getName();
	string getPhone();
	string getUserid();
};

#endif 

