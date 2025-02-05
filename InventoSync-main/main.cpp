#include <iostream>
#include <string>
#include "Stock.h"
#include "Item.h"
#include <fstream>
#include "User.h"
#include "Admin.h"
#include "Employee.h"
#include "Customer.h"

using namespace std;

void displayIntro();
void displayExit();
void displayMainMenu();

int getChoice();
int whoIsUser();

int main()
{
    Stock stock;
    displayIntro();

    int choice;
    string username, password;

    do
    {
        choice = whoIsUser();

        switch (choice)
        {
        case 1:
        {
            Admin admin;
            cout << "User Name: ";
            cin.ignore();
            getline(cin, username);

            if (admin.check())
            {
                cout << "LOGIN SUCCESSFUL\n";
                admin.pauseAndClear();
                admin.adminAccess();
            }
            else
            {
                system("cls");
                cout << "YOU HAVE ENTERED WRONG PASSWORD\n";
                admin.pauseAndClear();
            }
            break;
        }

        case 2:
        {
            Employee employee;
            cout << "User Name: ";
            cin.ignore();
            getline(cin, username);

            if (employee.check())
            {
                cout << "LOGIN SUCCESSFUL\n";
                employee.pauseAndClear();
                employee.employeeAccess();
            }
            else
            {
                system("cls");
                cout << "YOU HAVE ENTERED THE WRONG PASSWORD\n";
                employee.pauseAndClear();
            }
            break;
        }

        case 3:
        {
            Customer customer;
            customer.customerAccess();

            break;
        }

        case 4:
        {
            displayExit();
            system("pause");
            break;
        }

        default:

            cout << "Invalid choice" << '\n';
            break;
        }

    } while (choice != 4);


    return 0;
}

void displayMainMenu()
{
    cout << "INVENTOSYNC\n";
    cout << "1 - LOGIN AS ADMIN\n";
    cout << "2 - LOGIN AS EMPLOYEE\n";
    cout << "3 - ENTER TO PURCHASE AS CUSTOMER\n";
    cout << "4 - EXIT (ALL CHANGES WILL BE SAVED)\n";
}

int getChoice()
{
    int choice = -1;

    while (!(choice > 0 && choice < 5))
    {
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");

        if (!(choice > 0 && choice < 5))
        {
            cout << "Please choose a valid number from the following options of menu.\n";
            displayMainMenu();
        }

        cin.clear();
        cin.ignore(1000, '\n');
    }

    return choice;
}

int whoIsUser()
{
    displayMainMenu();
    return getChoice();
}

void displayIntro()
{
    cout << "WELCOME TO INVENTOSYNC\n";
    system("pause");
    system("cls");
}

void displayExit()
{
    cout << "THANK YOU FOR USING THE INVENTOSYNC\n";
    system("pause");
    system("cls");
}
