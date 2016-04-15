#include <iostream>
#include <fstream>
#include <queue>
#include <regex>
#include "Lexer.h"
#include <unistd.h>

/* ----- TOKENS ------
TOK_LETTER = A-Za-z
TOK_DIGIT = 0-9
TOK_PRINTABLE = \x20-\x7E
TOK_TYPE = 'real' | 'int' | 'bool' | 'string'
TOK_BOOLEANLITERAL = 'true' | 'false'
TOK_MULTIPLICATIVEOP = '*' | '/' | 'and'
TOK_ADDITIVEOP = '+' | '-' | 'or'
TOK_RELATIONALOP = '<' | '>' | '==' | '!=' | '<=' | '>='
TOK_EQUALS = '='
TOK_CURLYBRACE = { | }
TOK_ROUNDBRACE = ( | )
TOK_EOF
---------------------- */

using namespace std;

char curr, peek;
char* currPt;
static int id = 0;

class Token
{
public:
    enum TOK_TYPES
    {
        TOK_LETTER,
        TOK_DIGIT,
        TOK_PRINTABLE,
        TOK_TYPE,
        TOK_BOOLEANLITERAL,
        TOK_MULTIPLICATIVEOP,
        TOK_ADDITIVEOP,
        TOK_RELATIONALOP,
        TOK_EQUALS,
        TOK_CURLYBRACE,
        TOK_ROUNDBRACE,
        TOK_EOF
    };

    TOK_TYPES TokenType;
    string contents;
    int id;
};

enum TOK_TYPES
{
    TOK_LETTER,
    TOK_DIGIT,
    TOK_PRINTABLE,
    TOK_TYPE,
    TOK_BOOLEANLITERAL,
    TOK_MULTIPLICATIVEOP,
    TOK_ADDITIVEOP,
    TOK_RELATIONALOP,
    TOK_EQUALS,
    TOK_CURLYBRACE,
    TOK_ROUNDBRACE,
    TOK_EOF
};

bool isEquals (char in)
{
    if (in == '=')
        return true;
    else
        return false;
}

bool isArithmeticOperator (char in)
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

bool isPrintable (char in)
{
    if (in >= '\x20' && in <= '\x7E')
        return true;
    else
        return false;
}

string removeSingleLineComments(string in)
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
    string buf = "";

    int i = 0, size = in.length();
    while (i < size)
    {
        curr = in[i];
        usleep(10000);
        if (isNumber(curr))
        {
            while (isNumber(curr))
            {
                buf += curr;
                i++;
                curr = in[i];
            }
            newToken.TokenType = static_cast<Token::TOK_TYPES>(TOK_DIGIT);
            newToken.contents = buf;
            newToken.id = id;
            tokenList.push(newToken);
            buf = "";
            id++;
        }
        else if (isArithmeticOperator(curr))     //can detect single character operations only for now
        {
            buf += curr;

            newToken.TokenType = static_cast<Token::TOK_TYPES>(TOK_MULTIPLICATIVEOP);
            newToken.contents = buf;
            newToken.id = id;
            tokenList.push(newToken);
            buf = "";
            id++;
            i++;
        }
        else if (isEquals(curr))       //can detect single equals only for now
        {
            buf += curr;

            newToken.TokenType = static_cast<Token::TOK_TYPES>(TOK_EQUALS);
            newToken.contents = buf;
            newToken.id = id;
            tokenList.push(newToken);
            buf = "";
            id++;
            i++;
        }
        else
        {
            i++;
        }
    }
    cout<< "token list contains:" << endl;
    while (!tokenList.empty())
    {
        std::cout << "[" << tokenList.front().contents << "] size: " << tokenList.size() <<endl; //note: accesses first element... apparently
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

    fileIn = removeSingleLineComments(fileIn);
    cout << fileIn << endl;
    tokeniser(fileIn);


    myfile.close();

}
