#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для обмена элементов в сортировке
void swap(double *xp, double *yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Функция пузырьковой сортировки
void bubbleSort(double arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Вызов функции для обмена элементов
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // Проверка на правильное количество аргументов командной строки
    if (argc != 2)
    {
        printf("Используйте: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    printf("Введите размер массива:\n");
    int sizeMas;
    scanf("%d", &sizeMas);

    // Объявление массива чисел с плавающей точкой
    double mas[sizeMas];

    printf("Массив со случайными числами:\n");
    srand(time(NULL));
    for (int i = 0; i < sizeMas; i++)
    {
        // Заполнение массива случайными числами от 0 до 1
        mas[i] = (double)rand() / RAND_MAX;
        printf("mas[%d]=%f\n", i, mas[i]);
    }

    // Вызов функции сортировки пузырьком
    bubbleSort(mas, sizeMas);

    // Открытие файла для записи
    FILE *file;
    file = fopen(argv[1], "w");
    if (file == NULL)
    {
        // Вывод сообщения об ошибке, если файл не удалось открыть
        printf("Не удалось открыть файл для записи.\n");
        return 1;
    }

    // Запись отсортированного массива в файл
    for (int i = 0; i < sizeMas; i++)
    {
        fprintf(file, "mas[%d]=%f\n", i, mas[i]);
    }

    // Закрытие файла
    fclose(file);

    return 0;
}
