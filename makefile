CC = g++
CFLAGS = -std=c++11

analisadorLexico: analisador_lexico.cpp
	$(CC) $(CFLAGS) analisador_lexico.cpp -o analisador_lexico

.PHONY: clean run

run: analisadorLexico
	./analisado_lexico teste1.cpp

clean:
	rm -f analisadorLexico
