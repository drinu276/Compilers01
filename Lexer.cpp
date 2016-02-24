#include <iostream>
#include <fstream>
#include "Lexer.h"

using namespace std;

enum TOK_TYPE {
    TOK_NUMBER,
    TOK_ARITHMETIC_OP,
    TOK_WHITESPACE,
    TOK_COMMENT,
    TOK_UNDEFINED,
    TOK_EOF
};

struct Token {
    TOK_TYPE TokenType;
    string name;
    int id;
};

void Token() {

}

void Token(TOK_TYPE type, string tokenName, int tokenID) {

}

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
