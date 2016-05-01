#include <iostream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

Lexer lexer("example.txt");
Token tok;


Parser::Parser() {
  cout << "hellooooo" << endl;
  tok = lexer.GetNextToken();
  cout << tok.contents << endl;
}
