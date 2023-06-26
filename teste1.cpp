#include<iostream>

using namespace std;

void imprimirValor(const int &num){
    //num *= 2;
    cout << "Valor: " << num << endl;
}

void func(int (*funcao)(int), int valor){
    int resultado = funcao(valor);
    cout << "Resultado: " << resultado << endl;
}

int dobro(int num){
    return num * 2;
}

int main(){
    int valor = 10;
    int vet[20] = {1,2,3,4,5,6,7,8,9,10};

    imprimirValor(valor);
    func(dobro, valor);
    return 0;
}