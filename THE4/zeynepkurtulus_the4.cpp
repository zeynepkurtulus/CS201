#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "strutils.h"




using namespace std;

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
    string fn1, fn2, fn3, line1, line2, line3, shopqr, dataqr, name, amount, priceqr, price;
    int idx1, lenght;
    double vat, total = 0, totalvat = 0;
    

    ifstream i1, i2, i3;
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
    cin >> fn2; //price

    while(exists(fn2) == false){ //if the name is invalid keep asking the name
        cout << endl;
        cout << "The Price file does not exists" << endl;
        cout << "Please enter a filename for Price database: ";
        cin >> fn2;
    }
    
    cout << endl;

    cout << "Please enter a filename for your shopping list: ";
    cin >> fn3; //shoplist
    cout << endl;

    i3.open(fn3.c_str()); //open shoplist file
    while(getline(i3,line3)){ //read line by line
        ToUpper(line3); // make each line uppercase so that qr codes matches 

        istringstream iss3(line3); // read word by word
        iss3 >> shopqr >> amount; //first item is the qr code and second one is the amount
        i1.close(); //to start reading from the begining each time => eğer if e girmezse baştan okumaya başlasın diye

        i1.open(fn1.c_str()); //open the qr coed file
        while(getline(i1,line1)){ //read line by line
            istringstream iss1(line1); // read word by word
            iss1 >> dataqr; //first element is the qr code of the data
 
            if(dataqr == shopqr){ //if the qr code in the shoplist matches with the qr codes in the data set
                idx1 = line1.find(" "); //index of the space
                name = line1.substr(idx1 + 1); //name of the product
                if (!isalpha(name[name.length() -1])) { //if we come to a space
                    name.pop_back(); //leave the space out
                }
                double damount = atof(amount); //convert the string amount to a double
                i2.close(); //to start reading from the begining each time => eğer if e girmezse diye tekrar başa almak için
                i2.open(fn2.c_str()); //opened the price txt
                while(getline(i2,line2)){ //read line by line
                    istringstream iss2(line2); //read word by word
                    iss2 >> priceqr >> price; //first item = qr code second item = price
                    double dprice = atof(price); //make the string price a double
                    if(priceqr == shopqr){// if the qrcode of the price matches with the qrcode of the shoplist item
                        string s = "____________________________________";
                        int ss = s.length();
                        lenght = name.length() + 5;
                        vat = dprice * damount * 0.18;

                        totalvat += vat;
                        total += vat + (damount * dprice);
                        
                        cout << name << " *" << setw(3) << damount << setw(ss - lenght) << damount * dprice << endl;
                        
                        
                        
                        
                        
                        
                        i2.close(); //close the pricelist txt
                    }
                    else if(i2.eof()){
                        
                    }
                }
                

                    
                
                i1.close();
            }
            else if(i1.eof()){
                
            }
        }
        
    }
    cout << endl << "VAT(18%):" << setw(27) << totalvat << endl;
    cout << "_______________________________________" << endl;
    cout << "Total:" << setw(30) << total << endl;
   
    return 0;
}

