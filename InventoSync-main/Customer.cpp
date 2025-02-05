#include <string>
#include <iostream>
#include <fstream>
#include "Purchase.h"
#include "Customer.h"

using namespace std;

void Customer::pauseAndClear()
{
    cout << "\n\n";
    system("pause");
    system("cls");
}

Customer::Customer()
{
    address = "";
    email = "";
}

void Customer::setCustomer(string name, string id, string contact, string address, string email, string CNIC)
{
    User::setUser(name, id, contact);
    this->address = address;
    this->email = email;
    this->CNIC = CNIC;
}

void Customer::print()
{
    User::print();

    cout << "Address : " << address << endl;
    cout << "Email : " << email << endl;
}

string Customer::getAddress()
{
    return address;
}

string Customer::getEmail()
{
    return email;
}

string Customer::getCNIC()
{
    return CNIC;
}

void Customer::displayCustomerMenu()
{
    cout << "\n\n_________________________________________________________________\n";
    cout << "               INVENTOSYNC                           \n";
    cout << "                  CUSTOMER MENU\n";
    cout << "_________________________________________________________________\n";
    cout << "\n 1 - PURCHASE ITEM(s) FROM STOCK";
    cout << "\n 2 - DISPLAY ITEMS CURRENTLY IN STOCK";
    cout << "\n 3 - SEARCH ITEM(s) FROM STOCK";
    cout << "\n 4 - UPDATE PURCHASE";
    cout << "\n 5 - GENERATE RECEIPT";
    cout << "\n 6 - DELETE A PURCHASED ITEM";
    cout << "\n 7 - EXIT & RETURN TO MAIN MENU (ALL CHANGES WILL BE SAVED)\n";
    cout << "_________________________________________________________________\n";
}

int Customer::getCustomerChoice()
{
    int choice = -1;

    while (!(choice > 0 && choice < 8))
    {
        cout << "\n\n\n\t\tEnter your choice: ";
        cin >> choice;
        system("cls");

        if (!(choice > 0 && choice < 8))
        {
            cout << "\n\n\t\tPlease choose a valid number from the following options of menu.\n\n";
            displayCustomerMenu();
        }

        cin.clear();
        cin.ignore(1000, '\n');
    }
    return choice;
}


void Customer::saveReceipt()
{
    long double totalBill = 0;
    ofstream fout(getName() + ".txt");

    if (fout.is_open())
    {
        fout << "Customer Name: " << getName() << endl;
        fout << "Customer CNIC: " << getCNIC() << endl;
        fout << "Customer Phone Number: " << getPhone() << endl;
        fout << "Customer Address: " << getAddress() << endl;
        fout << "Customer Email: " << getEmail() << endl;
        fout << "-------------------------------------------------------------------------------------------\n";
        fout << "\t\tRECEIPT\n";
        fout << "-------------------------------------------------------------------------------------------\n";
        fout << "ITEM NAME\t\tSINGLE ITEM PRICE\t\tITEM QUANTITY\t\tTOTAL PRICE\n";
        fout << "-------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < purchaseItem.getCurrentSize(); i++)
        {
            fout << purchaseItem.getPurchaseItemArray()[i].getItemName() << "\t" << purchaseItem.getPurchaseItemArray()[i].getPrice() << "\t" << purchaseItem.getPurchaseItemArray()[i].getQuantity() << "\t" << purchaseItem.getPurchaseItemArray()[i].getTotalPrice() << endl;
            totalBill += purchaseItem.getPurchaseItemArray()[i].getTotalPrice();
        }

        fout << "-------------------------------------------------------------------------------------------\n";
        fout << "TOTAL BILL : " << totalBill << "$\n";
        fout << "-------------------------------------------------------------------------------------------\n";

        fout.close();
        cout << "\n\n\t\tReceipt saved successfully!\n";
    }
    else
    {
        cout << "\n\n\t\tFailed to save receipt. File could not be opened.\n";
    }
}

void Customer::customerAccess()
{
    string name, cnic, phone, address, email;
    int customerChoice;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your CNIC: ";
    getline(cin, cnic);
    cout << "Enter your phone number: ";
    getline(cin, phone);
    cout << "Enter your address: ";
    getline(cin, address);
    cout << "Enter your email: ";
    getline(cin, email);
    setCustomer(name, "0", phone, address, email, cnic);
    pauseAndClear();

    do
    {
        displayCustomerMenu();
        customerChoice = getCustomerChoice();

        switch (customerChoice)
        {
        case 1:
            obj.printStock();
            purchaseItem.addPurshase(obj);
            break;

        case 2:
            purchaseItem.printStock(obj);
            pauseAndClear();
            break;

        case 3:
            if (obj.getSize() != 0)
            {
                int indexOfItem = -1;
                char choice = 'y';
                while (choice == 'y' || choice == 'Y')
                {
                    do
                    {
                        string itemname;
                        cout << "\n\n\n\t\tEnter item name: ";
                        getline(cin, itemname);
                        indexOfItem = obj.searchItemName(itemname);
                        
                        if (indexOfItem == -1)
                            cout << "\n\n\t\tItem not found" << endl << "Please enter correct item Name.\n";
                        else
                        {
                            cout << "\nITEM NAME:     " << obj[indexOfItem].getItemName() << endl;
                            cout << "ITEM QUANTITY: " << obj[indexOfItem].getQuantity() << endl;
                            cout << "ITEM PRICE:    " << obj[indexOfItem].getPrice() << "/= Rs." << endl;
                        }
                    } while (indexOfItem == -1);
                    
                    
                    pauseAndClear();
                    cout << endl << "\n\n\tDo you want to search another item? (press y for yes and any other key for no): ";
                    cin >> choice;
                    cin.ignore();
                }
            }
            pauseAndClear();
            cin.ignore(1000, '\n');
            break;

        case 4:
            if (obj.getSize() != 0)
            {
                purchaseItem.displayReceipt();
                string name;
                char choice = 'y';
                while (choice == 'y' || choice == 'Y')
                {
                    if (purchaseItem.getCurrentSize() != 0)
                    {
                        do
                        {
                            cout << "\n\tEnter the name of item: ";
                            getline(cin, name);
                        } while (!purchaseItem.updatePurchasedItem(name, obj));
                    }
                    else
                    {
                        cout << "\n\tNo more items can be updated because the shopping cart is empty." << endl;
                        pauseAndClear();
                        break;
                    }
                    cout << "\n\tDo you want to update another item? (press y for yes and any other key for no): ";
                    cin >> choice;
                    cin.ignore();
                }
            }
            pauseAndClear();
            break;

        case 5:
            if (purchaseItem.getCurrentSize() > 0)
            {
                cout << "\n\n\t\tRECEIPT\n";
                purchaseItem.displayReceipt();
                saveReceipt();
            }
            else
            {
                cout << "\n\n\t\tNo items purchased yet.\n";
            }
            pauseAndClear();
            break;

        case 6:
            if (purchaseItem.getCurrentSize() > 0)
            {
                purchaseItem.displayReceipt();
                string name;
                char choice = 'y';
                while (choice == 'y' || choice == 'Y')
                {
                    if (purchaseItem.getCurrentSize() != 0)
                    {
                        do
                        {
                            cout << "\n\tEnter the name of item: ";
                            getline(cin, name);
                        } while (!purchaseItem.deletePurchasedItem(name, obj));
                    }
                    else
                    {
                        cout << "\n\tNo more items can be removed because the shopping cart is empty." << endl;
                        pauseAndClear();
                        break;
                    }
                    cout << "\n\tDo you want to remove another item? (press y for yes and any other key for no): ";
                    cin >> choice;
                    cin.ignore();
                }
            }
            pauseAndClear();
            break;

        case 7:
            obj.saveStock();
            saveReceipt();
            break;

        default:
            cout << "\n\n\t\tPlease choose a valid option.\n";
            pauseAndClear();
            break;

        }

    } while (customerChoice != 7);
}
