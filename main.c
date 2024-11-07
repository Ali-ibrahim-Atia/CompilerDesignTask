#include<stdio.h>
#include <stdlib.h>
#include "macofunctions.h"
#include<string.h>
#include <ctype.h>
int main()
{
   char *input = NULL;
    size_t size = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Please enter your code (press enter on an empty line to end input and start the operation):\n");


    while ((read = getline(&line, &len, stdin)) != -1) {
        if (strcmp(line, "\n") == 0) {
            break;
        }

        char *temp = realloc(input, size + read + 1);
        if (temp == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(input);
            free(line);
            return 1;
        }
        input = temp;
        strcpy(input + size, line);
        size += read;
    }

    free(line);
    if (input != NULL) {
        printf("Starting tokenization\n");
        tokenizer(input);
        free(input);
    }

    return 0;
}
int lenght_of_str(char* str)
{
    int i = 0;

    while(str[i] != '\0')
        i++;
    return i;
}
int compare_str(char* str1,char* str2)
{
    if(lenght_of_str(str1) == lenght_of_str(str2))
    {
        for(int i = 0; i < lenght_of_str(str1); i++)
        {
            if(str1[i] != str2[i])
                return 0;
        }
        return 1;
    }
    return 0;
}
char* substring(char* src_str,int l_pos,int r_pos)
{
    /* calc substring length*/
    int len = r_pos - l_pos + 1;

    /* create mem for substring copy*/
    char *dest_str = (char*)malloc(sizeof(char)*(len + 1));
    /*loop to copy substring into dest string*/
    for(int i = l_pos; i <= r_pos && src_str[i] != '\0'; i++)
    {
        *dest_str = src_str[i];
        dest_str++;
    }
    *dest_str = '\0';
    /*return pointer to the first character of substring*/
    return dest_str - len;
}

void copy_string(char* str1,char* str2)
{
    int i = 0;
    while (str1[i] != '\0')
    {
        str2[i] = str1[i];
        i++;
    }
}

int is_operator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' ||
       ch == '/' || ch == '>' || ch == '<' ||
       ch == '=')
       {return 1;}
    return 0;
}

int is_delimiter(char ch)
{
    if(ch == ' '||ch == '+'||ch == '-'||ch == '*'||
       ch == '/'||ch == ','||ch == ';'||ch == '>'||
       ch == '<'||ch == '='||ch == '('||ch==')'||
       ch == '['||ch == ']'||ch == '{'||ch=='}')
       {return 1;}
    return 0;
}

int is_valid_identifier(const char* str)
{

  if (str == NULL || str[0] == '\0') {
        return 0;
    }


    if (!(isalpha(str[0]) || str[0] == '_')) {
        return 0;
    }


    for (int i = 1; str[i] != '\0'; i++) {
        if (!(isalnum(str[i]) || str[i] == '_' )) {
            return 0;
        }
    }

    return 1;
}

int is_keyword(char* str)
{
 const char* keywords[] = {
        "if", "else", "while", "do", "break", "for", "continue",
        "int", "double", "float", "return", "char", "case", "short",
        "sizeof", "long", "typedef", "switch", "unsigned", "void",
        "static", "struct", "goto","volatile","union","enum","register","signed","inline","extern","auto","default","const"
    };


    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;


}

int is_integer(char* str)
{
    int len = lenght_of_str(str);
    if(len == 0)
        return 0;

    for(int i = 0; i < len; i++)
    {
        if(str[i] != '0'&&str[i] != '1'&&str[i] != '2'&&
           str[i] != '3'&&str[i] != '4'&&str[i] != '5'&&
           str[i] != '6'&&str[i] != '7'&&str[i] != '8'&&
           str[i] != '9' || (str[i] == '-'&&i > 0))
           { return 0;}
    }
    return 1;
}
int is_real_number(char* str){
    int decimal_flag = 0;
    int len = lenght_of_str(str);
    if(len == 0)
        return 0;
    for(int i = 0; i < len; i++)
    {
        if(str[i] != '0'&&str[i] != '1'&&str[i] != '2'&&
           str[i] != '3'&&str[i] != '4'&&str[i] != '5'&&
           str[i] != '6'&&str[i] != '7'&&str[i] != '8'&&
           str[i] != '9'&&str[i] != '.' || (str[i] == '-'&&i > 0))
           {return 0; }
        if(str[i] == '.')
        {
            decimal_flag = 1;
        }
    }
    return decimal_flag;
}

int tokenizer(char* str)
{
    int left = 0,right = 0;
    int len = lenght_of_str(str);

    while(right <= len && left <= right)
    {

        if (str[right] == '/' && str[right + 1] == '/') {
            while (str[right] != '\n' && right < len) {
                right++;
            }
            left = right;
            continue;
        }
        if (str[right] == '/' && str[right + 1] == '*') {
            while (!(str[right] == '*' && str[right + 1] == '/') && right < len) {
                right++;
            }
            right += 2;
            left = right;
            continue;
        }

        /* look for the first delimiter or white space */
        if(is_delimiter(str[right]) == 0)
        {right ++;}
        /*check if it is a single character then if it is an operator*/
        if(is_delimiter(str[right]) == 1 && left == right)
        {
            if(is_operator(str[right]) == 1)
                printf("(%c) = > is an operator \n",str[right]);
            else if(is_delimiter(str[right]) == 1 && str[right] != ' ')
            {
                printf("(%c) => is a special character\n",str[right]);
            }
            /*skip the delimiter and set new frame of reference*/
            right ++;
            left = right;
        }
        else if (is_delimiter(str[right]) == 1&& left != right ||(right == len && left != right))
        {
            char* substr = substring(str,left,right - 1);
            if(is_keyword(substr) == 1)
                printf("(%s) => is keyword \n",substr);
            else if(is_integer(substr) == 1)
                    printf("(%s) => is integer\n",substr);

              else if(is_real_number(substr) == 1)
                    printf("(%s) => is real number\n",substr);
             else if(is_valid_identifier(substr) == 1 && is_delimiter(str[right - 1]) == 0)
             {
                     printf("(%s) => is identifier\n",substr);


             }
        left = right;
        }
    }

    }

