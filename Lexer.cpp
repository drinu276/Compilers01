#include <iostream>
#include <fstream>
#include <queue>
#include <regex>
#include "Lexer.h"
#include "Token.h"
#include <unistd.h>
#include <string.h>

/* ----- TOKENS ------
TOK_MULTIPLICATIVEOP = '*' | '/' | 'and'
TOK_ADDITIVEOP = '+' | '-' | 'or'
TOK_RELATIONALOP = '<' | '>' | '==' | '!=' | '<=' | '>='
TOK_EQUALS = '='
TOK_COLON = ':'
TOK_SEMICOLON = ';'
TOK_COMMA = ','
TOK_CURLYBRACE = { | }
TOK_ROUNDBRACE = ( | )
---------------------- */

using namespace std;

enum TOK_TYPES
{
    TOK_ADDITIVEOP,
    TOK_BOOL,
    TOK_BOOLEANLITERAL,
    TOK_COLON,
    TOK_COMMA,
    TOK_CURLYBRACE_CLOSE,
    TOK_CURLYBRACE_OPEN,
    TOK_DIGIT,
    TOK_DOUBLEQUOTE,
    TOK_EOF,
    TOK_EQUALS,
    TOK_INT,
    TOK_LETTER,
    TOK_MULTIPLICATIVEOP,
    TOK_PRINTABLE,
    TOK_REAL,
    TOK_RELATIONALOP,
    TOK_RESWORD_AND,
    TOK_RESWORD_BOOL,
    TOK_RESWORD_DEF,
    TOK_RESWORD_ELSE,
    TOK_RESWORD_FALSE,
    TOK_RESWORD_IF,
    TOK_RESWORD_INT,
    TOK_RESWORD_NOT,
    TOK_RESWORD_OR,
    TOK_RESWORD_REAL,
    TOK_RESWORD_RETURN,
    TOK_RESWORD_SET,
    TOK_RESWORD_STRING,
    TOK_RESWORD_TRUE,
    TOK_RESWORD_VAR,
    TOK_RESWORD_WHILE,
    TOK_RESWORD_WRITE,
    TOK_ROUNDBRACE_CLOSE,
    TOK_ROUNDBRACE_OPEN,
    TOK_SEMICOLON,
    TOK_STRING
};

char curr, peek;
static int id = 0;
queue <Token> tokenList;

bool isArithmeticOperator (char in)
{
    if (in == '+' || in == '-' || in == '*' ||in == '/')
        return true;
    else
        return false;
}

bool isRelationalOperator (char in)
{
    if (in == '<' || in == '>' || in == '!' || in == '=')
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

bool isDigit(char in)
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

bool isBrace (char in)
{
    if (in == '(' || in == ')' || in == '{' || in == '}')
        return true;
    else
        return false;
}

bool isComma (char in)
{
    if (in == ',')
        return true;
    else
        return false;
}

bool isColon (char in)
{
    if (in == ';' && in == ':')
        return true;
    else
        return false;
}

bool isDoubleQuote (char in)
{
    if (in == '"')
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

void createToken(TOK_TYPES TokType, string contents, int id)
{
    Token newToken;
    newToken.TokenType = static_cast<Token::TOK_TYPES>(TokType);
    newToken.contents = contents;
    newToken.id = id;
    tokenList.push(newToken);
    id++;
}

void tokeniser(string in)
{
    Token newToken;
    string buf = "";

    int i = 0, size = in.length();
    while (i < size)
    {
        curr = in[i];
        if (isDigit(curr))
        {
            bool isReal = false;
            while (isDigit(curr))
            {
                buf += curr;
                i++;
                curr = in[i];
                if (curr == '.' && isDigit(in[i+1]))
                {
                    isReal = true;
                    buf += curr;
                    i++;
                    curr = in[i];
                }
                else if (curr == '.' && !isDigit(in[i+1]))
                {
                    cout << "Real numbers must have a digit after the decimal" << endl;
                }
            }
            if (isReal)
            {
                createToken(TOK_REAL, buf, id);
            }
            else
            {
                createToken(TOK_INT, buf, id);
            }
            buf = "";
        }
        else if (isArithmeticOperator(curr))
        {
            buf += curr;
            if (curr == '+' || curr == '*')
            {
                cout << "buf: " << buf << endl;
                cout << "id: " << id << endl;
                createToken(TOK_ADDITIVEOP, buf, id);
            }
            else
            {
                createToken(TOK_MULTIPLICATIVEOP, buf, id);
            }
            buf = "";
            i++;
        }
        else if (isRelationalOperator(curr))
        {
            while (isRelationalOperator(curr))
            {
                buf += curr;
                i++;
                curr = in[i];
            }
            if (strcmp(buf.data(),"=") == 0)
            {
                createToken(TOK_EQUALS, buf, id);
            }
            else
            {
                createToken(TOK_RELATIONALOP, buf, id);
            }
            buf = "";
        }
        else if (isLetter(curr))
        {
            while (isLetter(curr) || isDigit(curr))
            {
                buf += curr;
                i++;
                curr = in[i];
            }
            if (strcmp(buf.data(),"real") == 0)
            {
                createToken(TOK_RESWORD_REAL, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"int") == 0)
            {
                createToken(TOK_RESWORD_INT, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"bool") == 0)
            {
                createToken(TOK_RESWORD_BOOL, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"string") == 0)
            {
                createToken(TOK_RESWORD_STRING, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"true") == 0)
            {
                createToken(TOK_RESWORD_TRUE, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"false") == 0)
            {
                createToken(TOK_RESWORD_FALSE, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"and") == 0)
            {
                createToken(TOK_RESWORD_AND, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"or") == 0)
            {
                createToken(TOK_RESWORD_OR, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"not") == 0)
            {
                createToken(TOK_RESWORD_NOT, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"set") == 0)
            {
                createToken(TOK_RESWORD_SET, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"var") == 0)
            {
                createToken(TOK_RESWORD_VAR, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"def") == 0)
            {
                createToken(TOK_RESWORD_DEF, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"write") == 0)
            {
                createToken(TOK_RESWORD_WRITE, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"return") == 0)
            {
                createToken(TOK_RESWORD_RETURN, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"if") == 0)
            {
                createToken(TOK_RESWORD_IF, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"else") == 0)
            {
                createToken(TOK_RESWORD_ELSE, buf, id);
                buf = "";
                i++;
                continue;
            }
            if (strcmp(buf.data(),"while") == 0)
            {
                createToken(TOK_RESWORD_WHILE, buf, id);
                buf = "";
                i++;
                continue;
            }
            createToken(TOK_STRING, buf, id);
            buf = "";
        }
        else if (isComma(curr))
        {
            buf += curr;
            createToken(TOK_COMMA, buf, id);
            buf = "";
            i++;
        }
        else if (isColon(curr))
        {
            buf += curr;
            if (curr == ';')
            {
                createToken(TOK_SEMICOLON, buf, id);
            }
            else
            {
                createToken(TOK_COLON, buf, id);
            }
            buf = "";
            i++;
        }
        else if (isBrace(curr))
        {
            buf += curr;
            if (curr == '(')
            {
                createToken(TOK_ROUNDBRACE_OPEN, buf, id);
            }
            else if (curr == ')')
            {
                createToken(TOK_ROUNDBRACE_CLOSE, buf, id);
            }
            else if (curr == '{')
            {
                createToken(TOK_CURLYBRACE_OPEN, buf, id);
            }
            else
            {
                createToken(TOK_CURLYBRACE_CLOSE, buf, id);
            }
            buf = "";
            i++;
        }
        else if (isDoubleQuote(curr))
        {
            buf += curr;
            createToken(TOK_DOUBLEQUOTE, buf, id);
            buf = "";
            i++;
        }
        else
        {
            i++;
        }
    }
    createToken(TOK_EOF, "", id);
    //while (!tokenList.empty())
    //{
    //    std::cout << "[" << tokenList.front().contents << "] size: " << tokenList.size() << endl; //note: accesses first element... apparently
    //    tokenList.pop(); //note: removes first element...
    //}
}

Token Lexer::GetNextToken()
{
    Token newTok = tokenList.front();
    tokenList.pop();
    return newTok;
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
