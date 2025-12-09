#include "s21_test.h"

// проверяет, что функция s21_strpbrk находит первое вхождение любого символа из
// строки str2 в строке str1, если такие символы есть
START_TEST(test_s21_strpbrk_found_vowels) {
  const char *str1 = "String with vowels.";
  const char *str2 = "AEtIOUaewou";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет что функция s21_strpbrk возвращает NULL, если не находит ни одного
// символа из строки str2 в строке str1
START_TEST(test_s21_strpbrk_not_found) {
  const char *str1 = "String with vowels.";
  const char *str2 = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет  поведение функции s21_strpbrk, если первая строка пустая
START_TEST(test_s21_strpbrk_empty_str1) {
  const char *str1 = "";
  const char *str2 = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет поведение функции s21_strpbrk, если вторая строка пустая
START_TEST(test_s21_strpbrk_empty_str2) {
  const char *str1 = "String with vowels.";
  const char *str2 = "";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет поведение функции s21_strpbrk, если обе строки пустые
START_TEST(test_s21_strpbrk_both_empty) {
  const char *str1 = "";
  const char *str2 = "";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет работу функции s21_strpbrk при поиске одного символа в строке
START_TEST(test_s21_strpbrk_single_char_found) {
  const char *str1 = "String with vowels.";
  const char *str2 = "S";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет работу функции s21_strpbrk при поиске символа "." в строке
START_TEST(test_s21_strpbrk_single_char_dot) {
  const char *str1 = "String with vowels.";
  const char *str2 = ".";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет работу функции s21_strpbrk при поиске совпадающего символа
START_TEST(test_s21_strpbrk_single_char_match) {
  const char *str1 = "a";
  const char *str2 = "a";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет работу функции s21_strpbrk при отсутствии совпадающего символа
START_TEST(test_s21_strpbrk_single_char_no_match) {
  const char *str1 = "a";
  const char *str2 = "b";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// проверяет работу функции s21_strpbrk на длинных строках
START_TEST(test_s21_strpbrk_long_string) {
  const char *str1 =
      "a very long string that we are using to test the strpbrk function with "
      "a significant amount of characters to ensure it handles long strings "
      "correctly";
  const char *str2 = "qwe";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

// работу функции s21_strpbrk при наличии повторяющихся символов
START_TEST(test_s21_strpbrk_repeated_chars) {
  const char *str1 = "aaaabbbbcccc";
  const char *str2 = "b";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *suite_s21_strpbrk(void) {
  Suite *s = suite_create("s21_strpbrk");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strpbrk_found_vowels);
  tcase_add_test(tc_core, test_s21_strpbrk_not_found);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_str1);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_str2);
  tcase_add_test(tc_core, test_s21_strpbrk_both_empty);
  tcase_add_test(tc_core, test_s21_strpbrk_single_char_found);
  tcase_add_test(tc_core, test_s21_strpbrk_single_char_dot);
  tcase_add_test(tc_core, test_s21_strpbrk_single_char_match);
  tcase_add_test(tc_core, test_s21_strpbrk_single_char_no_match);
  tcase_add_test(tc_core, test_s21_strpbrk_long_string);
  tcase_add_test(tc_core, test_s21_strpbrk_repeated_chars);

  suite_add_tcase(s, tc_core);

  return s;
}