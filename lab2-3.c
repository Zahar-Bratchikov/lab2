#include <stdio.h>

struct goods
{
    char name[128];
    float price;
};

// Функция для обмена элементов в сортировке
void swap(struct goods *xp, struct goods *yp)
{
    struct goods temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Функция пузырьковой сортировки
void bubbleSort(struct goods *mas, int countString)
{
    int i, j;
    for (i = 0; i < countString - 1; i++)
    {
        for (j = 0; j < countString - i - 1; j++)
        {
            if (mas[j].price > mas[j + 1].price)
            {
                swap(&mas[j], &mas[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *inputFile;
    FILE *outputFile;

    // Открываем входной файл для чтения
    inputFile = fopen(argv[1], "r");

    // Проверка на успешное открытие файла
    if (inputFile == NULL)
    {
        printf("Ошибка при открытии входного файла.\n");
        return 1;
    }

    int countString = 0;
    char ch;

    // Подсчет количества строк в файле
    while ((ch = fgetc(inputFile)) != EOF)
    {
        if (ch == '\n')
        {
            countString++;
        }
    }

    // Создание массива структур для хранения товаров
    struct goods shop[countString];
    int i = 0;

    // Сброс указателя в начало файла
    fseek(inputFile, 0, SEEK_SET);

    // Заполнение массива данными из файла
    while (i < countString && fscanf(inputFile, "%127s %f", shop[i].name, &shop[i].price) == 2)
    {
        i++;
    }

    // Закрываем входной файл
    fclose(inputFile);

    // Сортировка массива товаров по цене
    bubbleSort(shop, countString);

    // Открываем выходной файл для записи
    outputFile = fopen(argv[2], "w");

    // Проверка на успешное открытие выходного файла
    if (outputFile == NULL)
    {
        printf("Ошибка при открытии выходного файла.\n");
        return 1;
    }

    // Запись отсортированных данных в выходной файл
    for (int c = 0; c < countString; c++)
    {
        fprintf(outputFile, "%s %.2f\n", shop[c].name, shop[c].price);
    }

    // Закрываем выходной файл
    fclose(outputFile);

    printf("Программа успешно выполнена!\n");

    return 0;
}
