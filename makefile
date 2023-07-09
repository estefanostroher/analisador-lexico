CC = g++
CFLAGS = -std=c++11

analisadorLexico: analisadorLexico.cpp
	$(CC) $(CFLAGS) analisadorLexico.cpp -o analisadorLexico

.PHONY: clean run

run: analisadorLexico
	./analisadorLexico teste1.cpp

clean:
	rm -f analisadorLexico
