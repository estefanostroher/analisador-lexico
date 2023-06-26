#ifndef TOKEN_H
#define TOKEN_H

enum Token{
    IF,
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
#endif 

void e_digito();
void e_caracter();
void e_operador();
