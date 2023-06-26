#include <iostream>
#include <string>
#include <map>

enum Token {
    IF = 256,
    THEN,
    DO,
    WHILE,
    FOR,
    ELSE,
    SWITCH,
    ID,
    NUM,
    SOMA,
    INT,
    BOOL,
    ATRIBUICAO
};


std::map<Token, std::string> tokenToString = {
    { IF, "IF" },
    { THEN, "THEN" },
    { DO, "DO" },
    { WHILE, "WHILE" },
    { FOR, "FOR" },
    { ELSE, "ELSE" },
    { SWITCH, "SWITCH" },
    { ID, "ID" },
    { NUM, "NUM" },
    { SOMA, "SOMA" },
    { INT, "INT" },
    { BOOL, "BOOL" },
    { ATRIBUICAO, "ATRIBUICAO" }
};

Token getToken(const std::string& tokenString) {
    if (tokenString == "if") {
        return Token::IF;
    } else if (tokenString == "then") {
        return THEN;
    } else if (tokenString == "do") {
        return DO;
    } else if (tokenString == "while") {
        return WHILE;
    } else if (tokenString == "for") {
        return FOR;
    } else if (tokenString == "else") {
        return ELSE;
    } else if (tokenString == "switch") {
        return SWITCH;
    } else if (tokenString == "ID") {
        return ID;
    } else if (tokenString == "NUM") {
        return NUM;
    } else if (tokenString == "+") {
        return SOMA;
    } else if (tokenString == "int") {
        return INT;
    } else if (tokenString == "bool") {
        return BOOL;
    } else if (tokenString == "=") {
        return ATRIBUICAO;
    } else {
        // Retornar um valor especial para indicar que o token não foi encontrado
        return ID; // ou qualquer outro valor que faça sentido no seu programa
    }
}



int main() {
    std::string inputToken;
    std::cout << "Digite o token: ";
    std::cin >> inputToken;
    
    Token token = getToken(inputToken);
    
    if (tokenToString.count(token) > 0) {
        std::cout << "Token encontrado: " << tokenToString[token] << std::endl;
    } else {
        std::cout << "Token não encontrado." << std::endl;
    }
    
    return 0;
}
