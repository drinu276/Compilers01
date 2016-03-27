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
    bool isArithmeticOperator(char in);
    bool isLetter(char in);
    bool isNumber(char in);
    //std::string removeComments(std::string in);
    Lexer(std::string fileName);
};
