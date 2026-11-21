#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char name[50];
    char greeting[100];

    // Шаг 1: Ввод имени
    puts("Пожалуйста, введите ваше имя: ");
    scanf("%49s", name);

    // Шаг 2: Замена буквы 'а' (и 'А') на '@'
    
    for (int i = 0; name[i] != '\0'; i++) {
        
        if (name[i] == 'а' || name[i] == 'А') {
            name[i] = '@';
        }
    }

    // Шаг 3: Формирование приветствия
    strcpy(greeting, "Привет, ");
    strcat(greeting, name);
    strcat(greeting, "!");

    // Шаг 4: Вывод результата
    puts(greeting);

    return 0;
}
