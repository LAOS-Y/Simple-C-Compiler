#include<map>
#include<string>
#include <vector>
#include <json.hpp>

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

nlohmann::json symbol2Json(Symbol symbol){
    nlohmann::json j;
    j["type_idx"] = int(symbol.token);
    j["type"] = token2str[symbol.token];

    if (symbol.token == Token::INT_CONSTANT){
        j["value"] = *((int*)(symbol.ptr));
        return j;
    }

    if (symbol.token == Token::FLOAT_CONSTANT){
        j["value"] = *((float*)(symbol.ptr));
        return j;
    }

    if (symbol.token == Token::DOUBLE_CONSTANT){
        j["value"] = *((double*)(symbol.ptr));
        return j;
    }
        
    if (symbol.token == Token::IDENTIFIER){
        j["value"] = *((std::string*)(symbol.ptr));
        return j;
    }

    j["value"] = "NULL";
    return j;
}

nlohmann::json symbolTable2Json(SymbolTable &st){
    nlohmann::json j;
    j["table"] = nlohmann::json::array();

    for (SymbolTable::iterator it = st.begin(); it != st.end(); it++){
        j["table"].push_back(symbol2Json(*it));
    }

    return j;
}

void print(SymbolTable &st){
    for (SymbolTable::iterator it = st.begin(); it != st.end(); it++){
        Symbol symbol = *it;

        std::cout << token2str[it->token] << ' ';

        if (it->token == Token::INT_CONSTANT){
            std::cout << *((int*)(it->ptr)) << std::endl;
            continue;
        }

        if (it->token == Token::FLOAT_CONSTANT){
            std::cout << *((float*)(it->ptr)) << std::endl;
            continue;
        }

        if (it->token == Token::DOUBLE_CONSTANT){
            std::cout << *((double*)(it->ptr)) << std::endl;
            continue;
        }
            
        if (it->token == Token::IDENTIFIER){
            std::cout << *((std::string*)(it->ptr)) << std::endl;
            continue;
        }
        std::cout << "NULL" << std::endl;
    }
}