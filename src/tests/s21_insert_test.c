#include "s21_test.h"

// проверяет вставку строки в середину исходной строки
START_TEST(test_insert_middle) {
  const char *src = "Hello, World!";
  const char *str = "Beautiful ";
  s21_size_t pos = 7;
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_str_eq(result, "Hello, Beautiful World!");

  free(result);
}
END_TEST

// проверяет вставку строки в начало исходной строки
START_TEST(test_insert_start) {
  const char *src = "World!";
  const char *str = "Hello, ";
  s21_size_t pos = 0;
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_str_eq(result, "Hello, World!");

  free(result);
}
END_TEST

// проверяет вставку строки в конец исходной строки
START_TEST(test_insert_end) {
  const char *src = "Hello, ";
  const char *str = "World!";
  s21_size_t pos = strlen(src);
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_str_eq(result, "Hello, World!");

  free(result);
}
END_TEST

// проверяет случай, когда вставляемая строка пустая
START_TEST(test_insert_empty_string) {
  const char *src = "Hello, World!";
  const char *str = "";
  s21_size_t pos = 5;
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_str_eq(result, "Hello, World!");

  free(result);
}
END_TEST

// проверяет вставку строки в пустую исходную строку
START_TEST(test_insert_into_empty_string) {
  const char *src = "";
  const char *str = "Hello!";
  s21_size_t pos = 0;
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_str_eq(result, "Hello!");

  free(result);
}
END_TEST

// проверяет поведение функции при попытке вставить строку в недопустимой
// позиции
START_TEST(test_insert_invalid_index) {
  const char *src = "Hello, World!";
  const char *str = "Beautiful ";
  s21_size_t pos = 50;
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_ptr_eq(result, NULL);
}
END_TEST

// проверяет обработку случая, когда исходная строка равна NULL.
START_TEST(test_insert_null_src) {
  const char *src = NULL;
  const char *str = "Hello!";
  s21_size_t pos = 0;
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_ptr_eq(result, NULL);
}
END_TEST

// проверяет обработку случая, когда вставляемая строка равна NULL.
START_TEST(test_insert_null_str) {
  const char *src = "Hello, World!";
  const char *str = NULL;
  s21_size_t pos = 5;
  char *result = (char *)s21_insert(src, str, pos);

  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *suite_s21_insert(void) {
  Suite *s = suite_create("s21_insert");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_insert_middle);
  tcase_add_test(tc_core, test_insert_start);
  tcase_add_test(tc_core, test_insert_end);
  tcase_add_test(tc_core, test_insert_empty_string);
  tcase_add_test(tc_core, test_insert_into_empty_string);
  tcase_add_test(tc_core, test_insert_invalid_index);
  tcase_add_test(tc_core, test_insert_null_src);
  tcase_add_test(tc_core, test_insert_null_str);

  suite_add_tcase(s, tc_core);

  return s;
}