#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

bool e_digito(char *str){
    if(strlen(str) == 0)
        return false;
    
    int tam = strlen(str);

    for(int i = 0; i < tam; i++){
        if(str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' ||
        str[i] == '6'|| str[i] == '7' || str[i] == '8' || str[i] == '9')
            return true;
    }
    return false;
}

bool caracteres_especiais(char *str){
    if(strlen(str) == 0)
        return false;

    int tam = strlen(str);

    for(int i = 0; i < tam; i++){
        if(str[i] == '!' || str[i] == '@' || str[i] == '#' || str[i] == '$' || str[i] == '%' || str[i] == '|' ||
        str[i] == '&' || str[i] == '*' || str[i] == '(' || str[i] == ')' || str[i] == '-' || str[i] == '_' ||
        str[i] == '=' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}' || str[i] == '!' || 
        str[i] == '^' || str[i] == '~' || str[i] == ';' || str[i] == ':' || str[i] == '<' || str[i] == '>' ||
        str[i] == ',' || str[i] == '.' || str[i] == '/')
            return true;
    }
    return false;
}

int main(){
    char str[] = "lalala3lalala";
    bool teste = e_digito(str);

    cout << "O token possui pelo menos " << teste << " digito" << endl; 

    return 0;
}
