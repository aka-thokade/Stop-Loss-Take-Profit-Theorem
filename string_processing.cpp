#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string readinglastline() {
    ifstream fin;
    fin.open("price.txt");
    string lastLine; 
    if(fin.is_open()) {
        fin.seekg(-1,ios_base::end);                // go to one spot before the EOF

        while(true) {
            char ch;
            fin.get(ch);                            // Get current byte's data

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

string time(string line){
    return line.substr(0,20).replace(10,1," ").erase(19);
}

string money(string line) {
    return line.substr(21, line.length());
}

int main() {
    
    string lastline = readinglastline();
    string t = time(lastline);
    string m = money(lastline);
    std::cout << lastline << "\n" << t << "\n" << m << "\n";
    return 0;
}