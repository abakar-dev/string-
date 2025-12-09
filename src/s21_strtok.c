#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *buffer;
  char *result = S21_NULL;

  if (str != S21_NULL) {
    buffer = str;
  } else if (buffer == S21_NULL) {
    result = S21_NULL;
  }
  if (result == S21_NULL) {
    while (*buffer && s21_strchr(delim, *buffer)) {
      buffer++;
    }

    if (*buffer == '\0') {
      result = S21_NULL;
    } else {
      char *token_start = buffer;
      buffer += s21_strcspn(buffer, delim);

      if (*buffer != '\0') {
        *buffer = '\0';
        buffer++;
      }
      result = token_start;
    }
  }
  return result;
}

// int main(){
//   char str[] = "Hello, world! Привет.";
//   const char delim[] = ", !";
//   char *token = s21_strtok(str, delim);
//   while (token != S21_NULL){
//     printf("Токен: %s\n", token);
//     token= s21_strtok(S21_NULL, delim);
//   }
//   return 0;
// }