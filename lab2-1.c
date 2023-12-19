#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long int randomGenerator(void) {
    return rand() % 100; // Генерация случайного числа в диапазоне [0, 99]
}

int main(int argc, char *argv[]) {
    // Проверка наличия аргумента командной строки
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <название_файла>\n", argv[0]);
        return 1;
    }

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Запрос у пользователя ввода размера массива
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    // Создание и заполнение массива случайными числами
    int *array = malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        array[i] = randomGenerator();
        printf("array[%d]=%d\n", i, array[i]);
    }

    // Открытие файла для записи в обратном порядке
    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла\n");
        free(array);
        return 1;
    }

    // Запись элементов массива в обратном порядке в файл
    for (int i = size - 1; i >= 0; i--) {
        fprintf(file, "array[%d]=%d\n", i, array[i]);
    }

    // Закрытие файла и освобождение выделенной памяти
    fclose(file);
    free(array);

    return 0;
}
