class Lexer
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

    struct Token
    {
        TOK_TYPE TokenType;
        std::string name;
        int id;
    };
    //isNumericOperator(char in);
    //isLetter(char in);
    //isNumber(char in);
    //removeComments(std::string in);
    //removeSpaces(std::string in);
    Lexer(std::string fileName);
};
