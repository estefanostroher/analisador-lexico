#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    DO,
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

bool eh_bool(const string& palavra){
    if (palavra.empty())
        return false;
    
    return (palavra == "true" || palavra == "false");
}

Token le_token(const string& token){
    Token resultado;

    string caracteres_ignorados = " \t\n\r\f";
    size_t posicao_inicial = token.find_first_not_of(caracteres_ignorados);
    if (posicao_inicial == string::npos) {
        resultado.tag = INVALIDO;
        return resultado;
    }

    size_t posicao_final = token.find_last_not_of(caracteres_ignorados);
    string token_limpo = token.substr(posicao_inicial, posicao_final - posicao_inicial + 1);

    if(eh_numero(token_limpo)){
        if (token.find('.') != string::npos) {
            resultado.tag = N_REAL;
        } else {
            resultado.tag = N_INT;
        }
    } else if(eh_bool(token_limpo)){
        resultado.tag = N_BOOL;
    } else if (token_limpo == "int") {
        resultado.tag = INT;
    } else if (token_limpo == "float") {
        resultado.tag = FLOAT;
    } else if (token_limpo == "char") {
        resultado.tag = CHAR;
    } else if (token_limpo == "bool") {
        resultado.tag = BOOL;
    } else if (token_limpo == "string") {
        resultado.tag = STRING;
    } else if (token_limpo == "else") {
        resultado.tag = ELSE;
    } else if (token_limpo == "while") {
        resultado.tag = WHILE;
    } else if (token_limpo == "do") {
        resultado.tag = DO;
    } else if (token_limpo == "main") {
        resultado.tag = MAIN;
    } else if (token_limpo == "for") {
        resultado.tag = FOR;
    } else if (token_limpo == "switch") {
        resultado.tag = SWITCH;
    } else if (token_limpo == "++") {
        resultado.tag = INCREMENTO;
    } else if (token_limpo == "--") {
        resultado.tag = DECREMENTO;
    } else if (token_limpo == "=") {
        resultado.tag = ATRIBUICAO;
    } else if (token_limpo == "+" || token_limpo == "-" || token_limpo == "*" || token_limpo == "/"){
        resultado.tag = OPER_ARIT;
    } else if (token_limpo == "==") {
        resultado.tag = IGUAL;
    } else if (token_limpo == "!=") {
        resultado.tag = DIFERENTE;
    } else if (token_limpo == ".") {
        resultado.tag = PONTO;
    } else if (token_limpo == ",") {
        resultado.tag = VIRGULA;
    } else if (token_limpo == ">=") {
        resultado.tag = MAIOR_IGUAL;
    } else if (token_limpo == "<=") {
        resultado.tag = MENOR_IGUAL;
    } else if (token_limpo == ">") {
        resultado.tag = MAIOR;
    } else if (token_limpo == "<") {
        resultado.tag = MENOR;
    } else if (token_limpo == "read") {
        resultado.tag = READ;
    } else if (token_limpo == "write") {
        resultado.tag = WRITE;
    } else if (token_limpo == "if") {
        resultado.tag = IF;
    } else if (token_limpo == ";") {
        resultado.tag = PONTO_VIRGULA;
    } else if (token_limpo == "(") {
        resultado.tag = ABRE_PARENTESES;
    } else if (token_limpo == ")") {
        resultado.tag = FECHA_PARENTESES;
    } else if (token_limpo == "{") {
        resultado.tag = ABRE_CHAVES;
    } else if (token_limpo == "}") {
        resultado.tag = FECHA_CHAVES;
    } else if (token_limpo == "&&") {
        resultado.tag = AND;
    } else if (token_limpo == "||") {
        resultado.tag = OR;
    } else if(eh_Nstring(token_limpo)){
        resultado.tag = N_STRING;
    } else if (eh_identificador(token_limpo)) {
        resultado.tag = ID;
    } else {
        resultado.tag = INVALIDO;
    }
    resultado.lexema = token_limpo;
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
        case CHAR:
            return "CHAR";
        case BOOL:
            return "BOOL";
        case STRING:
            return "STRING";
        case ATRIBUICAO:
            return "ATRIBUIÇÃO";
        case ELSE:
            return "ELSE";
        case WHILE:
            return "WHILE";
        case DO:
            return "DO";
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
                if (isspace(c)) {
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
                    } else {
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

    return 0;
}
