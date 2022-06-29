#include "Products.h"



Products::Products(){ //class name::function name

}

vector<Product> Products::get_item_list()const{ // return type is vector belongs to product class function name is get_item_list
    return item_list;
}
vector<Product> Products::get_shop_list()const{
    return shop_list;
}

Products::Products(const Products & p){
    item_list = p.get_item_list();
    shop_list = p.get_shop_list();
}

void Products::read_files(ifstream &qr, ifstream &price, const string fn2 ){ //reads files in the qr and price database
    string qrline, priceline, qrcode, pricecode, name;
    int idx1;
    double pricee;
    
    while(getline(qr, qrline)){
        
        qrline; // so that it matches
        idx1 = qrline.find(" ");
        name = qrline.substr(idx1 + 1);
        istringstream iss1(qrline);
        iss1 >> qrcode;
        ToUpper(qrcode);
        Product p1; // use product as p1
        p1.qr1 = qrcode; // assign qrcode into the variable x within product
        p1.qrname = name;
        item_list.push_back(p1); // add p1 to the item list vector
        
    }
    
        for(int i = 0; i < item_list.size(); i++){
            qrcode = item_list[i].qr1;
            price.close();
            price.open(fn2.c_str());
            while(getline(price, priceline)){
                istringstream iss2(priceline);
                iss2 >> pricecode >> pricee;
                if (qrcode == pricecode) {
                    item_list[i].qrprice = pricee; // item_list contains qrcode name and price of the items
                    
                }
            }
        }
}

void Products::add_item(string qr, int amount){ // qr code itemlist de varsa ve shoplist de yoksa user tarafından girilen qr code ve amount u shoplist e ekler
    //name ve price i shopliste eklemen lazim
    Product p2;
    ToUpper(qr);
    p2.qr2 = qr; // qr codes in the shoplist
    p2.amnt = amount; // amounts in the shoplist
    shop_list.push_back(p2);
    for (int i = 0; i < shop_list.size(); i ++) {
        for (int j = 0; j < item_list.size(); j++) {
            if (shop_list[i].qr2 == item_list[j].qr1 ) {
                shop_list[i].shopname = item_list[j].qrname;
                shop_list[i].shopprice = item_list[j].qrprice;
            }

        }
    }
    
    
}




bool Products::find(string qr_code){
    ToUpper(qr_code); //so that it mathces r
    for (int i = 0; i < item_list.size(); i++) {
        if (qr_code == item_list[i].qr1) {
            return true;
        }
    }
    return false;
}

bool Products::findInShopList(string qr_code){
    ToUpper(qr_code); //so that it matches
    for (int i = 0; i < shop_list.size(); i++) {
        if (qr_code == shop_list[i].qr2) {
            return true;
        }
    }
    return false;
}

void Products::remove_item(string qr){
    
    for (int i = 0 ; i < shop_list.size(); i++) {
        if (qr == shop_list[i].qr2) {
            shop_list.erase(shop_list.begin() + i);
        }
    }
}

void Products::edit_item(string qr, int amount){
    ToUpper(qr);
    for (int i = 0 ; i < shop_list.size(); i++) { //itirate over tne shoplist
        if (qr == shop_list[i].qr2) {
            shop_list[i].amnt = amount;
            
        }
    }
}

void Products::printCurrentReceipt(){
    
    string s = "_______________________________________ ";
    int ss = s.length();
    string n;
    int length;
    double totalvat = 0, total = 0;
    for (int i = 0; i < shop_list.size(); i++) {
        double totalprice = shop_list[i].shopprice * shop_list[i].amnt;
        n = shop_list[i].shopname;
        length = n.length() + 5;
        cout << shop_list[i].shopname.erase(shop_list[i].shopname.size() - 1) << " * " << setw(2) <<  shop_list[i].amnt << setw(ss - length - 3) << totalprice << endl;
        total += totalprice;
        totalvat += totalprice * 0.18;
       
    }
    total += totalvat;
    cout << endl;
    cout << "VAT(18%):" << setw(27) << totalvat << endl;
    cout << "_______________________________________" << endl;
    cout << "Total:" << setw(30) << total << endl;
    cout << endl;
}


void Products::printCurrentReceiptAscending(){
    //tempshop == shop_list;
    string n1;
    Product dummy;
    vector<Product> tempshop(shop_list.size(),dummy); //shoolistteki kadar index ve hepsi dummye eşit
   
    for (int i = 0 ; i < shop_list.size(); i++) {
        tempshop[i].tempname = shop_list[i].shopname;
        tempshop[i].tempamnt = shop_list[i].amnt;
        tempshop[i].tempprice = shop_list[i].shopprice;
    }
    string s = "_______________________________________";
    int ss = s.length();
    string n;
    int length;
    double totalvat = 0, total = 0;
    Product temp1, temp2, temp3;
    int minIndex;
    
    for (int i = 0; i < tempshop.size() - 1; i++) {
        minIndex = i;
        double totalprice = tempshop[i].tempprice * tempshop[i].tempamnt;
        for (int j = i + 1; j < tempshop.size(); j ++) {
            double totalprice2 = tempshop[j].tempprice * tempshop[j].tempamnt;
            if (totalprice2 < totalprice) { // sonradan gelen sayı öncekinden büyükse her şeyin yerini değiştiriceksin
                minIndex = j;
            }

        
        }temp1.tempname = tempshop[i].tempname;
        tempshop[i].tempname = tempshop[minIndex].tempname;
        tempshop[minIndex].tempname = temp1.tempname;
        
        temp2.tempamnt = tempshop[i].tempamnt;
        tempshop[i].tempamnt = tempshop[minIndex].tempamnt;
        tempshop[minIndex].tempamnt = temp2.tempamnt;
        
        
        temp3.tempprice = tempshop[i].tempprice;
        tempshop[i].tempprice = tempshop[minIndex].tempprice;
        tempshop[minIndex].tempprice = temp3.tempprice;
    }
    for (int i = 0; i < tempshop.size(); i++) {
        double totalprice = tempshop[i].tempprice * tempshop[i].tempamnt;
        n = shop_list[i].shopname;
        length = n.length() + 5;
        
        cout << tempshop[i].tempname << " * " << setw(2) <<  tempshop[i].tempamnt << setw(ss - length - 1) << totalprice << endl;
        total += totalprice;
        totalvat += totalprice * 0.18;
        
    }
    total += totalvat;
    cout << endl;
    cout << "VAT(18%):" << setw(27) << totalvat << endl;
    cout << "_______________________________________" << endl;
    cout << "Total:" << setw(30) << total << endl;
    cout << endl;
}
    

void Products::printCurrentReceiptDescending(){
    Product dum;
    vector<Product> tempshop(shop_list.size(), dum);
    for (int i = 0 ; i < shop_list.size(); i++) {
        tempshop[i].tn = shop_list[i].shopname;
        tempshop[i].tamnt = shop_list[i].amnt;
        tempshop[i].tp = shop_list[i].shopprice;
    }
    string s = "_______________________________________";
    int ss = s.length();
    string n;
    int length = 0;
    double totalvat = 0, total = 0;
    Product temp1, temp2, temp3;
    int maxIndex;
    for (int i = 0; i < tempshop.size() - 1; i++) {
        maxIndex = i;
        double totalprice = tempshop[i].tp * tempshop[i].tamnt;
        for (int j = i + 1; j < tempshop.size(); j ++) {
            double totalprice2 = tempshop[j].tp * tempshop[j].tamnt;
            if (totalprice2 > totalprice) { // sonradan gelen sayı öncekinden küçükse her şeyin yerini değiştiriceksin
                maxIndex = j;
            }
        
        }temp1.tn = tempshop[i].tn;
        tempshop[i].tn = tempshop[maxIndex].tn;
        tempshop[maxIndex].tn = temp1.tn;
        
        temp2.tamnt = tempshop[i].tamnt;
        tempshop[i].tamnt = tempshop[maxIndex].tamnt;
        tempshop[maxIndex].tamnt = temp2.tamnt;
        
        temp3.tp = tempshop[i].tp;
        tempshop[i].tp = tempshop[maxIndex].tp;
        tempshop[maxIndex].tp = temp3.tp;
    }
    for (int i = 0; i < tempshop.size(); i++) {
        double totalprice = tempshop[i].tp * tempshop[i].tamnt;
        n = tempshop[i].tn;
        length = n.length() + 5;
        cout << tempshop[i].tn << " * " << setw(2) <<  tempshop[i].tamnt << setw(ss - length - 3) << totalprice << endl;
        total += totalprice;
        totalvat += totalprice * 0.18;
        
    }
    total += totalvat;
    cout << endl;
    cout << "VAT(18%):" << setw(27) << totalvat << endl;
    cout << "_______________________________________" << endl;
    cout << "Total:" << setw(30) << total <<  endl;
    cout << endl;
    
}
