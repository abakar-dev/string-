#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  if (i < n) {
    dest[i] = '\0';
  }
  return dest;
}

// int main() {
//     char dest1[14] = {0};
//     char orig_dest1[14] = {0};

//     s21_strncpy(dest1, "Hello, World!", 1);
//     printf("Example 1: dest1 = '%s'\n", dest1);

//     strncpy(orig_dest1, "Hello, World!", 1);
//     orig_dest1[1] = '\0';
//     printf("Original Example 1: orig_dest1 = '%s'\n", orig_dest1);

//     return 0;
// }