#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) {
    return S21_NULL;
  }
  int err = 0;
  s21_size_t lenSrc = s21_strlen(src), lenStr = s21_strlen(str);
  if (start_index > lenSrc) {
    err = 1;
  }
  /* cppcheck-suppress cstyleCast */
  char *inserted = (char *)calloc(1 + lenSrc + lenStr, sizeof(char));
  if (inserted == S21_NULL) {
    err = 1;
  }
  s21_size_t j = 0;
  for (s21_size_t i = 0; i < lenSrc; i++, j++) {
    if (i == start_index) {
      for (s21_size_t g = 0; g < lenStr; g++, j++) {
        inserted[j] = str[g];
      }
    }
    inserted[j] = src[i];
  }
  if (start_index == lenSrc) {
    for (s21_size_t g = 0; g < lenStr; g++, j++) {
      inserted[j] = str[g];
    }
  }
  if (err == 1) {
    free(inserted);
  }
  /* cppcheck-suppress cstyleCast */
  return (err == 1) ? S21_NULL : (void *)inserted;
}

// int main(){
//     const char *src = "Hello, World!";
//     const char *str = S21_NULL;
//     size_t pos = 5;
//     /* cppcheck-suppress cstyleCast */
//     char *result = (char *)s21_insert(src, str, pos);
//     printf("%s\n" ,result);
//     free(result);
//     return 0;
// }

// int main(){
//     const char *q = "123890";
//     const char *p = "4567";
//     /* cppcheck-suppress cstyleCast */
//     char *a = (char *)s21_insert(q, p, 3);

//     if (a) {
//         printf("%s\n",a);
//         free(a);
//     } else {
//         printf("Ошибка вставки!\n");
//     }

//     return 0;
// }