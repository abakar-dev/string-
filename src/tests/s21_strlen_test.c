#include "s21_test.h"

#define BUFF_SIZE 512

// проверяет функцию s21_strlen на строке с символами
START_TEST(test_s21_strlen_non_empty_string) {
  const char *str = "String with characters.";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// проверяет функцию s21_strlen на строке, состоящей из одного пробельного
// символа
START_TEST(test_s21_strlen_spaces) {
  const char *str = "    ";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// проверяет функцию s21_strlen на строке "Hello, world!"
START_TEST(test_s21_strlen_hello_world) {
  const char *str = "Hello, world!";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// проверяет функцию s21_strlen на пустой строке
START_TEST(test_s21_strlen_empty_string) {
  const char *str = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// проверяет функцию s21_strlen на строке, состоящей из одного символа 'A
START_TEST(test_s21_strlen_single_char) {
  const char *str = "A";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

// проверяет функцию s21_strlen на строке длиной BUFF_SIZE - 1 символа, где
// BUFF_SIZE = 512 состоящей из символов 'a'
START_TEST(test_s21_strlen_long_string) {
  char str[BUFF_SIZE];
  for (int i = 0; i < BUFF_SIZE - 1; i++) {
    str[i] = 'a';
  }
  str[BUFF_SIZE - 1] = '\0';
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *suite_s21_strlen(void) {
  Suite *s = suite_create("s21_strlen");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strlen_non_empty_string);
  tcase_add_test(tc_core, test_s21_strlen_spaces);
  tcase_add_test(tc_core, test_s21_strlen_hello_world);
  tcase_add_test(tc_core, test_s21_strlen_empty_string);
  tcase_add_test(tc_core, test_s21_strlen_single_char);
  tcase_add_test(tc_core, test_s21_strlen_long_string);

  suite_add_tcase(s, tc_core);

  return s;
}