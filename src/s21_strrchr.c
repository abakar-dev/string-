#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *lastEntry = S21_NULL;

  do {
    if (*str == (char)c) {
      lastEntry = str;
    }
  } while (*str++ != '\0');

  return (char *)lastEntry;
}

// int main() {

//     const char *str = "Hello, world!";
//     int c = 'H';

//     char *result = s21_strrchr(str, c);

//     if (result != NULL) {
//         printf("The null terminator in \"%s\" is at position: %td\n", str,
//         result - str);
//     } else {
//         printf("Null terminator not found in \"%s\"\n", str);
//     }

//     return 0;
// }