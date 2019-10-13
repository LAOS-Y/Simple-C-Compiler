#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "lexer.h"

bool isDigit(char c){
    return '0' <= c && c <= '9';
}

bool isLetter(char c){
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool isLetterOrUnderline(char c){
    return (c == '_') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool isInt(std::string s){
    for (std::string::iterator i = s.begin(); i != s.end(); i++){
        if (!isDigit(*i)){
            return false;
        }
    }

    return true;
}

bool isDouble(std::string s){
    int cnt = 0;

    if (s.length() < 2){
        return false;
    }

    for (std::string::iterator i = s.begin(); i != s.end(); i++){
        if (*i == '.' && !cnt){
            cnt++;
            continue;
        }
        
        if (!isDigit(*i)){
            return false;
        }
    }

    return true && cnt;
}

bool isFloat(std::string s){
    if (s[s.length() - 1] != 'f' && s[s.length() - 1] != 'F'){
        return false;
    }

    if (s.length() == 1){
        return false;
    }

    return isDouble(s.substr(0, s.length() - 1));
}

bool isBlank(char c){
    return c == ' ' || c == '\t' || c == '\n';
}

int str2int(std::string s){
    int ans = 0;

    for (std::string::iterator i = s.begin(); i != s.end(); i++){
        ans *= 10;
        ans += *i - '0';
    }
    
    return ans;
}

double str2double(std::string s){
    double ans = 0;

    int pos = s.find('.');
    std::string before = s.substr(0, pos), after = s.substr(pos + 1); 

    for (std::string::iterator i = before.begin(); i != before.end(); i++){
        ans *= 10;
        ans += *i - '0';
    }

    double t = 0.1;
    for (std::string::iterator i = after.begin(); i != after.end(); i++){
        ans += (*i - '0') * t;
        t /= 10;
    }

    return ans;
}

float str2float(std::string s){
    return str2double(s.substr(0, s.length() - 1));
}

void printOneSymbol(Token token, void *ptr){
    std::cout << token2str[token] << ' ';

    if (token == Token::INT_CONSTANT){
        std::cout << *((int*)(ptr)) << std::endl;
        return;
    }
        
    if (token == Token::IDENTIFIER){
        std::cout << *((std::string*)(ptr)) << std::endl;
        return;
    }
    std::cout << "NULL" << std::endl;
}

SymbolTable tokenize(std::string code){
    SymbolTable symbol_table;
    int ahead = 0;

    while (ahead < code.length()){
        char c = code[ahead++];

        if (isBlank(c)){
            continue;
        }

        if (c == '.'){
            if (isLetterOrUnderline(code[ahead])){
                symbol_table.push_back(Symbol{Token::DOT, NULL});
                continue;
            }

            if (isDigit(code[ahead])){
                std::string buf = ".";
                c = code[ahead++];

                while(isDigit(c) || isLetterOrUnderline(c)){
                    buf += c;
                    c = code[ahead++];
                }

                if (isFloat(buf)){
                    float * ptr = new float;
                    *ptr = str2float(buf);

                    ahead--;
                    symbol_table.push_back(Symbol{Token::FLOAT_CONSTANT, (void*)ptr});

                    continue;
                }

                if (isDouble(buf)){
                    double * ptr = new double;
                    *ptr = str2double(buf);

                    ahead--;
                    symbol_table.push_back(Symbol{Token::DOUBLE_CONSTANT, (void*)ptr});

                    continue;
                }

                throw std::string("Invalid identifier: ") + buf;
            }
        }

        if (!isDigit(c) && !isLetterOrUnderline(c)){
            std::string buf = "";

            while(!isDigit(c) && !isLetterOrUnderline(c) && str2token.count(buf + c)){
                buf += c;
                c = code[ahead++];
            }

            if (!buf.length()){
                throw std::string("Unrecognized punctuator: ") + c;
            }

            if ((buf + c) == "//"){
                while (code[ahead] != '\n'){
                    ahead++;
                }

                continue;
            }

            if ((buf + c) == "/*"){
                char ch1 = code[ahead++], ch2 = code[ahead++];

                while (ch1 != '*' || ch2 != '/'){
                    ch1 = ch2;

                    ch2 = code[ahead++];
                }

                // std::cout << "/* */ detected" << std::endl;

                continue;
            }

            ahead--;
            symbol_table.push_back(Symbol{str2token[buf], NULL});

            continue;
        }

        // CONSTANT: INT FLOAT DOUBLE
        // also detect invalid identifier, such as 123aa
        if (isDigit(c) || c == '.'){
            std::string buf = "";

            int dot_cnt = 0;

            while(isDigit(c) || isLetterOrUnderline(c) || (c == '.' && (++dot_cnt) <= 1)){
                buf += c;
                c = code[ahead++];
            }

            if (isFloat(buf)){
                float * ptr = new float;
                *ptr = str2float(buf);

                ahead--;
                symbol_table.push_back(Symbol{Token::FLOAT_CONSTANT, (void*)ptr});

                continue;
            }

            if (isDouble(buf)){
                double * ptr = new double;
                *ptr = str2double(buf);

                ahead--;
                symbol_table.push_back(Symbol{Token::DOUBLE_CONSTANT, (void*)ptr});

                continue;
            }

            if (isInt(buf)){
                int * ptr = new int;
                *ptr = str2int(buf);

                ahead--;
                symbol_table.push_back(Symbol{Token::INT_CONSTANT, (void*)ptr});

                continue;
            }

            throw std::string("Invalid identifier: ") + buf;

        }

        if (isLetterOrUnderline(c)){
            std::string buf = "";

            while(isLetterOrUnderline(c) || isDigit(c)){
                buf += c;
                c = code[ahead++];
            }

            void *ptr;

            if (!str2token.count(buf)){
                std::string *ptr = new std::string;
                *ptr = buf;

                symbol_table.push_back(Symbol{Token::IDENTIFIER, (void*)ptr});
            }
            else{
                symbol_table.push_back(Symbol{str2token[buf], (void*)ptr});
            }

            ahead--;
            continue;
        }
    }

    return symbol_table;
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

int main(int argc, char *argv[]){
    std::string code;
    std::ifstream file;

    if (argc == 1){
        std::cerr << "No source file" << std::endl; 
    }

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(argv[1]);
        std::stringstream stream;

        stream << file.rdbuf();

        file.close();

        code = stream.str();
    }
    catch (std::ifstream::failure e){
        std::cout << "ERROR::FILE NOT SUCCESSFULLY READ" << std::endl;
    }

    SymbolTable symbol_table;

    try{
        symbol_table = tokenize(code);
    }
    catch (std::string e){
        std::cerr << e << std::endl;

        return -1;
    }

    print(symbol_table);
    return 0;
}
