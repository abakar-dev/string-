#include "s21_test.h"

// проверяет сравнение двух пустых строк с использованием функции s21_strncmp и
// стандартной функции strncmp
START_TEST(empty) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t n_byte = 0;

  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  ck_assert_int_eq(got, expected);
}
END_TEST

// равнивает строку "fasdfa" с пустой строкой, используя только один байт для
// сравнения
START_TEST(fasdfa_) {
  char str1[] = "fasdfa";
  char str2[] = "";
  s21_size_t n_byte = 1;

  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  ck_assert_int_eq(got > 0, expected > 0);
}
END_TEST

// сравнивает пустую строку со строкой "fasdfa", используя только один байт для
// сравнения
START_TEST(_fasdfa) {
  char str1[] = "";
  char str2[] = "fasdfa";
  s21_size_t n_byte = 1;

  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  ck_assert_int_eq(got > 0, expected > 0);
}
END_TEST

// сравнивает две одинаковые строки "fasdfa" с использованием шести байт для
// сравнения
START_TEST(fasdfa_fasdfa) {
  char str1[] = "fasdfa";
  char str2[] = "fasdfa";
  s21_size_t n_byte = 6;

  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  ck_assert_int_eq(got > 0, expected > 0);
}
END_TEST

// сравнивает две строки "fasdfabazbazkotya" и "fasdfabaz", используя десять
// байт для сравнения
START_TEST(fasdfa_fasdfa_zero_byte) {
  char str1[] = "fasdfabazbazkotya";
  char str2[] = "fasdfabaz";
  s21_size_t n_byte = 10;

  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  ck_assert_int_eq(got > 0, expected > 0);
}
END_TEST

// сравнивает две строки "fasdfa" с использованием только одного байта для
// сравнения
START_TEST(fasdfa_fasdfa_one_byte) {
  char str1[] = "fasdfa";
  char str2[] = "fasdfa";
  s21_size_t n_byte = 1;

  int got = s21_strncmp(str1, str2, n_byte);
  int expected = strncmp(str1, str2, n_byte);

  ck_assert_int_eq(got > 0, expected > 0);
}
END_TEST

Suite *suite_s21_strncmp(void) {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc = tcase_create("strncmp_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, fasdfa_);
  tcase_add_test(tc, _fasdfa);
  tcase_add_test(tc, fasdfa_fasdfa);
  tcase_add_test(tc, fasdfa_fasdfa_zero_byte);
  tcase_add_test(tc, fasdfa_fasdfa_one_byte);

  suite_add_tcase(s, tc);
  return s;
}