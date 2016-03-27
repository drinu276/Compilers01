#include <iostream>
#include <fstream>
#include <queue>
#include "Lexer.h"

using namespace std;

char curr, peek;

class Token
{
public:
    enum TOK_TYPE
    {
        TOK_NUMBER,
        TOK_ARITHMETIC_OP,
        TOK_WHITESPACE,
        TOK_COMMENT,
        TOK_UNDEFINED,
        TOK_EOF
    };

    TOK_TYPE TokenType;
    string name;
    int id;


};



/*struct Token
{
    TOK_TYPE TokenType;
    string name;
    int id;
} newToken;

void Token(TOK_TYPE type, string tokenName, int tokenID)
{

} */

bool isNumericOperator (char in)
{
    if (in == '+' || in == '-' || in == '*' ||in == '/')
        return true;
    else
        return false;
}

bool isLetter(char in)
{
    if ((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z'))
        return true;
    else
        return false;
}

bool isNumber(char in)
{
    if (in >= '0' && in <= '9')
        return true;
    else
        return false;
}

string removeComments(string in)
{
    char first = 0, lookahead = 0;
    int i = 0, strLen = 0, skip = 0;
    string out;

    strLen = in.length();

    while (i < strLen-1)
    {
        first = in[i];
        lookahead = in[i+1];

        if (first == '/' && lookahead == '/')
        {
            skip = 1;
        }
        else if (first == '\n')
        {
            skip = 0;
        }

        if (!skip && lookahead != '/')
        {
            out = out+first;
        }
        i++;
    }
    return out;
}

void tokeniser(string in)
{
    queue <Token> tokenList;
    Token newToken;

    int i = 0, size = in.length();
    while (i < size)
    {
        newToken.name = in[i];
        curr = in[i];
        i++;
        tokenList.push(newToken);
    }


    cout<< "token list contains:" << endl;
    while (!tokenList.empty())
    {
        std::cout << "" << tokenList.front().name; //note: accesses first element... apparently
        tokenList.pop(); //note: removes first element...
    }
}

Lexer::Lexer(string fileName)
{
    string fileIn = "", fileInLine = "";

    ifstream myfile;
    myfile.open (fileName.c_str(), ios::in);

    if (myfile.is_open())
    {
        while(getline(myfile,fileInLine))
        {
            fileIn = fileIn + fileInLine;
            fileIn = fileIn + '\n';
        }
    }

    fileIn = removeComments(fileIn);
    cout << fileIn << endl;
    tokeniser(fileIn);
    myfile.close();

}
