#include<map>
#include<string>
#include <vector>

enum Token{
    // Punctuators
    LPAR, // (
    RPAR, // )
    LSQB, // [
    RSQB, // ]
    LBRACE, // {
    RBRACE, // }
    COLON, // :
    COMMA, // ,
    SEMI, // ;
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /
    MOD, // %
    LESS, // <
    GREATER, // >
    ASSIGN, // =
    TILDE, // ~
    NOT, // !
    OR, // |
    AND, // &
    XOR, // ^
    DOT, // .
    COND, // ?
    SHARP, // #

    PTR, // ->
    INC, // ++
    DEC, // --
    LEFT, // <<
    RIGHT, // >>
    LE, // <=
    GE, // >=
    EQ, // ==
    NE, // !=
    LOGICAL_AND, // &&
    LOGICAL_OR, // ||
    MUL_ASSIGN, // *=
    DIV_ASSIGN, // /=
    MOD_ASSIGN, // %=
    ADD_ASSIGN, // +=
    SUB_ASSIGN, // -=
    LEFT_ASSIGN, // <<=
    RIGHT_ASSIGN, // >>=
    AND_ASSIGN, // &=
    XOR_ASSIGN, // ^=
    OR_ASSIGN, // |=
    ELLIPSIS, // ...

    // Punctuators end

    // KEYWORD BEGIN

    // TYPE SPECIFIER BEGIN
    VOID,
    CHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    BOOL,
    ENUM,
    // TYPE SPECIFIER END

    BREAK,
    CASE,
    CONTINUE,
    DEFAULT,
    DO,
    ELSE,
    FOR,
    GOTO,
    IF,
    RETURN,
    SIZEOF,
    SWITCH,
    WHILE,
    // KEYWORD END

    INT_CONSTANT,
    FLOAT_CONSTANT,
    DOUBLE_CONSTANT,
    IDENTIFIER,
};

std::map<std::string, Token> str2token{
    {"(", Token::LPAR},
    {")", Token::RPAR},
    {"[", Token::LSQB},
    {"]", Token::RSQB},
    {"{", Token::LBRACE},
    {"}", Token::RBRACE},
    {":", Token::COLON},
    {",", Token::COMMA},
    {";", Token::SEMI},
    {"+", Token::ADD},
    {"-", Token::SUB},
    {"*", Token::MUL},
    {"/", Token::DIV},
    {"%", Token::MOD},
    {"<", Token::LESS},
    {">", Token::GREATER},
    {"=", Token::ASSIGN},
    {"~", Token::TILDE},
    {"!", Token::NOT},
    {"|", Token::OR},
    {"&", Token::AND},
    {"^", Token::XOR},
    {".", Token::DOT},
    {"?", Token::COND},
    {"#", Token::SHARP},

    {"->", Token::PTR},
    {"++", Token::INC},
    {"--", Token::DEC},
    {"<<", Token::LEFT},
    {">>", Token::RIGHT},
    {"<=", Token::LE},
    {">=", Token::GE},
    {"==", Token::EQ},
    {"!=", Token::NE},
    {"&&", Token::LOGICAL_AND},
    {"||", Token::LOGICAL_OR},
    {"*=", Token::MUL_ASSIGN},
    {"/=", Token::DIV_ASSIGN},
    {"%=", Token::MOD_ASSIGN},
    {"+=", Token::ADD_ASSIGN},
    {"-=", Token::SUB_ASSIGN},
    {"<<=", Token::LEFT_ASSIGN},
    {">>=", Token::RIGHT_ASSIGN},
    {"&=", Token::AND_ASSIGN},
    {"^=", Token::XOR_ASSIGN},
    {"|=", Token::OR_ASSIGN},
    {"...", Token::ELLIPSIS},

    // Punctuators end

    // KEYWORD BEGIN

    // TYPE SPECIFIER BEGIN
    {"void", Token::VOID},
    {"char", Token::CHAR},
    {"short", Token::SHORT},
    {"int", Token::INT},
    {"long", Token::LONG},
    {"float", Token::FLOAT},
    {"double", Token::DOUBLE},
    {"bool", Token::BOOL},
    {"enum", Token::ENUM},
    // TYPE SPECIFIER END

    {"break", Token::BREAK},
    {"case", Token::CASE},
    {"continue", Token::CONTINUE},
    {"default", Token::DEFAULT},
    {"do", Token::DO},
    {"else", Token::ELSE},
    {"for", Token::FOR},
    {"goto", Token::GOTO},
    {"if", Token::IF},
    {"return", Token::RETURN},
    {"sizeof", Token::SIZEOF},
    {"switch", Token::SWITCH},
    {"while", Token::WHILE},
    // KEYWORD END

};

std::string token2str[] = {
    "(",
    ")",
    "[",
    "]",
    "{",
    "}",
    ":",
    ",",
    ";",
    "+",
    "-",
    "*",
    "/",
    "%",
    "<",
    ">",
    "=",
    "~",
    "!",
    "|",
    "&",
    "^",
    ".",
    "?",
    "#",

    "->",
    "++",
    "--",
    "<<",
    ">>",
    "<=",
    ">=",
    "==",
    "!=",
    "&&",
    "||",
    "*=",
    "/=",
    "%=",
    "+=",
    "-=",
    "<<=",
    ">>=",
    "&=",
    "^=",
    "|=",
    "...",

    // Punctuators end

    // KEYWORD BEGIN

    // TYPE SPECIFIER BEGIN
    "$VOID",
    "$CHAR",
    "$SHORT",
    "$INT",
    "$LONG",
    "$FLOAT",
    "$DOUBLE",
    "$BOOL",
    "$ENUM",
    // TYPE SPECIFIER END

    "$BREAK",
    "$CASE",
    "$CONTINUE",
    "$DEFAULT",
    "$DO",
    "$ELSE",
    "$FOR",
    "$GOTO",
    "$IF",
    "$RETURN",
    "$SIZEOF",
    "$SWITCH",
    "$WHILE",
    // KEYWORD END

    "$INT_CONSTANT",
    "$FLOAT_CONSTANT",
    "$DOUBLE_CONSTANT",
    "$IDENTIFIER",
};

struct Symbol{
    Token token;
    void * ptr;
};

typedef std::vector<Symbol> SymbolTable;