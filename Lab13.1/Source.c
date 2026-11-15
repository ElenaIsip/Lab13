#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

// Функция для формирования нового имени файла (например, input.dat -> inputvariant5.dat)
void make_new_filename(const char* old_name, int variant, char* new_name) {
    // Ищем последнюю точку в имени файла
    const char* dot = strrchr(old_name, '.');
    if (dot != NULL) {
        // Копируем имя без расширения, добавляем суффикс и оригинальное расширение
        int len = dot - old_name;
        strncpy(new_name, old_name, len);
        new_name[len] = '\0';
        sprintf(new_name + len, "variant%d%s", variant, dot);
    }
    else {
        // Если расширения нет
        sprintf(new_name, "%svariant%d", old_name, variant);
    }
}

int main(void) {
    setlocale(LC_ALL, "Russian");

    char in_filename[256];
    char out_filename[256];
    int variant;

    // 1. Запрос имени файла у пользователя
    printf("Введите имя исходного файла (например, input.dat): ");
    if (scanf("%255s", in_filename) != 1) return 1;

    printf("Введите номер варианта преобразования (1-12): ");
    if (scanf("%d", &variant) != 1) return 1;

    // 2. Открытие исходного файла
    FILE* in = fopen(in_filename, "r");
    if (in == NULL) {
        printf("Ошибка: не удалось открыть файл '%s'.\n", in_filename);
        return 1;
    }

    // 3. Формирование имени выходного файла и его открытие
    make_new_filename(in_filename, variant, out_filename);
    FILE* out = fopen(out_filename, "w");
    if (out == NULL) {
        printf("Ошибка: не удалось создать файл '%s'.\n", out_filename);
        fclose(in);
        return 1;
    }

    printf("Результат будет записан в файл: %s\n", out_filename);

    double a;         // текущее число
    double prev = 0;  // для варианта 6 (предыдущее число)
    int count = 0;    // порядковый номер числа (для вариантов 7 и 8)

    // 4. Чтение, обработка и запись чисел
    while (fscanf(in, "%lf", &a) == 1) {
        count++;

        // Если в файле числа записаны по одному в строке, можно прочитать 
        // и отбросить остаток строки, но fscanf("%lf") и так пропускает пробелы и переносы.

        switch (variant) {
        case 1: 
            if (count % 2 == 0) a = 0;
            fprintf(out, "%g\n", a);
            break;

        case 2: 
            if (a > 100) a /= 2.0;
            fprintf(out, "%g\n", a);
            break;

        case 3: 
            if (a > 0) a /= 4.0;
            fprintf(out, "%g\n", a);
            break;

        case 4: 
            a = round(a * 0.3);
            fprintf(out, "%g\n", a);
            break;

        case 5: 
            a = a - 1000;
            fprintf(out, "%g\n", a);
            break;

        case 6: 
         
            if (count == 1) {
                fprintf(out, "%g\n", a);
            }
            else {
                fprintf(out, "%g\n", (a + prev) / 2.0);
            }
            prev = a;
            break;

        case 7: 
            a = a + count;
            fprintf(out, "%g\n", a);
            break;

        case 8: 
            if (count % 3 == 0) a *= 2.0;
            fprintf(out, "%g\n", a);
            break;

        case 9: 
            if (count % 4 == 0) a /= 2.0;
            fprintf(out, "%g\n", a);
            break;

        case 10: 
            a = ceil(a * 1.66);
            fprintf(out, "%g\n", a);
            break;

        case 11:
            a = a * a;
            fprintf(out, "%g\n", a);
            break;

        case 12: 
            if (a > 0) fprintf(out, "положит\n");
            else if (a < 0) fprintf(out, "отриц\n");
            else fprintf(out, "ноль\n");
            break;

        default:
            printf("Неизвестный вариант. Записываем числа без изменений.\n");
            fprintf(out, "%g\n", a);
            break;
        }
    }

   
    fclose(in);
    fclose(out);

    printf("Обработка успешно завершена!\n");
    return 0;
}