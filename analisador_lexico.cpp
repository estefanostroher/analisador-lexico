#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>

using namespace std;

enum TokenTag{
    ID,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    BOOL,
    REAL,
    STRING,
    OPER_ARIT,
    OPER_SAIDA,
    OPER_ENTRADA,
    ATRIBUICAO,
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
    COUT,
    CIN,
    ENDL,
    DO,
    RETURN,
    VOID,
    CLASS,
    PUBLIC,
    PRIVATE,
    PROTECTED,
    INCREMENTO,
    DECREMENTO,
    FOR,
    SWITCH,
    MAIN,
    AND,
    OR,
    N_INT,
    N_REAL,
    N_BOOL,
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


bool eh_Nstring(const std::string& palavra) {
    if (palavra.empty() || palavra.length() < 2) {
        return false;
    }

    if (palavra.front() != '"' || palavra.back() != '"') {
        return false;
    }

    for (size_t i = 1; i < palavra.length() - 1; i++) {
        char c = palavra[i];
        if (!(isalpha(c) || !isdigit(c) || !ispunct(c) || !isspace(c))) {
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

bool eh_bool(const string& palavra){
    if (palavra.empty())
        return false;
    
    return (palavra == "true" || palavra == "false");
}

Token le_token(const string& token){
    Token resultado;

    if(eh_numero(token)){
        if (token.find('.') != string::npos) {
            resultado.tag = N_REAL;
        } else {
            resultado.tag = N_INT;
        }
    } else if(eh_bool(token)){
        resultado.tag = N_BOOL;
    } else if (token == "int") {
        resultado.tag = INT;
    } else if (token == "float") {
        resultado.tag = FLOAT;
    } else if (token == "double") {
        resultado.tag = DOUBLE; 
    } else if (token == "char") {
        resultado.tag = CHAR;
    } else if (token == "bool") {
        resultado.tag = BOOL;
    } else if (token == "string") {
        resultado.tag = STRING;
    } else if (token == "cout") {
        resultado.tag = COUT;
    } else if (token == "cin") {
        resultado.tag = CIN;
    } else if (token == "endl") {
        resultado.tag = ENDL; 
    } else if (token == "else") {
        resultado.tag = ELSE;
    } else if (token == "while") {
        resultado.tag = WHILE;
    } else if (token == "do") {
        resultado.tag = DO;
    } else if (token == "void") {
        resultado.tag = VOID;
    } else if (token == "class") {
        resultado.tag = CLASS;
    } else if (token == "public") {
        resultado.tag = PUBLIC;
    } else if (token == "private") {
        resultado.tag = PRIVATE;
    } else if (token == "protected") {
        resultado.tag = PROTECTED;
    } else if (token == "main") {
        resultado.tag = MAIN;
    } else if (token == "return") {
        resultado.tag = RETURN;
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
    } else if (token == ">>") {
        resultado.tag = OPER_ENTRADA;
    } else if (token == "<<") {
        resultado.tag = OPER_SAIDA;
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
    } else if (eh_Nstring(token)){
        resultado.tag = N_STRING;
    } else if (eh_identificador(token)) {
        resultado.tag = ID;
    } else {
        resultado.tag = INVALIDO;
    }
    resultado.lexema = token;
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
        case N_BOOL:
            return "N_BOOL";
        case N_STRING:
            return "N_STRING";
        case INT:
            return "INT";
        case FLOAT:
            return "FLOAT";
        case DOUBLE:
            return "DOUBLE";
        case CHAR:
            return "CHAR";
        case BOOL:
            return "BOOL";
        case STRING:
            return "STRING";
        case COUT:
            return "COUT";
        case CIN:
            return "CIN";
        case ENDL:
            return "ENDL";
        case ATRIBUICAO:
            return "ATRIBUIÇÃO";
        case ELSE:
            return "ELSE";
        case WHILE:
            return "WHILE";
        case DO:
            return "DO";
        case VOID:
            return "VOID";
        case CLASS:
            return "CLASS";
        case PUBLIC:
            return "PUBLIC";
        case PRIVATE:
            return "PRIVATE";
        case PROTECTED:
            return "PROTECTED";
        case FOR:
            return "FOR";
        case SWITCH:
            return "SWITCH";
        case MAIN:
            return "MAIN";
        case RETURN:
            return "RETURN";
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
            return "OPERADOR ARITMÉTICO";
       case OPER_ENTRADA:
            return "OPERADOR DE ENTRADA";
       case OPER_SAIDA:
            return "OPERADOR DE SAIDA";
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
        case ABRE_CHAVES:
            return "ABRE CHAVES";
        case FECHA_CHAVES:
            return "FECHA CHAVES";
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <nome_do_arquivo>" << endl;
        return 1;
    }

    ifstream arquivo(argv[1]);

    if (arquivo.is_open()) {
        string linha;

        while (getline(arquivo, linha)) {
            istringstream iss(linha);
            char c;
            string str;

            while (iss.get(c)) {
                if(c == '"'){
                    while(true){
                        if(eh_Nstring(str)){
                            Token token = le_token(str);
                            cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                            str.clear();
                            break;
                        }
                    str += c;
                    iss.get(c);
                    continue;
                    }
                } else if (isspace(c)) {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                } else if (c == ';' || c == ',' || c == '(' || c == ')' || c == '*' || c == '/' || c == '{' || c == '}') {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                    Token token = le_token(string(1, c));
                    cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                } else if (c == '=') {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                    if (iss.peek() == '=') {
                        iss.get(c);
                        Token token = le_token("==");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    } else {
                        Token token = le_token("=");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    }
                } else if (c == '>') {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                    if (iss.peek() == '=') {
                        iss.get(c);
                        Token token = le_token(">=");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    } else if (c == '>') {
                        iss.get(c);
                        Token token = le_token(">>");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl; 
                    } else {
                        Token token = le_token(">");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    }
                } else if (c == '<') {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                    if (iss.peek() == '=') {
                        iss.get(c);
                        Token token = le_token("<=");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    } else if (c == '<') {
                        iss.get(c);
                        Token token = le_token("<<");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl; 
                    }else {
                        Token token = le_token("<");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    }
                } else if (c == '!') {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                    if (iss.peek() == '=') {
                        iss.get(c);
                        Token token = le_token("!=");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    } else {
                        Token token = le_token("!");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    }
                } else if (c == '+') {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                    if (iss.peek() == '+') {
                        iss.get(c);
                        Token token = le_token("++");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    } else {
                        Token token = le_token("+");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    }
                } else if (c == '-') {
                    if (!str.empty()) {
                        Token token = le_token(str);
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                        str.clear();
                    }
                    if (iss.peek() == '-') {
                        iss.get(c);
                        Token token = le_token("--");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    } else {
                        Token token = le_token("-");
                        cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
                    }
                } else {
                    str += c;
                }
            }

            if (!str.empty()) {
                Token token = le_token(str);
                cout << "Token: " << string_da_tag(token.tag) << ", Lexema: " << token.lexema << endl;
            }
        }

        arquivo.close();
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }

}
