#include "s21_test.h"

// проверяет, что функция s21_strstr находит подстроку в строке
START_TEST(test_s21_strstr_found) {
  const char *str = "Hello, world!";
  const char *substr = "world";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

// проверяет, что функция s21_strstr не находит подстроку, которой нет в строке
START_TEST(test_s21_strstr_not_found) {
  const char *str = "Hello, world!";
  const char *substr = "planet";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

// проверяет, что функция s21_strstr корректно обрабатывает пустую подстроку
START_TEST(test_s21_strstr_empty_substr) {
  const char *str = "Hello, world!";
  const char *substr = "";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

// проверяет, что функция s21_strstr корректно обрабатывает случай, когда
// подстрока длиннее строки
START_TEST(test_s21_strstr_substr_longer_than_str) {
  const char *str = "Hi";
  const char *substr = "Hello";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

// проверяет, что функция s21_strstr находит подстроку в начале строки
START_TEST(test_s21_strstr_substr_at_start) {
  const char *str = "Hello, world!";
  const char *substr = "Hello";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

// проверяет, что функция s21_strstr находит подстроку в конце строки
START_TEST(test_s21_strstr_substr_at_end) {
  const char *str = "Hello, world!";
  const char *substr = "world!";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

// проверяет, что функция s21_strstr корректно обрабатывает случай полного
// совпадения строки и подстроки
START_TEST(test_s21_strstr_full_match) {
  const char *str = "Hello";
  const char *substr = "Hello";
  ck_assert_ptr_eq(s21_strstr(str, substr), strstr(str, substr));
}
END_TEST

Suite *suite_s21_strstr(void) {
  Suite *s = suite_create("s21_strstr");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strstr_found);
  tcase_add_test(tc_core, test_s21_strstr_not_found);
  tcase_add_test(tc_core, test_s21_strstr_empty_substr);
  tcase_add_test(tc_core, test_s21_strstr_substr_longer_than_str);
  tcase_add_test(tc_core, test_s21_strstr_substr_at_start);
  tcase_add_test(tc_core, test_s21_strstr_substr_at_end);
  tcase_add_test(tc_core, test_s21_strstr_full_match);

  suite_add_tcase(s, tc_core);

  return s;
}
