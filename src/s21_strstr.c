#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  int n = s21_strlen(haystack);
  int m = s21_strlen(needle);

  int i = 0;
  while (i <= n - m) {
    int j = 0;
    while (j < m && haystack[i + j] == needle[j]) {
      j++;
    }
    if (j == m) return (char *)(haystack + i);
    i++;
  }
  return S21_NULL;
}

// int main(){
//     char a[] = "111221";
//     char b[] = "12";

//     printf("%s\n", s21_strstr(a,b));
//     printf("%s\n", strstr(a,b));
//     return 0;
// }