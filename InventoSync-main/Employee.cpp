#include <iostream>
#include <string>
#include <fstream>
#include "Employee.h"

using namespace std;

void Employee::pauseAndClear()
{
    cout << "\n\n";
    system("pause");
    system("cls");
}

Employee::Employee()
{
    password = "";
}

bool Employee::check()
{
    int count = 3;
    bool status = true;
    string password, line;
    ifstream fin("password.txt");

    if (fin)
    {
        getline(fin, line); // Skip the admin password line
        getline(fin, line); // Read employee password
        password = line;
    }
    fin.close();

    while (count != 0 && status)
    {
        cout << "\nEnter password: ";
        char ch;
        ch = getchar();

        for (int i = 0; i < password.length(); i++)
        {
            password[i] = ch;
            cout << '*';
            ch = getchar();

            while (ch == '\b')
            {
                --i;
                cout << "\b \b";
                ch = getchar();
            }

            if (ch == 27)
            {
                status = false;
            }
        }

        if (password == line)
        {
            return true;
        }
        else
        {
            system("cls");
            cout << "\n\nWrong password!!" << endl;
            cout << "\nYou have " << count - 1 << " attempts left." << endl;
        }
        count--;
    }

    return false;
}

void Employee::changePasswordEmployee()
{
    ifstream fin("password.txt");
    string line, adminPassword;

    if (fin)
    {
        getline(fin, line); // Skip the admin password line
        getline(fin, adminPassword); // Read employee password
    }
    fin.close();

    string password, confirm;

    cout << "\n\nEnter new password: ";
    getline(cin, password);

    cout << "\nConfirm Password: ";
    getline(cin, confirm);

    while (password != confirm)
    {
        system("cls");
        cout << "\nPasswords do not match. Please try again!" << endl;
        cout << "\nEnter new password: ";
        getline(cin, password);
        cout << "\nConfirm Password: ";
        getline(cin, confirm);
    }

    ofstream fout("password.txt");

    if (fout)
    {
        fout << line << "\n";
        fout << password;
        cout << "\nPassword changed successfully!!" << endl;
    }
    else
    {
        cout << "\nFile not found!!" << endl;
    }
    fout.close();
}

void Employee::displayEmployeeMenu()
{
    cout << "\nINVENTOSYNC\n";
    cout << "EMPLOYEE MENU\n";

    cout << "\n1 - UPDATE ITEM(s) IN STOCK";
    cout << "\n2 - DISPLAY ITEMS CURRENTLY IN STOCK";
    cout << "\n3 - SEARCH ITEM(s) FROM STOCK";
    cout << "\n4 - CHANGE PASSWORD";
    cout << "\n5 - EXIT & RETURN TO MAIN MENU (ALL CHANGES WILL BE SAVED)\n";
}

int Employee::getEmployeeChoice()
{
    int choice = -1;

    while (!((choice > 0) && (choice < 6)))
    {
        cout << "\nEnter your choice: ";
        cin >> choice;
        system("cls");

        if (!((choice > 0) && (choice < 6)))
        {
            cout << "\nPlease choose a valid number from the menu.\n";
            displayEmployeeMenu();
        }

        cin.clear();
        cin.ignore(1000, '\n');
    }

    return choice;
}

void Employee::employeeAccess()
{
    object.loadStock();
    int employeeChoice;

    do
    {
        displayEmployeeMenu();
        employeeChoice = getEmployeeChoice();

        switch (employeeChoice)
        {
        case 1:
        {
            if (object.getSize() == 0)
            {
                cout << "\nSTOCK IS EMPTY!!" << endl;
            }
            else
            {
                string itemCode;
                int index;
                char choice = 'y';

                while (choice == 'y' || choice == 'Y')
                {
                    object.printStock();
                    pauseAndClear();
                    cout << "\nEnter item code: ";
                    getline(cin, itemCode);

                    index = object.updateItem(itemCode);

                    if (index == -1)
                    {
                        cout << "\nItem not found!!" << endl;
                        cout << "\nKindly inform the Admin that the item is not in the stock" << endl;
                        cout << "and also ask the Admin to add the item to the stock with this code." << endl;
                    }

                    pauseAndClear();
                    cout << "\nDo you want to update another item from stock? (press y for yes and any other key for no): ";
                    cin >> choice;
                    cin.ignore(1000, '\n');
                }

                pauseAndClear();
            }

            break;
        }

        case 2:
        {
            object.printStock();
            pauseAndClear();
            break;
        }

        case 3:
        {
            if (object.getSize() == 0)
            {
                cout << "\nSTOCK IS EMPTY!!" << endl;
            }
            else
            {
                char choice = 'y';

                while (choice == 'y' || choice == 'Y')
                {
                    string itemCode;
                    int index;
                    cout << "\nEnter item code: ";
                    getline(cin, itemCode);

                    index = object.searchItem(itemCode);

                    if (index == -1)
                    {
                        cout << "\nItem not found!!" << endl;
                        cout << "\nKindly inform the Admin that the item is not in the stock which you are searching" << endl;
                        cout << "so that he can add the item to the stock." << endl;
                    }
                    else
                    {
                        cout << "ITEM NAME:     " << object[index].getItemName() << endl;
                        cout << "ITEM CODE:     " << object[index].getItemCode() << endl;
                        cout << "ITEM QUANTITY: " << object[index].getQuantity() << endl;
                        cout << "ITEM PRICE:    " << object[index].getPrice() << " Rs." << endl;
                    }

                    pauseAndClear();
                    cout << "\nDo you want to search another item? (press y for yes and any other key for no): ";
                    cin >> choice;
                    cin.ignore(1000, '\n');
                }

                pauseAndClear();
            }

            break;
        }

        case 4:
        {
            changePasswordEmployee();
            pauseAndClear();
            break;
        }

        case 5:
        {
            object.saveStock();
            break;
        }

        default:
            cout << "\nInvalid choice!!" << endl;
            break;
        }

    } while (employeeChoice != 5);
}
