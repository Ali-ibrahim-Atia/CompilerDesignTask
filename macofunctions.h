#ifndef _MACRO_FUNCTION_
#define _MACRO_FUNCTION_

/* calculate the size of the string */
int lenght_of_str(char* str);
/* compare two strings*/
int compare_str(char* str1,char* str2);
/* create substring of a string
    * return pointer to string
*/
char* substring(char* src_str,int l_pos,int r_pos);
/*check if the current character is operator*/
int is_operator(char ch);
/*check if the current character is delimeter or not */
int is_delimiter(char ch);
/*check if the current identifier is valid*/
int is_valid_identifier(const char* str);
/*check if the current tocken is keyword*/
int is_keyword(char* str);
/*che if the current token is ineger*/
int is_integer(char* str);
int is_real_number(char* str);
int tokenizer(char* str);
void copy_string(char* str1,char* str2);




#endif
