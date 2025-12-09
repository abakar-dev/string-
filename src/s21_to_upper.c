#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  int length = s21_strlen(str) + 1;
  int err = 0;
  /* cppcheck-suppress cstyleCast */
  char *strUp = (char *)calloc(length, sizeof(char));
  if (strUp == S21_NULL) {
    err = 1;
  }
  for (int i = 0; i < length; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      strUp[i] = (str[i] - 'a' + 'A' + '\0');
    } else {
      strUp[i] = str[i];
    }
  }
  if (err == 1) {
    free(strUp);
  }
  /* cppcheck-suppress cstyleCast */
  return (err == 1) ? S21_NULL : (void *)strUp;
}

// int main(){
//     const char *q = "qwertyuio";
//     /* cppcheck-suppress cstyleCast */
//     char *p = (char *)s21_to_upper(q);
//     printf("%s \n", p);
//     free(p);

//     return 0;
// }