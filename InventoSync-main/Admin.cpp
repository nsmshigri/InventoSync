#include "Admin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Admin::pauseAndClear()
{
    cout << "\n\n";
    system("pause");
    system("cls");
}

Admin::Admin()
{
    username = "admin";
    password = "admin";
}

bool Admin::check()
{
    int count = 3;
    string enteredPassword, storedPassword;

    ifstream fin("password.txt");
    if (fin)
    {
        getline(fin, storedPassword);
    }
    fin.close();

    while (count != 0)
    {
        cout << "\nEnter password: ";
        getline(cin, enteredPassword);

        if (enteredPassword == storedPassword)
        {
            return true;
        }
        else
        {
            system("cls");
            cout << "\n\nWrong password!!\n";
            cout << "You have " << count - 1 << " attempts left.\n\n";
        }
        count = count - 1;

    }

    return false;
}

void Admin::changePassword()
{
    string empPassword;
    ifstream fin("password.txt");

    if (fin)
    {
        string line;
        getline(fin, line); // read and discard old password
        getline(fin, empPassword); // read employee password
    }
    fin.close();

    string newPassword, confirmNewPassword;
    cout << "\nEnter new password: ";
    getline(cin, newPassword);
    cout << "Confirm new password: ";
    getline(cin, confirmNewPassword);

    while (newPassword != confirmNewPassword)
    {
        system("cls");
        cout << "\nPasswords do not match. Please try again!\n\n";
        cout << "Enter new password: ";
        getline(cin, newPassword);
        cout << "Confirm new password: ";
        getline(cin, confirmNewPassword);
    }

    ofstream fout("password.txt");
    if (fout)
    {
        fout << newPassword << "\n";
        fout << empPassword;
        cout << "\nPassword changed successfully!!\n";
    }
    else
    {
        cout << "\nFile not found!!\n";
    }
    fout.close();
}

void Admin::displayAdminMenu()
{
    cout << "\n__________________________________________________\n";
    cout << "\n                  INVENTOSYNC                     \n";
    cout << "__________________________________________________\n";
    cout << "                  ADMIN MENU\n";
    cout << "__________________________________________________\n";
    cout << "\n1 - ADD NEW ITEM(s) IN STOCK";
    cout << "\n2 - UPDATE ITEM(s) IN STOCK";
    cout << "\n3 - DISPLAY ITEMS CURRENTLY IN STOCK";
    cout << "\n4 - SEARCH ITEM(s) FROM STOCK";
    cout << "\n5 - DELETE ITEM(s) FROM STOCK";
    cout << "\n6 - CHANGE PASSWORD";
    cout << "\n7 - EXIT & RETURN TO MAIN MENU (ALL CHANGES WILL BE SAVED)\n";
    cout << "__________________________________________________\n";
}

int Admin::getAdminChoice()
{
    int choice = -1;

    while (!(choice > 0 && choice < 8))
    {
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        system("cls");

        if (!(choice > 0 && choice < 8))
        {
            cout << "\nPlease choose a valid number from the following options of menu.\n\n";
            displayAdminMenu();
        }

        cin.ignore(1000, '\n'); // Clear input buffer
    }
    return choice;
}

void Admin::adminAccess()
{
    stock.loadStock();
    int adminChoice;
    do
    {
        displayAdminMenu();
        adminChoice = getAdminChoice();

        switch (adminChoice)
        {
        case 1:
        {
            int count = 0;
            char choice = 'y';

            while (choice == 'y' || choice == 'Y')
            {
                stock.printStock();
                pauseAndClear();

                string itemName, itemCode;

                int quantity = -1;
                double price = -1;

                cout << "\nEnter item name: ";
                getline(cin, itemName);

                cout << "Enter item code: ";
                getline(cin, itemCode);

                cout << "Enter quantity of " << itemName << ": ";
                while (quantity < 1)
                {
                    cin >> quantity;
                    if (quantity < 1)
                    {
                        cout << "\nInvalid Quantity. Enter Valid Quantity of " << itemName << ", must be greater than 0: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                }

                cout << "Enter price of " << itemName << ": ";
                while (price < 1)
                {
                    cin >> price;
                    if (price < 1)
                    {
                        cout << "\nValid Price of " << itemName << " must be more than 0. Please Enter again: ";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                }

                Item item(itemName, itemCode, quantity, price);
                stock.addItem(item);

                cout << "\n" << itemName << " against " << itemCode << " code added successfully!\n\n";

                pauseAndClear();
                cout << "Do you want to add another item to stock? (press y for yes and any other key for no): ";
                cin >> choice;
                cin.ignore(1000, '\n');
            }
            cout << count << " Item(s) added successfully.\n";

            cin.ignore(1000, '\n');
            pauseAndClear();

            break;
        }

        case 2:
        {
            if (stock.getSize() == 0)
            {
                cout << "\nSTOCK IS EMPTY!!\n";
            }
            else
            {
                string itemCode;
                int quantity = -1, index;

                char choice = 'y';

                while (choice == 'y' || choice == 'Y')
                {
                    stock.printStock();
                    pauseAndClear();

                    cout << "\nEnter item code: ";
                    getline(cin, itemCode);

                    index = stock.updateItem(itemCode);

                    if (index == -1)
                    {
                        cout << "\nThere is no Item with this Item Code. Add it to Stock.\n";
                    }

                    pauseAndClear();
                    
                    cout << "\nDo you want to update another item to stock? (press y for yes and any other key for no): ";
                    cin >> choice;
                   
                    cin.ignore(1000, '\n');
                }

                pauseAndClear();
            }
            break;
        }

        case 3:
        {
            stock.printStock();
            pauseAndClear();

            break;
        }

        case 4:
        {
            if (stock.getSize() == 0)
            {
                cout << "\nSTOCK IS EMPTY!!\n";
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

                    index = stock.searchItem(itemCode);

                    if (index == -1)
                    {
                        cout << "\nThere is no Item with this Item Code. You can add it to inventory if you want.\n";
                    }
                    else
                    {
                        cout << "\nITEM NAME:      " << stock[index].getItemName() << endl;
                        cout << "ITEM CODE:      " << stock[index].getItemCode() << endl;
                        cout << "ITEM QUANTITY:  " << stock[index].getQuantity() << endl;
                        cout << "ITEM PRICE:     " << stock[index].getPrice() << " Rs.\n";
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

        case 5:
        {
            if (stock.getSize() == 0)
            {
                cout << "\nSTOCK IS EMPTY!!\n";
            }
            else
            {
                int count = 0;
                char choice = 'y';

                while (choice == 'y' || choice == 'Y')
                {
                    stock.printStock();
                    pauseAndClear();

                    if (stock.getSize() != 0)
                    {
                        count++;
                        string itemCode;
                        cout << "\nEnter item code: ";
                        getline(cin, itemCode);
                        stock.removeItem(itemCode);
                        cout << "\nStock of Item removed successfully against code " << itemCode << ".\n\n";
                    }
                    else
                    {
                        cout << "\nNo more items can be removed because now Stock is empty.\n";
                        break;
                    }

                    pauseAndClear();
                    cout << "\nDo you want to remove another item? (press y for yes and any other key for no): ";
                    cin >> choice;
                    cin.ignore(1000, '\n');
                }
                cout << count << " item(s) removed successfully.\n";

                pauseAndClear();
            }
            break;
        }

        case 6:
        {
            changePassword();
            pauseAndClear();
            break;
        }

        case 7:
        {
            stock.saveStock();
            break;
        }

        default:
            cout << "\nInvalid choice!!\n";
            break;
        }

    } while (adminChoice != 7);

}


