#include "s21_test.h"

// проверяет функцию s21_to_lower на корректное преобразование всех символов в
// строке в нижний регистр
START_TEST(to_lower_test1) {
  char str[] = "oLoLolo D aLdFsAdf?";
  char expected[] = "olololo d aldfsadf?";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// проверяет  функцию s21_to_lower на корректное преобразование всех символов в
// строке в нижний регистр, включая цифры
START_TEST(to_lower_test2) {
  char str[] = "123456789Q";
  char expected[] = "123456789q";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// проверяет функцию s21_to_lower на корректное преобразование всех символов в
// строке в нижний регистр, включая пробелы
START_TEST(to_lower_test3) {
  char str[] = "Space created";
  char expected[] = "space created";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// проверяет функцию s21_to_lower на корректное обработку пустой строки
START_TEST(to_lower_test4) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

// проверяет функцию s21_to_lower на корректное обработку пустой строки
START_TEST(to_lower_test5) {
  char str[] = "";
  char expected[] = "";
  char *got = s21_to_lower(str);
  ck_assert_str_eq(got, expected);
  if (got) free(got);
}
END_TEST

Suite *suite_s21_to_lower(void) {
  Suite *s = suite_create("s21_to_lower");
  TCase *tc = tcase_create("to_lower_tc");

  tcase_add_test(tc, to_lower_test1);
  tcase_add_test(tc, to_lower_test2);
  tcase_add_test(tc, to_lower_test3);
  tcase_add_test(tc, to_lower_test4);
  tcase_add_test(tc, to_lower_test5);

  suite_add_tcase(s, tc);
  return s;
}