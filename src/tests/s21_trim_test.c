#include "s21_test.h"

// проверяет базовый случай обрезания пробельных символов с начала и конца
// строки
START_TEST(test_trim_basic) {
  const char *src = "  hello  ";
  const char *expected = "hello";
  char *result = s21_trim(src, NULL);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

// проверяет случай, когда в строке нет символов для обрезания
START_TEST(test_trim_no_trim_chars) {
  const char *src = "hello";
  const char *expected = "hello";
  char *result = s21_trim(src, NULL);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

// проверяет обрезание пользовательских символов с начала и конца строки
START_TEST(test_trim_custom_chars) {
  const char *src = "--hello--";
  const char *expected = "hello";
  char *result = s21_trim(src, "-");

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

// проверяет обрезание пустой строки
START_TEST(test_trim_empty_string) {
  const char *src = "";
  const char *expected = "";
  char *result = s21_trim(src, NULL);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

// проверяет случай, когда вся строка состоит из символов для обрезания
START_TEST(test_trim_all_trimmed) {
  const char *src = "    ";
  const char *expected = "";
  char *result = s21_trim(src, NULL);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

// проверяет обрезание специальных пробельных символов с начала и конца строки
START_TEST(test_trim_special_chars) {
  const char *src = "\t\n\v\r\f hello \t\n";
  const char *expected = "hello";
  char *result = s21_trim(src, NULL);

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

// проверяет обрезание пользовательских специальных символов с начала и конца
// строки
START_TEST(test_trim_custom_special_chars) {
  const char *src = "@@@hello@@@";
  const char *expected = "hello";
  char *result = s21_trim(src, "@");

  ck_assert_str_eq(result, expected);

  free(result);
}
END_TEST

Suite *suite_s21_trim(void) {
  Suite *s = suite_create("s21_trim");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_trim_basic);
  tcase_add_test(tc_core, test_trim_no_trim_chars);
  tcase_add_test(tc_core, test_trim_custom_chars);
  tcase_add_test(tc_core, test_trim_empty_string);
  tcase_add_test(tc_core, test_trim_all_trimmed);
  tcase_add_test(tc_core, test_trim_special_chars);
  tcase_add_test(tc_core, test_trim_custom_special_chars);

  suite_add_tcase(s, tc_core);

  return s;
}