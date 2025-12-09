#include "s21_test.h"

// проверяет, что если строка пустая, функция "s21_memchr"
// возвращает такой же результат, как и обычная функция "memchr"
START_TEST(empty_str) {
  s21_size_t n_byte = 1;
  char str[] = "";
  int find_byte = '\0';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

// проверяет, что если строка пустая, содержимое памяти
// также должно быть равным для функций "s21_memchr" и "memchr"
START_TEST(empty_str_mem_loc) {
  s21_size_t n_byte = 1;
  char str[] = "";
  int find_byte = '\0';

  ck_assert_mem_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte), n_byte);
}

END_TEST

// проверяет поведение функции при поиске символа после нулевого символа в
// строке
START_TEST(char_after_zero_symbol) {
  s21_size_t n_byte = 21;
  char str[] = "Shololo \0 LLLooololo";
  int find_byte = 'L';

  // ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
  //                  memchr(str, find_byte, n_byte));
  ck_assert_mem_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte), 1);
}
END_TEST

// проверяет поиск нулевого символа в строке
START_TEST(find_zero_in_string) {
  s21_size_t n_byte = 5;
  char str[] = "ollo";
  int find_byte = '\0';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

// проверяет поиск символа в начале строки
START_TEST(find_simbol_in_string_in_start) {
  s21_size_t n_byte = 10;
  char str[] = "Beliberda";
  int find_byte = 'B';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

// проверяет поиск символа в конце строки
START_TEST(find_simbol_in_string_in_end) {
  s21_size_t n_byte = 10;
  char str[] = "chop choP";
  int find_byte = 'P';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

// проверяет поиск числа в середине строки
START_TEST(find_num_in_string_in_mid) {
  s21_size_t n_byte = 25;
  char str[] = "hello worl111d salalalal";
  int find_byte = '1';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

// проверяет поиск числа в массиве чисел
START_TEST(find_num_in_array_num) {
  int array[] = {1, 2, 3, 42, 5, 99, 100};
  s21_size_t n_byte = sizeof(int) * 7;
  int find_byte = 42;

  ck_assert_ptr_eq(s21_memchr(array, find_byte, n_byte),
                   memchr(array, find_byte, n_byte));
}
END_TEST

// проверяет поиск числа с плавающей точкой в массиве чисел
START_TEST(find_float_in_array) {
  float array[] = {1, 2, 3, 42, 5, 99, 100};
  s21_size_t n_byte = sizeof(float) * 7;
  int find_byte = 42;

  ck_assert_ptr_eq(s21_memchr(array, find_byte, n_byte),
                   memchr(array, find_byte, n_byte));
}
END_TEST

// проверяет простой случай поиска символа в строке
START_TEST(easy_test_string) {
  s21_size_t n_byte = 7;
  char str[] = "sholom";
  int find_byte = 'c';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, n_byte),
                   memchr(str, find_byte, n_byte));
}
END_TEST

Suite *suite_s21_memchr(void) {
  Suite *s = suite_create("s21_memchr");
  TCase *tc = tcase_create("memchr_tc");

  tcase_add_test(tc, empty_str);
  tcase_add_test(tc, empty_str_mem_loc);
  tcase_add_test(tc, char_after_zero_symbol);
  tcase_add_test(tc, find_zero_in_string);
  tcase_add_test(tc, find_simbol_in_string_in_start);
  tcase_add_test(tc, find_simbol_in_string_in_end);
  tcase_add_test(tc, find_num_in_string_in_mid);
  tcase_add_test(tc, find_num_in_array_num);
  tcase_add_test(tc, find_float_in_array);
  tcase_add_test(tc, easy_test_string);

  suite_add_tcase(s, tc);
  return s;
}