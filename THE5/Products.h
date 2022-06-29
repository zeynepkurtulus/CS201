#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

struct Product{
    string qr1, qr2, qrname, tempname =  "", shopname, tn = "";
    double qrprice = 0, tempprice = 0, shopprice = 0 , amnt = 0, tempamnt = 0, tp = 0, tamnt = 0;
    int count = 0;
};



class Products{

private:
    vector<Product> item_list; //empty vector
    vector<Product> shop_list; //empty vector 

public:
    Products();
    Products(const Products & p);
    vector<Product> get_item_list() const;
    vector<Product> get_shop_list() const;


    // you are going to implement these member functions
    void read_files(ifstream & qr, ifstream & price, const string fn2); 
    bool find(string qr_code);
    bool findInShopList(string qr_code);
    void add_item(string qr, int amount);
    void edit_item(string qr, int amount);
    void remove_item(string qr);
    void printCurrentReceipt();
    void printCurrentReceiptAscending();
    void printCurrentReceiptDescending();

};
