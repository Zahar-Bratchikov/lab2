#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    double data;
    struct Node* prev;
};

struct Stack {
    struct Node* top;
    int count; 
};

// Инициализация элемента стека
struct Node* init_Node(double data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Ошибка.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    return newNode;
}

// Инициализация стека
struct Stack* init_Stack() {
    struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));
    if (newStack == NULL) {
        printf("Ошибка. \n");
        exit(1);
    }
    newStack->top = NULL;
    newStack->count = 0;
    return newStack;
}

// Добавление нового элемента
void push(struct Stack* stack, double data, int max_size) {
    struct Node* new_Node = init_Node(data);
    if (new_Node == NULL) {
        printf("Ошибка. Переполнение стека\n");
        exit(1);
    }
    if (stack->count < max_size) {
        new_Node->prev = stack->top;
        stack->top = new_Node;
        stack->count++;
    } else {
        printf("Стек переполнен, невозможно внести значение: %f\n", data);
        free(new_Node);
    }
}

// Извлечение значения из стека
double pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Ошибка. Пустой стек\n");
        exit(1);
    }
    struct Node* temp = stack->top;
    double data = temp->data;
    stack->top = temp->prev;
    stack->count--;
    free(temp);
    return data;
}

// Просмотр верхнего значения
double peek(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Ошибка. Пустой стек\n");
        exit(1);
    }
    return stack->top->data;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r"); // Открытие файла для чтения
    if (file == NULL) {
        printf("Не удалось открыть файл: %s\n", argv[1]);
        return 1;
    }

    struct Stack* stack = init_Stack();
    char ch;
    int max_size = sizeof(file);
    while ((ch = fgetc(file)) != EOF) {
        if (isdigit(ch)) {
            push(stack, ch - '0', max_size);
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            double el_2 = pop(stack);
            double el_1 = pop(stack);
            switch (ch) {
                case '+':
                    push(stack, el_1 + el_2, max_size);
                    break;
                case '-':
                    push(stack, el_1 - el_2, max_size);
                    break;
                case '*':
                    push(stack, el_1 * el_2, max_size);
                    break;
                case '/':
                    push(stack, el_1 / el_2, max_size);
                    break;
            }
        }
    }

    fclose(file);
    printf("Результат: %f\n", pop(stack));
    free(stack);

    return 0;
}
