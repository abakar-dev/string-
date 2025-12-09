#include "s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  int err = 0;
  int length = s21_strlen(str);
  /* cppcheck-suppress cstyleCast */
  char *strLow = (char *)malloc((1 + length) * sizeof(char));
  if (strLow == S21_NULL) {
    err = 1;
  }
  for (int i = 0; i < length; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      strLow[i] = (str[i] - 'A' + 'a' + '\0');
    } else {
      strLow[i] = str[i];
    }
  }
  strLow[length] = '\0';
  if (err == 1) {
    free(strLow);
  }
  /* cppcheck-suppress cstyleCast */
  return (err == 1) ? S21_NULL : (void *)strLow;
}

// int main(){
//     char str[] = "WERTYUIO";
// //   char expected[] = "";/
//   char *got = s21_to_lower(str);

//     printf("%s\n",got);
//     free(got);
//     return 0;
// }

// int main(){
//     const char *q = "WERTYUIOL";
//     /* cppcheck-suppress cstyleCast */
//     char *p = (char *)s21_to_lower(q);

//     printf("%s\n", p);
//     free(p);

//     return 0;
// }