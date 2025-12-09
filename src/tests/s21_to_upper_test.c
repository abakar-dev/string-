#include "s21_test.h"

// проверяет функцию s21_to_upper, которая преобразует все символы в строке в
// верхний регистр
START_TEST(to_upper_test1) {
  char str[] = "hello world";
  char expected[] = "HELLO WORLD";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// аналогично предыдущему тесту
START_TEST(to_upper_test2) {
  char str[] = "empty";
  char expected[] = "EMPTY";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// проверяет что функция не изменяет строку, если в ней присутствуют числовые
// символы
START_TEST(to_upper_test3) {
  char str[] = "1+1*1";
  char expected[] = "1+1*1";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// проверяет что функция сохраняет пробел в строке без изменений
START_TEST(to_upper_test4) {
  char str[] = " ";
  char expected[] = " ";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// проверяет  что функция корректно обрабатывает пустую строку
START_TEST(to_upper_test5) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_upper(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

Suite *suite_s21_to_upper(void) {
  Suite *s = suite_create("s21_to_upper");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, to_upper_test1);
  tcase_add_test(tc, to_upper_test2);
  tcase_add_test(tc, to_upper_test3);
  tcase_add_test(tc, to_upper_test4);
  tcase_add_test(tc, to_upper_test5);

  suite_add_tcase(s, tc);
  return s;
}