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
    string lexema;
};

bool eh_identificador(const string& palavra) {
    if (palavra.empty())
        return false;
    
    char primeiro_caracter = palavra[0];
    if (!isalpha(primeiro_caracter) && primeiro_caracter != '_')
        return false;
    
    for (size_t i = 1; i < palavra.length(); i++){
        char c = palavra[i];
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}

bool eh_Nstring(const string& palavra) {
    if (palavra.empty() || palavra.length() < 2) {
        return false;
    }

    if (palavra.front() != '"' || palavra.back() != '"') {
        return false;
    }

    for (size_t i = 1; i < palavra.length() - 1; i++) {
        char c = palavra[i];
        if (isspace(c)) {
            continue; 
        }
        if (!(isalpha(c) || isdigit(c) || ispunct(c))) {
            return false;
        }
    }

    return true;
}

bool eh_numero(const string& palavra){
    if (palavra.empty())
        return false;
    
    bool tem_ponto = false;
    bool tem_digito = false;
    
    for (char c : palavra) {
        if (isdigit(c)) {
            tem_digito = true;
        } else if (c == '.') {
            if (tem_ponto)
                return false;
            tem_ponto = true;
        } else {
            return false;  
        }
    }
    
    return tem_digito && (tem_ponto || !palavra.empty());
}

Token le_token(const string& token){
    Token resultado;
    resultado.lexema = token;

    // Ignorar caracteres em branco, tabulações, quebras de linha, retorno de carro e alimentação de formulário
    string caracteres_ignorados = " \t\n\r\f";
    size_t posicao_inicial = token.find_first_not_of(caracteres_ignorados);
    if (posicao_inicial == string::npos) {
        // Se o token contiver apenas caracteres ignorados, retorne um token inválido
        resultado.tag = INVALIDO;
        return resultado;
    }
    
    // Remover caracteres ignorados do início e do final do token
    size_t posicao_final = token.find_last_not_of(caracteres_ignorados);
    string token_limpo = token.substr(posicao_inicial, posicao_final - posicao_inicial + 1);
    
    if(eh_numero(token)){
        if (token.find('.') != string::npos) {
            resultado.tag = N_REAL;
        } else {
            resultado.tag = N_INT;
        }
    } else if (token == "int") {
        resultado.tag = INT;
    } else if (token == "float") {
        resultado.tag = FLOAT;
    } else if (token == "char") {
        resultado.tag = CHAR;
    } else if (token == "bool") {
        resultado.tag = BOOL;
    } else if (token == "else") {
        resultado.tag = ELSE;
    } else if (token == "while") {
        resultado.tag = WHILE;
    } else if (token == "main") {
        resultado.tag = MAIN;
    } else if (token == "for") {
        resultado.tag = FOR;
    } else if (token == "switch") {
        resultado.tag = SWITCH;
    } else if (token == "++") {
        resultado.tag = INCREMENTO;
    } else if (token == "--") {
        resultado.tag = DECREMENTO;
    } else if (token == "=") {
        resultado.tag = ATRIBUICAO;
    } else if (token == "+" || token == "-" || token == "*" || token == "/"){
        resultado.tag = OPER_ARIT;
    } else if (token == "==") {
        resultado.tag = IGUAL;
    } else if (token == "!=") {
        resultado.tag = DIFERENTE;
    } else if (token == ".") {
        resultado.tag = PONTO;
    } else if (token == ",") {
        resultado.tag = VIRGULA;
    } else if (token == ">=") {
        resultado.tag = MAIOR_IGUAL;
    } else if (token == "<=") {
        resultado.tag = MENOR_IGUAL;
    } else if (token == ">") {
        resultado.tag = MAIOR;
    } else if (token == "<") {
        resultado.tag = MENOR;
    } else if (token == "read") {
        resultado.tag = READ;
    } else if (token == "write") {
        resultado.tag = WRITE;
    } else if (token == "if") {
        resultado.tag = IF;
    } else if (token == ";") {
        resultado.tag = PONTO_VIRGULA;
    } else if (token == "(") {
        resultado.tag = ABRE_PARENTESES;
    } else if (token == ")") {
        resultado.tag = FECHA_PARENTESES;
    } else if (token == "{") {
        resultado.tag = ABRE_CHAVES;
    } else if (token == "}") {
        resultado.tag = FECHA_CHAVES;
    } else if (token == "&&") {
        resultado.tag = AND;
    } else if (token == "||") {
        resultado.tag = OR;
    } else if(eh_Nstring(token_limpo)){
        resultado.tag = N_STRING;
    } else if (eh_identificador(token_limpo)) {
        resultado.tag = ID;
    } else {
        resultado.tag = INVALIDO;
    }
    return resultado;
}

string string_da_tag(TokenTag Tag) {
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
            Token token = le_token(str);
            cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema  << endl;
        }
    }

    return 0;
}
