#include "s21_test.h"

// проверяет корректность работы функции s21_strchr при поиске символа 'a' в
// строке "abrakadabra
START_TEST(Abrakadabra_find_a) {
  char src[] = "abrakadabra";
  char find = 'a';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

// проверяет корректность работы функции s21_strchr
// при поиске символа 'L' после символа с нулевым байтом в строке "Shololo \0
// LLLooololo"
START_TEST(char_after_zero_symbol) {
  char str[] = "Shololo \0 LLLooololo";
  int find_byte = 'L';

  ck_assert_ptr_eq(s21_strchr(str, find_byte), strchr(str, find_byte));
}
END_TEST

// проверяет  корректность работы функции s21_strchr при поиске символа 'A' в
// строке "abrakadAbra"
START_TEST(abrakadabra_find_A) {
  char src[] = "abrakadAbra";
  char find = 'A';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

// проверяет корректность работы функции s21_strchr при поиске символа '1' в
// строке "abrakaDA1bra"
START_TEST(abrakadabra_find_1) {
  char src[] = "abrakaDA1bra";
  char find = '1';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

// проверяет корректность работы функции s21_strchr при поиске символа 'Z' в
// строке "abrakaDA1bra"
START_TEST(abrakaDA1bra_find_Z) {
  char src[] = "abrakaDA1bra";
  char find = 'Z';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

// проверяет корректность работы функции s21_strchr при поиске символа '3' в
// строке "abrakaDA1bra"
START_TEST(abrakaDA1bra_find_3) {
  char src[] = "abrakaDA1bra";
  char find = '3';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

// проверяет корректность работы функции s21_strchr при передаче пустой строки и
// поиске символа '3'
START_TEST(empty_src) {
  char src[] = "";
  char find = '3';

  ck_assert_pstr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

Suite *suite_s21_strchr(void) {
  Suite *s = suite_create("s21_strchr");
  TCase *tc = tcase_create("strchr_tc");

  tcase_add_test(tc, Abrakadabra_find_a);
  tcase_add_test(tc, char_after_zero_symbol);
  tcase_add_test(tc, abrakadabra_find_A);
  tcase_add_test(tc, abrakadabra_find_1);
  tcase_add_test(tc, abrakaDA1bra_find_Z);
  tcase_add_test(tc, abrakaDA1bra_find_3);
  tcase_add_test(tc, empty_src);

  suite_add_tcase(s, tc);
  return s;
}