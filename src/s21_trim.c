#include "s21_string.h"

int s21_trim_null(char chr) {
  return (chr < 9 || (chr > 13 && chr != 32)) ? 1 : 0;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *trimmed = S21_NULL;

  if (src != S21_NULL) {
    int lenSrc = s21_strlen(src);
    int start = 0, end = lenSrc - 1;

    while (start < lenSrc &&
           ((trim_chars && s21_strchr(trim_chars, src[start]) != S21_NULL) ||
            (!trim_chars && !s21_trim_null(src[start])))) {
      start++;
    }

    while (end >= start &&
           ((trim_chars && s21_strchr(trim_chars, src[end]) != S21_NULL) ||
            (!trim_chars && !s21_trim_null(src[end])))) {
      end--;
    }

    int new_len = (end - start + 1);
    /* cppcheck-suppress cstyleCast */
    trimmed = (char *)calloc(new_len + 1, sizeof(char));
    if (trimmed != S21_NULL) {
      s21_strncpy(trimmed, src + start, new_len);
    }
  }

  return (void *)trimmed;
}

// int main() {
//     char charsToTrim1[] = " \t\n";
//     char s1[] = "  \t\n  Hello World! \n\t  ";
//     /* cppcheck-suppress cstyleCast */
//     char *p = (char *)s21_trim(s1, charsToTrim1);

//     if (p != S21_NULL) {
//         printf("%s\n", p);
//         free(p);
//     } else {
//         printf("Trimming resulted in S21_NULL\n");
//     }

//     return 0;
// }