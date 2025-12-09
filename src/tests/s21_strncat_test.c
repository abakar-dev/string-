#include "s21_test.h"

// проверяет, что функция s21_strncat правильно объединяет две строки, когда
// количество байт для объединения указано
START_TEST(test) {
  char src[] = "test";
  char res[3] = "";

  char expected[3] = "";
  s21_size_t n_byte = 2;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет, что функция s21_strncat правильно работает, когда обе строки пусты
START_TEST(all_empty) {
  char src[] = "";
  char res[] = "";
  char expected[] = "";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет,что функция s21_strncat не изменяет строку при объединении нулевого
// количества байт
START_TEST(zero_byte) {
  char src[] = "abosal";
  char res[10] = "";
  char expected[10] = "";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет,что функция s21_strncat добавляет указанное количество байт из
// пустой исходной строки к другой строке
START_TEST(empty_src) {
  char src[] = "";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 1;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет что функция s21_strncat правильно объединяет строки с заданным
// количеством байт
START_TEST(cd_abosa) {
  char src[] = "asdfaad";
  char res[12] = "cd";
  char expected[12] = "cd";
  s21_size_t n_byte = 5;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет  функция s21_strncat правильно добавляет указанное количество байт
// из одной строки к другой
START_TEST(string) {
  char src[] = "shalal";
  char res[25] = "alalak";
  char expected[25] = "alalak";
  s21_size_t n_byte = 6;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет  функция s21_strncat правильно добавляет указанное количество
// байт из одной строки к другой, когда это происходит в середине строки
START_TEST(BIGFLOPPA) {
  char src[] = "SHALALA";
  char res[25] = "LALALASHA";
  char expected[25] = "LALALASHA";
  s21_size_t n_byte = 5;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет что функция s21_strncat не изменяет строку при объединении нулевого
// количества байт
START_TEST(BIGFLOPPA2) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет что функция s21_strncat добавляет указанное количество
// байт из одной строки к другой, когда этот байт находится в начале строки
START_TEST(BIGFLOPPA3) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

// проверяет функция s21_strncat правильно объединяет строки с указанием
// большого количества байт
START_TEST(BIGFLOPPA4) {
  char src[] = "BIGFLOPPA";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 10;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

// проверяет что функция s21_strncat правильно добавляет символ с нулевым байтом
// к строке
START_TEST(zero_char) {
  char src[] = "\0";
  char res[25] = "BIGFLOPPA";
  char expected[25] = "BIGFLOPPA";
  s21_size_t n_byte = 1;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_str_eq(res, expected);
}
END_TEST

Suite *suite_s21_strncat(void) {
  Suite *s = suite_create("s21_strncat");
  TCase *tc = tcase_create("strncat_tc");

  tcase_add_test(tc, test);
  tcase_add_test(tc, all_empty);
  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, empty_src);
  tcase_add_test(tc, cd_abosa);
  tcase_add_test(tc, string);
  tcase_add_test(tc, BIGFLOPPA);
  tcase_add_test(tc, BIGFLOPPA2);
  tcase_add_test(tc, BIGFLOPPA3);
  tcase_add_test(tc, BIGFLOPPA4);
  tcase_add_test(tc, zero_char);

  suite_add_tcase(s, tc);
  return s;
}