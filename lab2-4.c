#include <stdio.h>
#include <stdlib.h>

#define max_size 3

struct Node {
    int data;
    struct Node* prev;
};

struct Stack {
    struct Node* top;
    int count;
};

// Инициализация элемента стека
struct Node* init_Node(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Ошибка при выделении памяти для узла стека.\n");
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
        printf("Ошибка при выделении памяти для стека.\n");
        exit(1);
    }
    newStack->top = NULL;
    newStack->count = 0;
    return newStack;
}

// Добавление нового элемента
void push(struct Stack* stack, int data) {
    struct Node* new_Node = init_Node(data);
    if (new_Node == NULL) {
        printf("Ошибка. Переполнение стека\n");
        exit(1);
    }
    if (stack->count < max_size) {
        new_Node->prev = stack->top;
        stack->top = new_Node;
        stack->count++;
    }
    else {
        printf("Стек переполнен, невозможно внести значение: %d\n", data);
        free(new_Node); // Освобождаем память, выделенную для нового узла
    }
}

// Извлечение значения из стека
int pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Ошибка. Пустой стек\n");
        exit(1);
    }
    struct Node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->prev;
    stack->count--;
    free(temp);
    return data;
}

// Просмотр верхнего значения
int peek(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Ошибка. Пустой стек\n");
        exit(1);
    }
    return stack->top->data;
}

int main() {
    struct Stack* stack = init_Stack();
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    printf("Верхний элемент: %d\n", peek(stack));
    printf("Извлеченный элемент: %d\n", pop(stack));
    push(stack, 40);
    push(stack, 50);
    printf("Стек:\n");
    while (stack->top != NULL) {
        printf("%d\n", pop(stack));
    }
    free(stack);
    return 0;
}
