class Lexer
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

    struct Token
    {
        TOK_TYPES TokenType;
        std::string name;
        int id;
    };
    bool isArithmeticOperator(char in);
    bool isLetter(char in);
    bool isNumber(char in);
    //std::string removeComments(std::string in);
    Lexer(std::string fileName);
};
