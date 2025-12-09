#include "s21_test.h"

// проверяет функцию s21_strcspn на случай, когда две строки не имеют общих
// символов. Сравнивает результат работы функции s21_strcspn с результатом
// работы стандартной функции strcspn
START_TEST(test_s21_strcspn_no_common_chars) {
  const char *str1 = "hello world";
  const char *str2 = "abc";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// проверяет функцию s21_strcspn на случай, когда две строки содержат общие
// символы.
// Сравнивает результат работы функции s21_strcspn с результатом работы
// стандартной функции strcspn
START_TEST(test_s21_strcspn_with_common_chars) {
  const char *str1 = "hello world";
  const char *str2 = "def";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// проверяет функцию s21_strcspn на случай, когда одна строка полностью
// содержится в другой. Сравнивает результат работы функции s21_strcspn с
// результатом работы стандартной функции strcspn
START_TEST(test_s21_strcspn_full_match) {
  const char *str1 = "hello world";
  const char *str2 = "world";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// проверяет функцию s21_strcspn на случай, когда вторая строка пустая.
// Сравнивает результат работы функции s21_strcspn с результатом работы
// стандартной функции strcspn
START_TEST(test_s21_strcspn_empty_str2) {
  const char *str1 = "hello world";
  const char *str2 = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// проверяет функцию s21_strcspn на случай, когда первая строка пустая.
// Сравнивает результат работы функции s21_strcspn с результатом работы
// стандартной функции strcspn
START_TEST(test_s21_strcspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// проверяет функцию s21_strcspn на случай, когда обе строки пустые.
// Сравнивает результат работы функции s21_strcspn с результатом работы
// стандартной функции strcspn
START_TEST(test_s21_strcspn_both_empty) {
  const char *str1 = "";
  const char *str2 = "";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite *suite_s21_strcspn(void) {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strcspn_no_common_chars);
  tcase_add_test(tc_core, test_s21_strcspn_with_common_chars);
  tcase_add_test(tc_core, test_s21_strcspn_full_match);
  tcase_add_test(tc_core, test_s21_strcspn_empty_str2);
  tcase_add_test(tc_core, test_s21_strcspn_empty_str1);
  tcase_add_test(tc_core, test_s21_strcspn_both_empty);

  suite_add_tcase(s, tc_core);

  return s;
}