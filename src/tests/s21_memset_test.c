#include "s21_test.h"

// проверяет корректность замены символов в строке "shala\0alalalal" на символ
// 'S' в 10 байтах
START_TEST(mem_test) {
  char res[] = "shala\0alalalal";
  char expected[] = "shala\0alalalal";
  char replace = 'S';
  s21_size_t n_byte = 10;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

// проверяет корректность замены символов в строке "aboba" на символ 'g' в 5
// байтах
START_TEST(aboba_test) {
  char res[] = "aboba";
  char expected[] = "aboba";
  char replace = 'g';
  s21_size_t n_byte = 5;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

// проверяет корректность замены символов в строке "aboba" на символ 'g' в 0
// байтах (не должна произойти замена)
START_TEST(zero_byte) {
  char res[] = "aboba";
  char expected[] = "aboba";
  char replace = 'g';
  s21_size_t n_byte = 0;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

// проверяет корректность замены символов в пустой строке на символ '\0' в 1
// байте
START_TEST(empty) {
  char res[] = "";
  char expected[] = "";
  char replace = '\0';
  s21_size_t n_byte = 1;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

// проверяет корректность замены символов в строке "aboba" на символ 'A' в 3
// байтах
START_TEST(replace_on_register_sim) {
  char res[] = "aboba";
  char expected[] = "aboba";
  char replace = 'A';
  s21_size_t n_byte = 3;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_mem_eq(res, expected, n_byte);
}
END_TEST

// проверяет корректность замены символов в строке "a1obA" на символ '1' в 5
// байтах
START_TEST(replace_on_register_num) {
  char res[] = "a1obA";
  char expected[] = "a1obA";
  char replace = '1';
  s21_size_t n_byte = 5;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет корректность замены символов в длинной строке на символ '1' в 5
// байтах
START_TEST(long_string) {
  char res[] =
      "a1oas[pifjaosidfj oapisjdfpoi asjdfoij ouh12oi3 uh12i3 "
      "hiajhIOUAHSDiouAHSdu1).bA";
  char expected[] =
      "a1oas[pifjaosidfj oapisjdfpoi asjdfoij ouh12oi3 uh12i3 "
      "hiajhIOUAHSDiouAHSdu1).bA";
  char replace = '1';
  s21_size_t n_byte = 5;

  s21_memset(res, replace, n_byte);
  memset(expected, replace, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

Suite *suite_s21_memset(void) {
  Suite *s = suite_create("s21_memset");
  TCase *tc = tcase_create("memset_tc");

  tcase_add_test(tc, mem_test);
  tcase_add_test(tc, aboba_test);
  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, replace_on_register_sim);
  tcase_add_test(tc, replace_on_register_num);
  tcase_add_test(tc, long_string);

  suite_add_tcase(s, tc);
  return s;
}