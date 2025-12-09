#include "s21_test.h"

// возвращает строку с описанием ошибки для заданного кода ошибки
// сначала определяются границы значений кодов ошибок в зависимости от
// операционной системы
//  затем в цикле проходятся все значения в этом диапазоне
// для каждого значения кода ошибки вызывается функция s21_strerror
// и функция strerror из стандартной библиотеки, и их результаты сравниваются с
// помощью функции ck_assert_str_eq
START_TEST(test_s21_strerror) {
  int start, end;
#ifdef __APPLE__
  start = -1;
  end = 107;
#elif __linux__
  start = -1;
  end = 134;
#else
  start = 0;
  end = 0;
#endif

  for (int i = start; i <= end; i++) {
    const char *expected = strerror(i);
    const char *result = s21_strerror(i);
    ck_assert_str_eq(result, expected);
  }
}
END_TEST

Suite *suite_s21_strerror(void) {
  Suite *s = suite_create("s21_strerror");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strerror);

  suite_add_tcase(s, tc_core);

  return s;
}
