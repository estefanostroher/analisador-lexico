# Analisador Léxico

O analisador léxico é uma parte essencial de um compilador, responsável por analisar o código-fonte e dividir em unidades léxicas chamadas tokens. Cada token representa uma sequência de caracteres com significado semântico, como palavras-chave, identificadores, números, operadores, delimitadores, etc.


O código do analisador léxico possui as seguintes funções:

- bool eh_identificador(const string& palavra): Verifica se uma string é um identificador válido. Um identificador começa com uma letra ou um sublinhado, seguido por letras, dígitos ou sublinhados.

- bool eh_Nstring(const string& palavra): Verifica se uma string é uma string delimitada por aspas duplas. A string deve conter apenas caracteres alfanuméricos, pontuação ou espaços.

- bool eh_numero(const string& palavra): Verifica se uma string é um número válido. Um número pode ser um inteiro ou um número de ponto flutuante.

- bool eh_bool(const string& palavra): Verifica se uma string é um valor booleano válido, ou seja, "true" ou "false".

- Token le_token(const string& token): Recebe uma string como entrada e retorna um objeto Token com a tag e o lexema correspondentes. A função verifica o tipo de lexema com base nas funções de validação mencionadas anteriormente.

- string string_da_tag(TokenTag Tag): Converte uma tag de token em uma string legível para impressão. Essa função é usada para exibir o tipo de lexema no console.

- Função main: A função principal do programa. Lê um arquivo de código-fonte fornecido como argumento de linha de comando. O código-fonte é lido linha por linha. Para cada linha, o analisador léxico percorre os caracteres e forma os tokens chamando a função le_token(). Os tokens são impressos no console com suas respectivas tags e lexemas.


Compilação e Execução

Para compilar o código do analisador léxico, siga as instruções abaixo:

- Certifique-se de ter um compilador C++ instalado, como o GCC.
- Salve o código do analisador léxico em um arquivo com a extensão .cpp, por exemplo, analisador_lexico.cpp.
- Abra um terminal e navegue até o diretório onde o arquivo .cpp está localizado.

Execute o seguinte comando para compilar o código:
    
    g++ analisador_lexico.cpp -o analisador_lexico

Isso compilará o código e criará um arquivo executável chamado analisador_lexico no mesmo diretório. Agora, você pode executar o analisador léxico fornecendo um arquivo de código-fonte como argumento:

    ./analisador_lexico <nome_do_arquivo>

Substitua <nome_do_arquivo> pelo caminho ou nome do arquivo de código-fonte que você deseja analisar. Os tokens encontrados serão exibidos no console, juntamente com suas tags e lexemas correspondentes.
    

Também é possível utilizar o makefile, apenas certifique-se de navegar ate o diretório onde o arquivo .cpp está localizado, segue as instruções abaixo:

    make run analisador_lexico

Os tokens encontrados serão exibidos no console, juntamente com suas tags e lexemas correspondentes.
