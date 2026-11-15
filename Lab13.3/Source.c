#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

// Функция для вывода слов строки в обратном порядке
void print_reverse_words(FILE* fout, char* line) {
    char* words[256]; // Массив для хранения указателей на слова
    int word_count = 0;
    char* p = line;

    // 1. Разбиваем строку на слова (разделители - пробелы, знаки препинания, перевод строки)
    char* token = strtok(p, " \t\n\r.,!?;:'\"");
    while (token != NULL) {
        words[word_count++] = token;
        token = strtok(NULL, " \t\n\r.,!?;:'\"");
    }

    // 2. Выводим слова в обратном порядке
    for (int i = word_count - 1; i >= 0; i--) {
        fprintf(fout, "%s", words[i]);
        // Добавляем пробел после слова, если это не последнее выводимое слово
        if (i > 0) {
            fprintf(fout, " ");
        }
    }
    fprintf(fout, "\n"); // Переход на новую строку после вывода всех слов
}

int main(void) {
    setlocale(LC_ALL, "Russian");

    char input_path[] = "winter.txt"; // Исходный файл
    char output_path[256];            // Файл для результата

    printf("Введите имя файла для сохранения результата: ");
    if (scanf("%255s", output_path) != 1) {
        fprintf(stderr, "Ошибка чтения имени файла.\n");
        return 1;
    }

    FILE* fin = fopen(input_path, "r");
    if (!fin) {
        perror("Не удалось открыть исходный файл winter.txt");
        return 1;
    }

    FILE* fout = fopen(output_path, "w");
    if (!fout) {
        perror("Не удалось создать файл для записи");
        fclose(fin);
        return 1;
    }

    char line[1024];
    int line_count = 0;

    // Читаем файл построчно
    while (fgets(line, sizeof(line), fin)) {
        line_count++;
        // Если строка пустая (или состоит только из пробелов/переводов строк) - просто пишем пустую строку
        if (strspn(line, " \t\n\r") == strlen(line)) {
            fprintf(fout, "\n");
            continue;
        }

        // Вызываем функцию для обработки слов в строке
        print_reverse_words(fout, line);
    }

    fclose(fin);
    fclose(fout);

    printf("\nГотово! Обработано строк: %d\n", line_count);
    printf("Результат сохранен в файл: %s\n", output_path);

    return 0;
}