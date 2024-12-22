#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 20
#define MAX_SYMBOLS 10
#define MAX_INPUT 100

// تعريف قاعدة النحو
typedef struct {
    char head;                  // الرمز الرئيسي للقاعدة (مثل A)
    char body[MAX_SYMBOLS];     // الجزء الأيمن للقاعدة (مثل aA)
} Rule;

Rule rules[MAX_RULES];          // مصفوفة لتخزين القواعد
int rule_count = 0;             // عدد القواعد

char input[MAX_INPUT];          // الإدخال النصي
int position = 0;               // مؤشر النص المدخل

// دالة للتحقق من الحرف الحالي
char lookahead() {
    return input[position];
}

// دالة للطباعة بمسافات من أجل شجرة التحليل
void print_indent(int level) {
    int i;
    for (i = 0; i < level; i++) {
        printf("  ");
    }
}

// دالة لفحص القواعد البسيطة
int is_simple_rule(char head, char *body) {
    int i;
    if (!isupper(head)) return 0;  // يجب أن يكون الرأس حرف كبير (Non-terminal)
    for (i = 0; i < strlen(body); i++) {
        if (!isalpha(body[i]) && body[i] != '\0') {
            return 0;  // يجب أن تتكون من حروف فقط (terminals أو non-terminals)
        }
    }
    return 1;
}

// دالة لإضافة قاعدة جديدة
void add_rule() {
    if (rule_count >= MAX_RULES) {
        printf("Error: Maximum rule limit reached!\n");
        return;
    }

    char head;
    char body[MAX_SYMBOLS];
    printf("Enter rule (format: Head Body): ");
    scanf(" %c %s", &head, body);

    if (!is_simple_rule(head, body)) {
        printf("Error: Rule %c -> %s is not a simple rule.\n", head, body);
        return;
    }

    rules[rule_count].head = head;
    strcpy(rules[rule_count].body, body);
    rule_count++;
    printf("Rule added successfully!\n");
}

// دالة لعرض القواعد الحالية
void display_rules() {
    printf("\nCurrent Grammar Rules:\n");
    int i;
    for (i = 0; i < rule_count; i++) {
        printf("%d. %c -> %s\n", i + 1, rules[i].head, rules[i].body);
    }
    printf("\n");
}

// دالة للتحقق من الحرف المتوقع
void match(char expected) {
    if (lookahead() == expected) {
        position++;
    } else {
        printf("Error: Unexpected character '%c'.\n", lookahead());
        exit(1);
    }
}

// دالة لطباعة شجرة التحليل (Parser Tree)
void parse_tree(char non_terminal, int level) {
    print_indent(level);
    printf("%c\n", non_terminal);

    // البحث عن القاعدة المطابقة
    int i;
    for (i = 0; i < rule_count; i++) {
        if (rules[i].head == non_terminal) {
            int body_len = strlen(rules[i].body);
            print_indent(level + 1);
            printf("-> %s\n", rules[i].body);

            int j;
            for (j = 0; j < body_len; j++) {
                if (isupper(rules[i].body[j])) {  // Non-terminal
                    parse_tree(rules[i].body[j], level + 2);
                } else {  // Terminal
                    print_indent(level + 2);
                    printf("%c\n", rules[i].body[j]);
                    match(rules[i].body[j]);
                }
            }
            return;
        }
    }

    printf("Error: No matching rule for %c\n", non_terminal);
    exit(1);
}

// دالة لبدء التحليل
void start_parsing() {
    if (rule_count == 0) {
        printf("Error: No rules defined!\n");
        return;
    }

    printf("Enter input string: ");
    scanf("%s", input);
    position = 0;

    printf("\nParsing starts...\n");
    parse_tree(rules[0].head, 0);

    if (position == strlen(input)) {
        printf("\nParsing Successful! Input Accepted.\n");
    } else {
        printf("\nParsing Failed! Unconsumed Input Remaining.\n");
    }
}

// القائمة الرئيسية
void menu() {
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a rule\n");
        printf("2. Display current rules\n");
        printf("3. Start parsing\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_rule();
                break;
            case 2:
                display_rules();
                break;
            case 3:
                start_parsing();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    printf("Welcome to the Simple Grammar Parser!\n");
    menu();
    return 0;
}
