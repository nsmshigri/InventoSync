#include <iostream>
#include <string>
#include "Purchase.h"
#include "Stock.h"

using namespace std;

void Purchase::pauseAndClear()
{
    cout << "\n\n";
    system("pause");
    system("cls");
}

void Purchase::resize()
{
    purchaseSize++;
    Item* temp = new Item[purchaseSize];

    for (int i = 0; i < purchaseSize - 1; i++)
    {
        temp[i] = PurchaseItem[i];
    }

    delete[] PurchaseItem;
    PurchaseItem = temp;
}

Purchase::Purchase()
{
    purchaseSize = 1;
    currentSize = 0;
    PurchaseItem = new Item[purchaseSize];
}

Purchase::Purchase(const Purchase& purchase)
{
    purchaseSize = purchase.purchaseSize;
    currentSize = purchase.currentSize;
    PurchaseItem = new Item[purchaseSize];

    for (int i = 0; i < purchaseSize; i++)
    {
        PurchaseItem[i] = purchase.PurchaseItem[i];
    }
}

Purchase::~Purchase()
{
    delete[] PurchaseItem;
}

const Purchase& Purchase::operator=(const Purchase& purchase)
{
    if (this != &purchase)
    {
        delete[] PurchaseItem;

        purchaseSize = purchase.purchaseSize;
        currentSize = purchase.currentSize;
        PurchaseItem = new Item[purchaseSize];

        for (int i = 0; i < purchaseSize; i++)
        {
            PurchaseItem[i] = purchase.PurchaseItem[i];
        }
    }
    return *this;
}

Purchase::Purchase(const Item* arr, int s)
{
    purchaseSize = s;
    currentSize = 0;
    PurchaseItem = new Item[purchaseSize];
    
    for (int i = 0; i < s; i++)
    {
        PurchaseItem[i] = arr[i];
    }
}

int Purchase::getPurchaseSize() const
{
    return purchaseSize;
}

int Purchase::getCurrentSize() const
{
    return currentSize;
}

Item& Purchase::operator[](const int index) const
{
    return PurchaseItem[index];
}

const Item* Purchase::getPurchaseItemArray() const
{
    return PurchaseItem;
}

void Purchase::addPurshase(Stock& obj)
{
    if (obj.getSize() == 0)
    {
        cout << "\n\n\tSTOCK IS EMPTY!!" << endl;
        return;
    }

    char choice;
    int CustomerQuantity = 0;
    string itemName;

    do 
    {
        obj.printStock();
        cout << "\n\n\t\tEnter item Name: ";
        getline(cin, itemName);

        int index = obj.searchItemName(itemName);

        while (index == -1)
        {
            cout << "\n\t\tItem not found!! Enter valid item name: ";
            getline(cin, itemName);
            index = obj.searchItemName(itemName);
        }

        if (searchPurchasedItem(itemName) != -1)
        {
            cout << "\n\t\tItem already exists in the purchase list";
        }
        else
        {
            cout << "\n\t\tHow much quantity of " << itemName << " do you want to purchase? ";
            cin >> CustomerQuantity;

            while (obj[index].getQuantity() < CustomerQuantity)
            {
                cout << "\n\t\tSorry, we don't have enough quantity of " << itemName;
                cout << ". We only have " << obj[index].getQuantity() << " " << itemName << endl;

                cout << "\n\t\tPlease enter quantity less than or equal to " << obj[index].getQuantity() << endl;

                cout << "\n\t\tHow many " << itemName << " do you want to purchase? ";
                cin >> CustomerQuantity;
            }

            PurchaseItem[currentSize] = obj[index];
            PurchaseItem[currentSize].setQuantity(CustomerQuantity);
            PurchaseItem[currentSize].setTotalPrice();
            
            obj.updateItem(CustomerQuantity, itemName);
            currentSize = currentSize - 1;

            if (currentSize >= purchaseSize)
            {
                resize();
            }
        }
        
        pauseAndClear();
        cout << "Do you want to purchase another item? (y/n): ";
        cin >> choice;
        cin.ignore(1000, '\n');


    } while (choice == 'y' || choice == 'Y');

    pauseAndClear();
}

bool Purchase::updatePurchasedItem(string name, Stock& obj)
{
    int flag = searchPurchasedItem(name);
    int q = 0;

    if (flag != -1)
    {
        q = -PurchaseItem[flag].getQuantity();
        obj.updateItem(q, PurchaseItem[flag].getItemName());

        int indexStockItem = obj.searchItem(PurchaseItem[flag].getItemCode());
        int quantity;
       
        do
        {
            cout << "Enter quantity of " << PurchaseItem[flag].getItemName() << " you want to buy: ";
            cin >> quantity;

        } while (quantity > obj[indexStockItem].getQuantity());

        PurchaseItem[flag].setQuantity(quantity);
        PurchaseItem[flag].setTotalPrice();
        obj.updateItem(quantity, PurchaseItem[flag].getItemName());

        return true;
    }
    else
    {
        return false;
    }
}

bool Purchase::deletePurchasedItem(string name, Stock& obj)
{
    if (currentSize != 0)
    {
        int flag = searchPurchasedItem(name);
        int q = 1;

        if (flag != -1)
        {
            obj.updateItem(-PurchaseItem[flag].getQuantity(), name);

            for (int i = flag; i < currentSize - 1; i++)
            {
                PurchaseItem[i] = PurchaseItem[i + 1];
            }

            currentSize = currentSize - 1;
            cout << "\n\t\t" << name << " has been succesfully deleted from purchased list!!\n";
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout << "\n\t\tNo items in the purchased list!!\n";
        return false;
    }
}

int Purchase::searchPurchasedItem(string name)
{
    for (int i = 0; i < currentSize; i++)
    {
        if (name == PurchaseItem[i].getItemName())
        {
            return i;
        }
    }
    return -1;
}

void Purchase::printStock(Stock& obj)
{
    if (obj.getSize() == 0)
    {
        cout << "\n\n\tSTOCK IS EMPTY!!" << endl;
    }
    else
    {
        cout << "Items in Stock:" << endl;
        for (int i = 0; i < obj.getSize(); i++)
        {
            cout << "Item " << i + 1 << ": " << obj[i].getItemName() << ", Price: " << obj[i].getPrice() << " Rs." << endl;
        }
    }
}

void Purchase::displayReceipt()
{
    long double totalBill = 0;
    cout << "-----------------------------------------------" << endl;
    cout << "RECEIPT" << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < currentSize; i++)
    {
        cout << "Item " << i + 1 << ": " << PurchaseItem[i].getItemName() << ", Price: " << PurchaseItem[i].getPrice() << " Rs., Quantity: " << PurchaseItem[i].getQuantity() << ", Total Price: " << PurchaseItem[i].getTotalPrice() << " Rs." << endl;
        totalBill = totalBill + PurchaseItem[i].getTotalPrice();
    }

    cout << "-----------------------------------------------" << endl;
    cout << "TOTAL BILL : " << totalBill << " Rs." << endl;
    cout << "-----------------------------------------------" << endl;
}
