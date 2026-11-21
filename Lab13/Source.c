#include <stdio.h>
#include <string.h>
#include <ctype.h> 

int main(void)
{
    char name[50];
    char greeting[100];

    // ================= ШАГ 1: Ввод имени =================
    puts("Пожалуйста, введите ваше имя: ");
    scanf("%49s", name); 

    // ================= 1.2: Имя заглавными буквами =================
 
    for (int i = 0; name[i] != '\0'; i++) {
        name[i] = toupper((unsigned char)name[i]);
    }

    // ================= ШАГ 3: Формирование приветствия =================
   
    strcpy(greeting, "Привет, ");
   
    strcat(greeting, name);

    // ================= 1.3: Длина строки 40 символов =================
 
    int current_len = strlen(greeting);
    int target_len = 40;
    int exclamation_count = target_len - current_len;

    
    if (exclamation_count > 0) {
       
        for (int i = 0; i < exclamation_count; i++) {
            
            strcat(greeting, "!");
        }
    } else {
        puts("Внимание: имя слишком длинное, лимит в 40 символов превышен!");
    }

    // ================= ШАГ 4: Вывод результата =================
    puts("--- Результат ---");
    puts(greeting);


    printf("Фактическая длина строки: %zu\n", strlen(greeting));

    return 0;
}
