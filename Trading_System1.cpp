#include <iostream>
#include <fstream>
#include <string>
//#include <typeinfo>
#include <iomanip>

using namespace std;

// function to return the last line, i.e. current spot price
string readinglastline(string name) {
    ifstream fin;
    fin.open(name);
    string lastLine; 
    if(fin.is_open()) {
        fin.seekg(-1,ios_base::end);                // go to one spot before the EOF

        while(true) {
            char ch;
            fin.get(ch);                            // Get current byte's data
            // not used since the file is not going to be empty in this case.
            /* if((int)fin.tellg() <= 1) {          // If the data was at or before the 0th byte
                fin.seekg(0);                       // The first line is the last line
                break;                              // So stop there
            } */ 
            if(ch == '\n') {                        // If the data was a newline
                break;                              // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                fin.seekg(-2,ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }
                   
        getline(fin,lastLine);                      // Read the current line
        
        //cout << "Result: " << lastLine << '\n';
        
        fin.close();
        
    }
    return lastLine;
}

//function to separate time from the last line
string time(string line) {
    return line.substr(0,20).replace(10,1," ").erase(19);
}

//function to separte the price from the last line
double spotprice(string line) {
    return stod(line.substr(21, line.length()));
}

//function to check if the investment is in loss
void check_loss(double curr_value, double bought_price, double &stop_loss_percent, string t) {
    //cout <<"in check loss" << curr_price << endl;
    float loss = ((bought_price - curr_value)/bought_price) * 100;
    if(loss >= stop_loss_percent) {
        std::cout << "\nResult: \nThe admissible loss percent is reached.";
        std::cout << "\nAt " << t << " UTC, you are " << loss << "% in loss with current value of your assets at Rs. " << curr_value << endl;
    }

    else {
        std::cout << "\nResult: \nThe admissible loss percent is not reached.";
        std::cout << "\nAt " << t << " UTC, you are " << loss << "% in loss with current value of your assets at Rs. " << curr_value << endl;
    }
}

// function to check if the investment is in profit
void check_profit(double curr_value, double &bought_price, double &take_profit_percent, string t) {

    float profit = ((curr_value - bought_price)/bought_price) * 100;
    if(profit >=  take_profit_percent) {
        std::cout << "\nResult: \nThe admissible profit percent is reached.";
        std::cout << "\nAt " << t << " UTC, you are " << profit << "% in profit with current value of your assets at Rs. " << curr_value << endl;
    }
    else {
        std::cout << "\nResult: \nThe admissible profit percent is not reached.";
        std::cout << "\nAt " << t << " UTC, you are " << profit << "% in profit with current value of your assets at Rs. " << curr_value << endl;
    }
}

int main() {

    char ch;
    int choice;
    double coins, bought_price, stop_loss_percent, take_profit_percent, curr_price, curr_value;
    string lastline, t;
    
    std::cout.precision(12);

    do {
        // display coin menu
        std::cout << "\nCoin Menu\n\n1. Bitcoin (BTC)\n2. Ethereum (ETH)\n3. Chainlink (LINK)\n";
        std::cout << "Enter your choice of cryptocurrency: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                lastline = readinglastline("BTCprice.txt");
                break;
            case 2:
                lastline = readinglastline("ETHprice.txt");
                break;
            case 3:
                lastline = readinglastline("LINKprice.txt");
                break;
            default:
                std::cout << "Invalid choice of cryptocurrency." << std::endl;
                goto ending;
                break;
        }

        std::cout << "How many coins do you have? ";
        std::cin >> coins;
        std::cout << "How  much did you pay to buy these coins? ";
        std::cin >> bought_price;
        std::cout << "What percentage loss is admissible? ";
        std::cin >> stop_loss_percent;
        std::cout << "What percentage profit is admissible? ";
        std::cin >> take_profit_percent;

        //store the spot price and the time in two variables
        curr_price = spotprice(lastline);
        t = time(lastline);

        // check for profit, loss or no change
        curr_value = coins*curr_price;
        if (curr_value > bought_price)
        {
            check_profit(curr_value, bought_price, take_profit_percent, t);
        }
    
        else if (curr_value < bought_price)
        {
            check_loss(curr_value, bought_price, stop_loss_percent, t);
        }

        else
        {
            std::cout << "There is no change in the amount you invested and the current value of the coins you own at" << time(lastline) << endl;
        }

        ending:
            std::cout << "\nWant to continue? Y/N";
            std::cin >> ch;

    } while (ch == 'y' || ch == 'Y');
    
    return 0;
}

