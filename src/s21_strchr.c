#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  /* cppcheck-suppress cstyleCast */
  const unsigned char *s = (const unsigned char *)str;
  char *result = S21_NULL;
  char h = c + '\0';

  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (h == s[i]) {
      result = (char *)(s + i);
      break;
    }
  }
  return result;
}

// int main() {
//     char h[] = "12345";
//     printf("%s\n", s21_strchr(h,'3'));
//     // printf("%s\n", strchr(h,'3'));
//     return 0;
// }