#include "s21_test.h"

// проверяет копирование пустой строки в строку назначения размером 1 байт
START_TEST(empty) {
  char src[] = "";
  char res[] = "1111";
  char exp[] = "1111";
  s21_size_t n_byte = 1;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

// проверяет копирование строки "123" в строку назначения размером 4 байта.
START_TEST(four_bytes) {
  char src[] = "123";
  char res[] = "abcd";
  char exp[] = "abcd";
  s21_size_t n_byte = 4;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

// проверяет копирование пустой строки в строку назначения размером 1 байт
START_TEST(empty_src) {
  char src[] = "";
  char res[] = "123";
  char exp[] = "123";
  s21_size_t n_byte = 1;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

// проверяет копирование одного символа из строки "123" в строку назначения
// размером 4 байта
START_TEST(one_byte) {
  char src[] = "123";
  char res[4] = "999";
  char exp[4] = "999";
  s21_size_t n_byte = 1;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

// проверяет копирование двух символов из строки "123" в строку назначения
// размером 3 байта
START_TEST(two_bytes) {
  char src[] = "123";
  char res[] = "xxx";
  char exp[] = "xxx";
  s21_size_t n_byte = 2;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

// проверяет копирование строки "Str1ng" в строку назначения размером 7 байт
START_TEST(string) {
  char src[] = "Str1ng";
  char res[] = "gn1rtS";
  char exp[] = "gn1rtS";
  s21_size_t n_byte = 7;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);
}
END_TEST

Suite *suite_s21_strncpy(void) {
  Suite *s = suite_create("s21_strncpy");
  TCase *tc = tcase_create("strncpy_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, four_bytes);
  tcase_add_test(tc, empty_src);
  tcase_add_test(tc, one_byte);
  tcase_add_test(tc, two_bytes);
  tcase_add_test(tc, string);

  suite_add_tcase(s, tc);
  return s;
}