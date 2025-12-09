#include "s21_test.h"

// проверяет корректность копирования строки из одной области памяти в другую с
// указанием количества копируемых ячеек памяти
START_TEST(cpy_test) {
  char src[] = "who cares?";
  s21_size_t mem_cells = 11;
  char res[mem_cells];
  char expected[] = "non__empty";

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// проверяет корректную обработку случая, когда количество копируемых ячеек
// памяти равно 0
START_TEST(zero_test_string) {
  char src[] = "aboba";
  s21_size_t mem_cells = 0;
  char res[mem_cells + 7];
  char expected[mem_cells + 7];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// проверяет корректную обработку случая, когда исходная строка пустая
START_TEST(any_empty) {
  char src[] = "";
  s21_size_t mem_cells = 1;
  char res[mem_cells];
  char expected[mem_cells];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// аналогично второму тесту, но также проверяет наличие регистра
START_TEST(zero_test_string_with_register) {
  char src[] = "I hate memcmp";
  s21_size_t mem_cells = 0;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// аналогично второму тесту, но с числами
START_TEST(zero_test_num) {
  char src[] = "123";
  s21_size_t mem_cells = 0;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// проверяет корректность копирования строки из одного символа
START_TEST(one_byte_string) {
  char src[] = "aboba";
  s21_size_t mem_cells = 1;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// аналогично предыдущему тесту, но также проверяет наличие регистра
START_TEST(one_byte_string_with_register) {
  char src[] = "Zboba";
  s21_size_t mem_cells = 1;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// аналогично предыдущему тесту, но с числами
START_TEST(one_byte_num) {
  char src[] = "09";
  s21_size_t mem_cells = 1;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// проверяет корректность копирования длинной строки
START_TEST(basic_long_string) {
  char src[] = "abobasdafoijasdofjas asdopij";
  s21_size_t mem_cells = 29;
  char res[mem_cells];
  char expected[mem_cells];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// аналогично предыдущему тесту, но также проверяет наличие регистра
START_TEST(long_string_with_register) {
  char src[] = "aposkd AOSIjFasodijpaoisdjf poisdjfg";
  s21_size_t mem_cells = 37;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// аналогично предыдущему тесту, но также проверяет наличие чисел
START_TEST(long_string_with_register_and_num) {
  char src[] = "aodasf ieuwfh luhasdfLIAUSHD liuh 12li3uh 12i4ouhsdfh";
  s21_size_t mem_cells = 54;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

// аналогично предыдущему тесту, но также проверяет наличие специальных символов
START_TEST(long_string_with_register_and_num_and_simbol) {
  char src[] =
      "()()(((())):!,....aodasf ieuwfh luhasdfLIAUSHD liuh 12li3uh 12i4ouhsdfh";
  s21_size_t mem_cells = 72;
  char res[mem_cells + 8];
  char expected[mem_cells + 8];

  s21_memcpy(res, src, mem_cells);
  memcpy(expected, src, mem_cells);

  ck_assert_mem_eq(res, expected, mem_cells);
}
END_TEST

Suite *suite_s21_memcpy(void) {
  Suite *s = suite_create("s21_memcpy");
  TCase *tc = tcase_create("memcpy_tc");

  tcase_add_test(tc, cpy_test);
  tcase_add_test(tc, zero_test_string);
  tcase_add_test(tc, any_empty);
  tcase_add_test(tc, zero_test_string_with_register);
  tcase_add_test(tc, zero_test_num);
  tcase_add_test(tc, one_byte_string);
  tcase_add_test(tc, one_byte_string_with_register);
  tcase_add_test(tc, one_byte_num);
  tcase_add_test(tc, basic_long_string);
  tcase_add_test(tc, long_string_with_register);
  tcase_add_test(tc, long_string_with_register_and_num);
  tcase_add_test(tc, long_string_with_register_and_num_and_simbol);

  suite_add_tcase(s, tc);
  return s;
}