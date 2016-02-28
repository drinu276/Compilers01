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

bool isNumericOperator (char in) {
    if (in == '+' || in == '-' || in == '*' ||in == '/')
        return true;
    else
        return false;
}

bool isLetter(char in) {
    if ((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z'))
        return true;
    else
        return false;
}

bool isNumber(char in) {
    if (in >= '0' && in <= '9')
        return true;
    else
        return false;
}

string removeComments(string in) {
    char first = 0, lookahead = 0;
    int i = 0, strLen = 0, skip = 0, changed = 1;
    string out;

    strLen = in.length();

    while (i < strLen-1) {
        first = in[i];
        lookahead = in[i+1];

        if (first == '/' && lookahead == '/') {
            skip = 1;
        } else if (first == '\n') {
            skip = 0;
        }

        if (!skip) {
            out = out+first;
        }
        i++;
    }
return out;
}

Lexer::Lexer(string fileName) {
    string fileIn = "", fileInLine = "", fileInString = "";

    ifstream myfile;
    myfile.open (fileName.c_str(), ios::in);

    if (myfile.is_open()) {
        while(getline(myfile,fileInLine)) {
            fileIn = fileIn + fileInLine;
            fileIn = fileIn + '\n';
        }
    }
    cout << removeComments(fileIn) << endl;
    myfile.close();

}
