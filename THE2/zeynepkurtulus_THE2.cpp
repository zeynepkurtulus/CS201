#include <iostream>

using namespace std;


int max(int previousmax, int current, int budget){ // determines the maximum price
    if (current > budget || current < previousmax){
        return previousmax;
    }
    return current;
}


int price(int quantity1, int quantity2, int quantity3){ // calculates the price
    int prc =  5*quantity1 + 10*quantity2 + 15*quantity3;
    return prc;
}


void compareprices(int q1, int q2, int q3, int budget, int & maxprice){ // compares the prices
    int currprice = price(q1,q2,q3);
    maxprice = max(maxprice, currprice, budget); // sets the max price
}


int combinations(int quantity1, int quantity2, int quantity3, int budget){ // calculates all possible combinations
    int maxprice = -1;

    compareprices(quantity1,quantity3,quantity2, budget, max_price);
    compareprices(quantity1,quantity2,quantity3, budget, max_price);
    compareprices(quantity2,quantity1,quantity3, budget, max_price);
    compareprices(quantity2,quantity3,quantity1, budget, max_price);
    compareprices(quantity3,quantity2,quantity1, budget, max_price);
    compareprices(quantity3,quantity1,quantity2, budget, max_price);

    return max_price;
}


bool budgetChecker(int budget){ // input checker for the budget
    return budget >= 0;
}


bool quantitiychecker(int quantity1, int quantity2, int quantity3){ // input checker for the quantity
    return quantity1 > 0 && quantity2 > 0 && quantity3 > 0;
}


void displayer(){ //displays the info in the screen
    int quantity1, quantity2, quantity3, budget;
    cout << "Please enter your budget: ";
    cin >> budget;

    if(budgetChecker(budget)){
        cout << "Please enter three quantities: ";
        cin >> quantity1 >> quantity2 >> quantity3;
        if(quantitiychecker(quantity1, quantity2, quantity3)){
            int maxprice = combinations(quantity1,quantity2,quantity3,budget);
            if(maxprice == -1){
                cout << "You cannot afford any of the permutations with these quantities and budget." << endl;
            }
            else{
                cout << "You have " << budget - maxprice << " liras left." << endl;
            }
        } 
        else{
            cout << "All quantities must be positive." << endl;
        }
    }
    else{
        cout << "Budget cannot be negative." << endl;
    }
    cout << endl;
}


int main(){
    displayer();
    displayer();
    cout << "Goodbye!" << endl;
    return 0;
}
