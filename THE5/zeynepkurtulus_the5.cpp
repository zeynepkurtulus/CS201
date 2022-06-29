#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Products.h"
#include "strutils.h"

using namespace std;


bool amountcheck(int amount){
    if (amount >= 0 && amount <= 25) {
        return true;
    }else
        return false;
}

void display(int &choice){
    cout << "MENU" << endl;
    cout << "1. Add item to the shopping list" << endl;
    cout << "2. Delete item from the shopping list" << endl;
    cout << "3. Edit the amount of existing item" << endl;
    cout << "4. Print current receipt" << endl;
    cout << "5. Print current receipt in order" << endl;
    cout << "6. Print current receipt in reverse order" << endl;
    cout << "7. Exit" << endl;
    cout << "---" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
}


bool exists(string s1){ //checks if the file can be opened
    bool v1;
    ifstream input1;
    input1.open(s1.c_str());
    if(input1.fail()){
        v1 = false; //return false if it cannot open
    }
    else{
        v1 = true; //return true if it can open
    }
    return v1;
}

int main(){
    Products pro;
    string fn1, fn2, qr_code, qr;
    ifstream stock, price;
    int choice = 0, amount;
    
    cout << "Please enter a filename for QR database: ";
    cin >> fn1; //qrfile
    
    while(exists(fn1) == false){ //if the name is invalid
        cout << endl;
        cout << "The QR file does not exists" << endl; //keep asking the name
        cout << "Please enter a filename for QR database: ";
        cin >> fn1;
    }
    cout << endl;
    
    cout << "Please enter a filename for Price database: ";
    cin >> fn2;
    
    while(exists(fn2) == false){
        cout << endl;
        cout << "The Price file does not exists" << endl; //keep asking it until valid
        cout << "Please enter a filename for the Price database: ";
        cin >> fn2;
    }
    
    stock.open(fn1.c_str()); //open the qr database
    price.open(fn2.c_str()); //open the price database
    pro.read_files(stock, price, fn2);
    
    
    bool goOn = true;
    while (goOn) {
        display(choice);
        if (choice == 7) { // exit option
            cout << "Goodbye!" << endl;
            goOn = false;
            
        }
        if(choice == 1){ //adding item
            cout << "Please enter the QR code to add: ";
            cin >> qr_code;
            if (pro.find(qr_code) == false) { //keep displaying the menu if the qr code dne
                cout << "Invalid QR code, try again" << endl;
            }
            
            if (pro.find(qr_code) && pro.findInShopList(qr_code) == false) { //if qr code exists
                cout << "Please enter the amount to add: ";
                cin >> amount;
                if (amountcheck(amount) == false) { //amount valid değil ise
                    cout << "Invalid amount, try again" << endl;
                    
                }
                // amount ve qrcode valid ise
                else {
                    pro.add_item(qr_code, amount); // add qr code and amount to the shoplist 
                }
            }
                
            else if (pro.find(qr_code) && pro.findInShopList(qr_code)) // both in shoplist and price list
            {
                cout << "Item is already in the shoplist, if you want to edit the amount please choose option 3" << endl;
            }
                
            
        }else if (choice == 2){ // delete item
            cout << "Please enter the QR code to delete: ";
            cin >> qr;
            if (pro.findInShopList(qr) == false) { // if the qr code is not found in the shoplist
                cout << "Shoplist does not contain given QR code" << endl;
            }
            else{
                pro.remove_item(qr);
            }
            
        }else if(choice == 3){ // edit item
            cout << "Please enter the QR code to edit: ";
            cin >> qr;
            if(pro.findInShopList(qr) == false) { // qr code dne
                cout << "Shoplist does not contain the given QR code." << endl;
            }else // qr code exists
            {
                cout << "Please enter the amount to edit: ";
                cin >> amount;
                if (amountcheck(amount) == false) { //invalid amount
                    cout << "Invalid amount try again" << endl;
                    
                }else if (amountcheck(amount)){ //valid amount
                    pro.edit_item(qr, amount);
                }
            }
        }else if (choice == 4){ //print receipt
            pro.printCurrentReceipt();
        }else if (choice == 5){ // print receipt in ascending order
            pro.printCurrentReceiptAscending();
            
        }else if (choice == 6){ //print receipt in descending order 
            pro.printCurrentReceiptDescending();
        }
        
        
    }
    

    
    
    return 0;
}
