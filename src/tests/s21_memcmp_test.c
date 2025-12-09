#include "s21_test.h"

// Сравнивает две строки с n равным 0, должен вернуть 0, так как ни один байт не
// сравнивается
START_TEST(zero_byte) {
  char str1[] = "arraba";
  char str2[] = "arraba";
  int n = 0;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает первые 3 байта двух строк, должен вернуть результат функции memcmp
// для того же сравнения
START_TEST(first_byte_in_string) {
  char str1[] = "arraba";
  char str2[] = "arraba";
  int n = 3;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает первый байт двух строк, одна содержит строчную букву,
// а другая ту же самую букву в верхнем регистре.Проверяет корректность
// обработки регистра функцией
START_TEST(register_test) {
  char str1[] = "arraba";
  char str2[] = "Arraba";
  int n = 1;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает две однозначные цифры с n равным 0, должен вернуть 0, так как ни
// один байт не сравнивается
START_TEST(zero_byte_in_num) {
  char str1[] = "1";
  char str2[] = "1";
  int n = 0;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает первый байт однозначной цифры с первым байтом четырехзначной
// цифры. Проверяет корректность сравнения чисел функцией
START_TEST(first_byte_in_num) {
  char str1[] = "1";
  char str2[] = "1234";
  int n = 1;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает первые 2 байта двух четырехзначных чисел, должен вернуть результат
// функции memcmp для того же сравнения
START_TEST(two_byte_in_num) {
  char str1[] = "1234";
  char str2[] = "1234";
  int n = 2;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает первые 2 байта двузначного числа с четырехзначным числом.
// Проверяет корректность обработки чисел разной длины функцией
START_TEST(two_byte_long_two_num) {
  char str1[] = "13";
  char str2[] = "1234";
  int n = 2;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает первые 2 байта шестизначного числа с четырехзначным числом.
// Проверяет корректность обработки чисел разной длины функцией
START_TEST(two_byte_long_first_num) {
  char str1[] = "134567";
  char str2[] = "1234";
  int n = 2;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает две длинные строки из 71 символа каждая,
// включая буквы, цифры и пробелы. Проверяет корректность сравнения длинных
// строк функцией
START_TEST(eq_long_string) {
  char str1[] =
      "111111111111111111112312312312312312434524563567adsfe 4rafa ewfseASDASD";
  char str2[] =
      "111111111111111111112312312312312312434524563567adsfe 4rafa ewfseASDASD";
  int n = 71;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

// Сравнивает две длинные строки из 71 символа каждая,
// где последний символ отличается в одной из строк. Проверяет обнаружение
// различия и правильный результат функции
START_TEST(not_eq_long_string) {
  char str1[] =
      "111111111111111111112312312312312312434524563567adsfe 4rafa ewfseASDASD";
  char str2[] =
      "111111111111111111112312312312312312434524563567adsfe 4rafa ewfseASDASd";
  int n = 71;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

Suite *suite_s21_memcmp(void) {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc = tcase_create("memcmp_tc");

  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, first_byte_in_string);
  tcase_add_test(tc, register_test);
  tcase_add_test(tc, zero_byte_in_num);
  tcase_add_test(tc, first_byte_in_num);
  tcase_add_test(tc, two_byte_in_num);
  tcase_add_test(tc, two_byte_long_two_num);
  tcase_add_test(tc, two_byte_long_first_num);
  tcase_add_test(tc, eq_long_string);
  tcase_add_test(tc, not_eq_long_string);

  suite_add_tcase(s, tc);
  return s;
}