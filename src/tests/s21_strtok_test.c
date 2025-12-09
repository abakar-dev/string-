#include "s21_test.h"

// проверяет работу функции s21_strtok() при обычном использовании, когда строка
// содержит различные символы-разделители
START_TEST(test_s21_strtok_normal_use) {
  char str1_s21[] = "Hello, world! This is a test.";
  char str1_sys[] = "Hello, world! This is a test.";
  const char delim1[] = " ,.!";

  char *token1_s21 = s21_strtok(str1_s21, delim1);
  char *token1_sys = strtok(str1_sys, delim1);
  ck_assert_str_eq(token1_s21, token1_sys);
}
END_TEST

// проверяет работу функции s21_strtok() при передаче пустой строки
START_TEST(test_s21_strtok_empty_string) {
  char str2_s21[] = "";
  char str2_sys[] = "";
  const char delim2[] = " ,.!";

  char *token2_s21 = s21_strtok(str2_s21, delim2);
  char *token2_sys = strtok(str2_sys, delim2);
  ck_assert_ptr_eq(token2_s21, token2_sys);
}
END_TEST

// проверяет работу функции s21_strtok() при передаче строки, содержащей только
// символы-разделители
START_TEST(test_s21_strtok_only_delimiters) {
  char str3_s21[] = ",,,, ....";
  char str3_sys[] = ",,,, ....";
  const char delim3[] = " ,.!";

  char *token3_s21 = s21_strtok(str3_s21, delim3);
  char *token3_sys = strtok(str3_sys, delim3);
  ck_assert_ptr_eq(token3_s21, token3_sys);
}
END_TEST

// проверяет работу функции s21_strtok() при отсутствии символов-разделителей в
// строке, а также поведение функции при передаче NULL в качестве аргумента
START_TEST(test_s21_strtok_no_delimiters) {
  char str4_s21[] = "nodelimitershere";
  char str4_sys[] = "nodelimitershere";
  const char delim4[] = " ,.!";

  char *token4_s21 = s21_strtok(str4_s21, delim4);
  char *token4_sys = strtok(str4_sys, delim4);
  ck_assert_str_eq(token4_s21, token4_sys);

  token4_s21 = s21_strtok(S21_NULL, delim4);
  token4_sys = strtok(NULL, delim4);
  ck_assert_ptr_eq(token4_s21, token4_sys);
}
END_TEST

// проверяет работу функции s21_strtok() при наличии символов-разделителей в
// начале и в конце строки
START_TEST(test_s21_strtok_leading_trailing_delimiters) {
  char str5_s21[] = " WOW! , Hello, world! , ";
  char str5_sys[] = " WOW! , Hello, world! , ";
  const char delim5[] = " ,.!";

  char *token5_s21 = s21_strtok(str5_s21, delim5);
  char *token5_sys = strtok(str5_sys, delim5);
  ck_assert_str_eq(token5_s21, token5_sys);
}
END_TEST

Suite *suite_s21_strtok(void) {
  Suite *s = suite_create("s21_strtok");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strtok_normal_use);
  tcase_add_test(tc_core, test_s21_strtok_empty_string);
  tcase_add_test(tc_core, test_s21_strtok_only_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_no_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_leading_trailing_delimiters);

  suite_add_tcase(s, tc_core);

  return s;
}
