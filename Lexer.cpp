#include <iostream>
#include <fstream>
#include "Lexer.h"

using namespace std;

Lexer::Lexer(string fileName) {
    string fileIn = "", fileInLine = "";

    ifstream myfile;
    myfile.open (fileName.c_str(), ios::in);

    if (myfile.is_open()) {
        while(getline(myfile,fileInLine)) {
            fileIn = fileIn + fileInLine;
        }
    }
    cout << fileIn << endl;
    myfile.close();

}
