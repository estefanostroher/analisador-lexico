#include<iostream>
#include<string>

enum Token {
    IF,
    THEN,
    WHILE,
    FOR,
    ELSE,
    ID,
    NUM,
    SOMA
};

Token getNextToken(const std::string& input){
    static int currentPosition = 0;
    static std::string currentToken = "";

    // Verifica se a posição atual está além do comprimento da entrada
    if (currentPosition >= input.length()) {
        // Retorna um token de fim de arquivo
        return Token::EOF;
    }

    // Pula espaços em branco
    while (input[currentPosition] == ' ' || input[currentPosition] == '\t') {
        currentPosition++;
    }

    // Verifica os caracteres especiais
    switch (input[currentPosition]) {
        case '+':
            currentPosition++;
            return Token::SOMA;
        // Adicione mais casos para outros caracteres especiais, se necessário

        default:
            break;
    }

    // Verifica se é um número
    if (isdigit(input[currentPosition])) {
        currentToken = "";
        while (isdigit(input[currentPosition])) {
            currentToken += input[currentPosition];
            currentPosition++;
        }
        return Token::NUM;
    }

    // Verifica se é uma palavra-chave ou identificador
    if (isalpha(input[currentPosition])) {
        currentToken = "";
        while (isalnum(input[currentPosition])) {
            currentToken += input[currentPosition];
            currentPosition++;
        }

        // Verifica se é uma palavra-chave conhecida
        if (currentToken == "if") {
            return Token::IF;
        } else if (currentToken == "then") {
            return Token::THEN;
        } else if (currentToken == "while") {
            return Token::WHILE;
        } else if (currentToken == "for") {
            return Token::FOR;
        } else if (currentToken == "else") {
            return Token::ELSE;
        }

        // Se não for uma palavra-chave, é um identificador
        return Token::ID;
    }

    // Caso contrário, é um caractere inválido
    currentPosition++;
    return Token::INVALID;
}

int main() {
    std::string input = "+ if else 123";

    Token token;
    while ((token = getNextToken(input)) != Token::EOF) {
        std::cout << "Token: " << token << std::endl;
    }

    return 0;
}
