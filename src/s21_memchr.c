#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) /* str: указатель на
область памяти, в которой будет производиться поиск, c: символ, который нужно
найти, n: количество байтов для поиска*/
{
  /* cppcheck-suppress cstyleCast */ /* этот комментарий указывает статическому
  анализатору CppCheck игнорировать предупреждение о приведении типов в стиле C
  в следующей строке*/
  /* без этого выходит предупреждение вызванное требованиями инструмента
   * статического анализа*/
  const unsigned char *q = (const unsigned char *)
      str; /* Приведение указателя str к типу const unsigned
char *. Это делается для того, чтобы можно было работать с каждым байтом памяти.
Тип unsigned char выбран, так как он гарантированно занимает один байт*/

  char *res = S21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (q[i] == (unsigned char)c) {
      res = (char *)(q + i);
      break;
    }
  }
  return (void *)res;
}

// int main()
// {
//     const char *str = "logitech";
//     char c = 'h';
//     s21_size_t n = 9;
//     /* cppcheck-suppress cstyleCast */
//     char *result = (char *)s21_memchr(str, c, n); /* Приведение указателя str
//     к const unsigned char* */ if (result != S21_NULL)
//     {
//         printf("Found '%c' at position: %td\n", c, result - str);
//     }
//     else
//     {
//         printf("Character '%c' not found in the first %zu bytes\n", c, n);
//     }
//     return 0;
// }