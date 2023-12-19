#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Глобальные переменные
const char* input; // Входная строка
char lookahead;    // Текущий символ

// Прототипы функций
void expr();
void exprPrime();
void term();
void termPrime();
void factor();
void match(char expected);
void error();

// Функция для печати символа
void print(char c) {
    printf("%c", c);
}

// Функция для получения следующего символа
void getNextToken() {
    lookahead = *input++;
}

// Функция для сопоставления текущего символа с ожидаемым
void match(char expected) {
    if (lookahead == expected) {
        getNextToken();
    } else {
        error(); // В случае несоответствия вызываем функцию ошибки
    }
}

// Функция для обработки ошибок
void error() {
    printf("Error\n");
    exit(1);
}

// Начальная точка программы
int main() {
    printf("Введите инфиксное выражение: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;
    getNextToken(); // Инициализация lookahead
    expr();         // Начало анализа
    printf("\n");
    return 0;
}

// Функции для разбора грамматики
void expr() {
    term();
    exprPrime();
}

void exprPrime() {
    if (lookahead == '+') {
        match('+');
        term();
        exprPrime();
        print('+'); // Печать оператора в постфиксной записи
    } else if (lookahead == '-') {
        match('-');
        term();
        exprPrime();
        print('-'); // Печать оператора в постфиксной записи
    }
}

void term() {
    factor();
    termPrime();
}

void termPrime() {
    if (lookahead == '*') {
        match('*');
        factor();
        termPrime();
        print('*'); // Печать оператора в постфиксной записи
    } else if (lookahead == '/') {
        match('/');
        factor();
        termPrime();
        print('/'); // Печать оператора в постфиксной записи
    }
}

void factor() {
    if (isdigit(lookahead)) {
        print(lookahead); // Печать цифры в постфиксной записи
        match(lookahead);
    } else if (lookahead == '(') {
        match('(');
        expr();
        match(')');
    } else {
        error(); // Если символ не цифра и не открывающая скобка, вызываем ошибку
    }
}
