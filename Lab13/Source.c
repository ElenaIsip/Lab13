#include <stdio.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "Russian");
   

    FILE* in;
    int a;
    int sum = 0;
    int n = 0;
    double avg;

    in = fopen("numbers.txt", "r");
    if (in == NULL)
    {
        printf("Ошибка: не удалось открыть файл numbers.txt\n");
        return 1;
    }

    while (!feof(in))
    {
        if (fscanf(in, "%d", &a) == 1)
        {
            sum += a;
            n++;
        }
    }
    fclose(in);

    if (n > 0)
    {
        avg = (double)sum / n;
        printf("Количество чисел: %d\n", n);
        printf("Сумма чисел: %d\n", sum);
        printf("Среднее арифметическое: %.2f\n", avg);
    }
    else
    {
        printf("Файл не содержит целых чисел.\n");
    }

    return 0;
}
