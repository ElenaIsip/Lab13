#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

int main(void) {

    setlocale(LC_ALL, "Russian");
    char input_path[256];
    char output_path[512];

    printf("Введите имя входного файла: ");
    if (scanf("%255s", input_path) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла\n");
        return 1;
    }

    FILE* fin = fopen(input_path, "r");
    if (!fin) {
        perror("Не удалось открыть входной файл");
        return 1;
    }

    /* Формируем имя выходного файла:
       <имя>_x1.66_ceil<расширение> */
    const char* dot = strrchr(input_path, '.');
    if (dot) {
        size_t base_len = (size_t)(dot - input_path);
        snprintf(output_path, sizeof(output_path),
            "%.*s_x1.66_ceil%s", (int)base_len, input_path, dot);
    }
    else {
        snprintf(output_path, sizeof(output_path),
            "%s_x1.66_ceil", input_path);
    }

    FILE* fout = fopen(output_path, "w");
    if (!fout) {
        perror("Не удалось открыть выходной файл");
        fclose(fin);
        return 1;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), fin)) {
        /* убираем возможные пробелы/переводы строк */
        char* p = line;
        while (*p == ' ' || *p == '\t') p++;

        /* пропускаем пустые строки */
        if (*p == '\0' || *p == '\n' || *p == '\r') continue;

        char* endptr = NULL;
        double value = strtod(p, &endptr);

        if (endptr == p || (*endptr != '\0' && *endptr != '\n' &&
            *endptr != '\r' && *endptr != ' ' && *endptr != '\t')) {
            fprintf(stderr, "Пропущена некорректная строка: %s", line);
            continue;
        }

        double result = ceil(value * 1.66);
        fprintf(fout, "%.0f\n", result);
        count++;
    }

    fclose(fin);
    fclose(fout);

    printf("Обработано чисел: %d\n", count);
    printf("Результат записан в файл: %s\n", output_path);
    return 0;
}
