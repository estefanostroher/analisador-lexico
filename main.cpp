#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <ctype.h>

using namespace std;

enum TokenTag{
    ID,
    INT,
    FLOAT,
    CHAR,
    BOOL,
    REAL,
    STRING,
    OPER_ARIT,
    ATRIBUICAO,
    SOMA,
    SUB,
    MUL,
    DIV,
    READ,
    WRITE,
    IF,
    MAIOR,
    MENOR,
    MAIOR_IGUAL,
    MENOR_IGUAL,
    PONTO_VIRGULA,
    ABRE_CHAVES,   
    FECHA_CHAVES,  
    ABRE_PARENTESES,
    FECHA_PARENTESES,
    ELSE,    
    WHILE,   
    INCREMENTO,
    DECREMENTO,
    FOR,
    SWITCH,
    MAIN,
    AND,
    OR,
    N_INT,
    N_REAL,
    N_STRING,
    IGUAL,
    DIFERENTE,
    PONTO,
    VIRGULA,  
    INVALIDO
};

struct Token {
    TokenTag tag;
    string lexeme;
};

bool isIdentifier(const string& str) {
    if (str.empty())
        return false;
    
    char firstChar = str[0];
    if (!isalpha(firstChar) && firstChar != '_')
        return false;
    
    for (size_t i = 1; i < str.length(); i++){
        char c = str[i];
        if (!isalnum(c) && c != '_')
            return false;
    }
    
    return true;
}

bool isNstring(const string& input) {
    if (input.empty() || input.length() < 2) {
        return false;
    }

    if (input.front() != '"' || input.back() != '"') {
        return false;
    }

    for (size_t i = 1; i < input.length() - 1; i++) {
        char c = input[i];
        if (isspace(c)) {
            continue; 
        }
        if (!(isalpha(c) || isdigit(c) || ispunct(c))) {
            return false;
        }
    }

    return true;
}

bool isNumber(const string& str){
    if (str.empty())
        return false;
    
    bool hasDot = false;
    bool hasDigit = false;
    
    for (char c : str) {
        if (isdigit(c)) {
            hasDigit = true;
        } else if (c == '.') {
            if (hasDot)
                return false;
            hasDot = true;
        } else {
            return false;  
        }
    }
    
    return hasDigit && (hasDot || !str.empty());
}

Token le_Token(const string& token){
    Token result;
    result.lexeme = token;

    // Ignorar caracteres em branco, tabulações, quebras de linha, retorno de carro e alimentação de formulário
    string ignoredCharacters = " \t\n\r\f";
    size_t startPos = token.find_first_not_of(ignoredCharacters);
    if (startPos == string::npos) {
        // Se o token contiver apenas caracteres ignorados, retorne um token inválido
        result.tag = INVALIDO;
        return result;
    }
    
    // Remover caracteres ignorados do início e do final do token
    size_t endPos = token.find_last_not_of(ignoredCharacters);
    string cleanedToken = token.substr(startPos, endPos - startPos + 1);
    
    if(isNumber(token)){
        if (token.find('.') != string::npos) {
            result.tag = N_REAL;
        } else {
            result.tag = N_INT;
        }
    } else if (token == "int") {
        result.tag = INT;
    } else if (token == "float") {
        result.tag = FLOAT;
    } else if (token == "char") {
        result.tag = CHAR;
    } else if (token == "bool") {
        result.tag = BOOL;
    } else if (token == "else") {
        result.tag = ELSE;
    } else if (token == "while") {
        result.tag = WHILE;
    } else if (token == "main") {
        result.tag = MAIN;
    } else if (token == "for") {
        result.tag = FOR;
    } else if (token == "switch") {
        result.tag = SWITCH;
    } else if (token == "++") {
        result.tag = INCREMENTO;
    } else if (token == "--") {
        result.tag = DECREMENTO;
    } else if (token == "=") {
        result.tag = ATRIBUICAO;
    } else if (token == "+") {
        result.tag = OPER_ARIT;
    } else if (token == "-") {
        result.tag = OPER_ARIT;
    } else if (token == "*") {
        result.tag = OPER_ARIT;
    } else if (token == "/") {
        result.tag = OPER_ARIT;
    } else if (token == "==") {
        result.tag = IGUAL;
    } else if (token == "!=") {
        result.tag = DIFERENTE;
    } else if (token == ".") {
        result.tag = PONTO;
    } else if (token == ",") {
        result.tag = VIRGULA;
    } else if (token == ">=") {
        result.tag = MAIOR_IGUAL;
    } else if (token == "<=") {
        result.tag = MENOR_IGUAL;
    } else if (token == ">") {
        result.tag = MAIOR;
    } else if (token == "<") {
        result.tag = MENOR;
    } else if (token == "read") {
        result.tag = READ;
    } else if (token == "write") {
        result.tag = WRITE;
    } else if (token == "if") {
        result.tag = IF;
    } else if (token == ";") {
        result.tag = PONTO_VIRGULA;
    } else if (token == "(") {
        result.tag = ABRE_PARENTESES;
    } else if (token == ")") {
        result.tag = FECHA_PARENTESES;
    } else if (token == "{") {
        result.tag = ABRE_CHAVES;
    } else if (token == "}") {
        result.tag = FECHA_CHAVES;
    } else if (token == "&&") {
        result.tag = AND;
    } else if (token == "||") {
        result.tag = OR;
    } else if(isNstring(cleanedToken)){
        result.tag = N_STRING;
    } else if (isIdentifier(cleanedToken)) {
        result.tag = ID;
    } else {
        result.tag = INVALIDO;
    }
    return result;
}

string tokenTagToString(TokenTag Tag) {
    switch (Tag) {
        case ID:
            return "ID";
        case N_INT:
            return "N_INT";
        case N_REAL:
            return "N_REAL";
        case N_STRING:
            return "N_STRING";
        case INT:
            return "INT";
        case FLOAT:
            return "FLOAT";
        case CHAR:
            return "CHAR";
        case BOOL:
            return "BOOL";
        case ATRIBUICAO:
            return "ATRIBUIÇÃO";
        case ELSE:
            return "ELSE";
        case WHILE:
            return "WHILE";
        case FOR:
            return "FOR";
        case SWITCH:
            return "SWITCH";
        case MAIN:
            return "MAIN";
        case INCREMENTO:
            return "INCREMENTO";
        case DECREMENTO:
            return "DECREMENTO";
        case IGUAL:
            return "IGUAL";
        case DIFERENTE:
            return "DIFERENTE";
        case PONTO:
            return "PONTO";
        case VIRGULA:
            return "VIRGULA";
        case OPER_ARIT:
            return "OPER_ARIT";
        case READ:
            return "READ";
        case WRITE:
            return "WRITE";
        case IF:
            return "IF";
        case MAIOR:
            return "MAIOR";
        case MENOR:
            return "MENOR";
        case MAIOR_IGUAL:
            return "MAIOR IGUAL";
        case MENOR_IGUAL:
            return "MENOR IGUAL";
        case PONTO_VIRGULA:
            return "PONTO VIRGULA";
        case ABRE_PARENTESES:
            return "ABRE PARENTESES";
        case FECHA_PARENTESES:
            return "FECHA PARENTESES";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case INVALIDO:
            return "INVALIDO";
        default:
            return "NÃO ENCONTRADO";
    }
}

int main() {
    string line;
    while (getline(cin, line)){
        istringstream iss(line);
        string str;
        while (iss >> str) {
            Token token = le_Token(str);
            cout << "Token: " << tokenTagToString(token.tag) << ", Lexema: " << token.lexeme  << endl;
        }
    }

    return 0;
}
