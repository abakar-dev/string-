#include "s21_test.h"

// проверяет, что функция s21_strrchr находит последнее вхождение символа 'o'
// в строке "Hello, world!" и возвращает указатель на этот символ
START_TEST(test_s21_strrchr_found) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
}
END_TEST

// проверяет , что функция s21_strrchr не находит символ 'z' в строке "Hello,
// world!" и возвращает NULL
START_TEST(test_s21_strrchr_not_found) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

// проверяет  что функция s21_strrchr возвращает NULL при поиске символа 'a' в
// пустой строке
START_TEST(test_s21_strrchr_empty_string) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
}
END_TEST

// проверяет что функция s21_strrchr находит символ 'A' в строке "A" и
// возвращает указатель на этот символ
START_TEST(test_s21_strrchr_single_char) {
  const char *str = "A";
  ck_assert_ptr_eq(s21_strrchr(str, 'A'), strrchr(str, 'A'));
}
END_TEST

// проверяет что функция s21_strrchr не находит символ 'B' в строке "A" и
// возвращает NULL
START_TEST(test_s21_strrchr_single_char_not_found) {
  const char *str = "A";
  ck_assert_ptr_eq(s21_strrchr(str, 'B'), strrchr(str, 'B'));
}
END_TEST

// проверяет что функция s21_strrchr находит символ '\0' в строке "Find the null
// character\0 here" и возвращает указатель на этот символ
START_TEST(test_s21_strrchr_null_char) {
  const char *str = "Find the null character\0 here";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

// проверяет что функция s21_strrchr находит последнее вхождение символа 'b' в
// строке "aabbccddeeff" и возвращает указатель на этот символ
START_TEST(test_s21_strrchr_repeated_chars) {
  const char *str = "aabbccddeeff";
  ck_assert_ptr_eq(s21_strrchr(str, 'b'), strrchr(str, 'b'));
}
END_TEST

// проверяет что функция s21_strrchr находит пробел в строке "This is a test
// string." и возвращает указатель на этот символ
START_TEST(test_s21_strrchr_space_char) {
  const char *str = "This is a test string.";
  ck_assert_ptr_eq(s21_strrchr(str, ' '), strrchr(str, ' '));
}
END_TEST

Suite *suite_s21_strrchr(void) {
  Suite *s = suite_create("s21_strrchr");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strrchr_found);
  tcase_add_test(tc_core, test_s21_strrchr_not_found);
  tcase_add_test(tc_core, test_s21_strrchr_empty_string);
  tcase_add_test(tc_core, test_s21_strrchr_single_char);
  tcase_add_test(tc_core, test_s21_strrchr_single_char_not_found);
  tcase_add_test(tc_core, test_s21_strrchr_null_char);
  tcase_add_test(tc_core, test_s21_strrchr_repeated_chars);
  tcase_add_test(tc_core, test_s21_strrchr_space_char);

  suite_add_tcase(s, tc_core);

  return s;
}