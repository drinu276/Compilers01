#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

class Token{

    public: enum TOK_TYPES
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
    TOK_TYPES TokenType;
    std::string contents;
    int id;
};

#endif // TOKEN_H_INCLUDED
