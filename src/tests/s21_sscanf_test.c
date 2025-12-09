#include "s21_test.h"

START_TEST(sscanf_test_char_1) {
  char c1, c2;
  int result1 = s21_sscanf("a", "%c", &c1);
  int result2 = sscanf("a", "%c", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_char_2) {
  char c1, c2;
  int result1 = s21_sscanf(" ", "%c", &c1);
  int result2 = sscanf(" ", "%c", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST
#ifdef __linux__
START_TEST(sscanf_test_char_3) {
  char c1, c2;
  char c1_s21, c2_s21;
  int result1 = s21_sscanf(" a", "%c%c", &c1_s21, &c2_s21);
  int result2 = sscanf(" a", "%c%c", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
}
END_TEST

#endif

START_TEST(sscanf_test_str_1) {
  char c1[20];
  char c2[20];
  char *buffer = "Pfff";
  int result1 = s21_sscanf(buffer, "%s", c1);
  int result2 = sscanf(buffer, "%s", c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_str_2) {
  char c1[20];
  char c2[20];
  char *buffer = "Pfff\n";
  int result1 = s21_sscanf(buffer, "%s", c1);
  int result2 = sscanf(buffer, "%s", c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_str_3) {
  char c1[20];
  char c2[20];
  char *buffer = "Pff\nf";
  int result1 = s21_sscanf(buffer, "%s", c1);
  int result2 = sscanf(buffer, "%s", c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_str_4) {
  char c1[20];
  char c2[20];
  char *buffer = "Pff\tf";
  int result1 = s21_sscanf(buffer, "%s", c1);
  int result2 = sscanf(buffer, "%s", c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_str_5) {
  char c1[20];
  char c2[20];
  char *buffer = "Pfff";
  int result1 = s21_sscanf(buffer, "%9s", c1);
  int result2 = sscanf(buffer, "%9s", c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_int_1) {
  int c1, c2;
  int result1 = s21_sscanf("1", "%d", &c1);
  int result2 = sscanf("1", "%d", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_int_2) {
  int c1, c2;
  int result1 = s21_sscanf("1", "%i", &c1);
  int result2 = sscanf("1", "%i", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_int_3) {
  int c1, c2;
  int result1 = s21_sscanf("-1", "%u", &c1);
  int result2 = sscanf("-1", "%u", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_oct_1) {
  int c1, c2;
  int result1 = s21_sscanf("100", "%o", &c1);
  int result2 = sscanf("100", "%o", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_xeh_1) {
  int c1, c2;
  int result1 = s21_sscanf("100", "%x", &c1);
  int result2 = sscanf("100", "%x", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_xeh_2) {
  int c1, c2;
  int result1 = s21_sscanf("0x7ffff", "%x", &c1);
  int result2 = sscanf("0x7ffff", "%x", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_xeh_3) {
  int c1, c2;
  int result1 = s21_sscanf("0x7ffff", "%X", &c1);
  int result2 = sscanf("0x7ffff", "%X", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_xeh_4) {
  int c1, c2;
  int result1 = s21_sscanf("-f", "%x", &c1);
  int result2 = sscanf("-f", "%x", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_float_1) {
  float c1, c2;
  int result1 = s21_sscanf("5.5", "%f", &c1);
  int result2 = sscanf("5.5", "%f", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_float_2) {
  float c1, c2;
  int result1 = s21_sscanf("5.5", "%g", &c1);
  int result2 = sscanf("5.5", "%g", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_float_3) {
  float c1, c2;
  int result1 = s21_sscanf("5.5", "%e", &c1);
  int result2 = sscanf("5.5", "%e", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_float_4) {
  float c1, c2;
  float c1_s21, c2_s21;
  int result1 = s21_sscanf("5.55.5", "%3f%f", &c1_s21, &c2_s21);
  int result2 = sscanf("5.55.5", "%3f%f", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_float_5) {
  float c1, c2;
  float c1_s21, c2_s21;
  int result1 = s21_sscanf("5.55.5", "%5f%f", &c1_s21, &c2_s21);
  int result2 = sscanf("5.55.5", "%5f%f", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_float_6) {
  float c1, c2;
  float c1_s21, c2_s21;
  int result1 = s21_sscanf("5.55.5", "%1f%f", &c1_s21, &c2_s21);
  int result2 = sscanf("5.55.5", "%1f%f", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_float_7) {
  float c1, c2, c3;
  float c1_s21, c2_s21, c3_s21;
  int result1 = s21_sscanf("5.55.55.5", "%f%f%f", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf("5.55.55.5", "%f%f%f", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
  ck_assert_float_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_pointer_1) {
  void *c1;
  void *c2;
  char *buffer = "0xFFFF";
  int result1 = s21_sscanf(buffer, "%p", &c1);
  int result2 = sscanf(buffer, "%p", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_pointer_2) {
  void *c1_s21, *c2_s21;
  void *c1, *c2;
  char *buffer = "0xFFFF 0xAAAA";
  int result1 = s21_sscanf(buffer, "%p%p", &c1_s21, &c2_s21);
  int result2 = sscanf(buffer, "%p%p", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_ptr_eq(c1, c1_s21);
  ck_assert_ptr_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_number_1) {
  int c1, c2;
  char *buffer = "Pfff";
  int result1 = s21_sscanf(buffer, "%*s%n", &c1);
  int result2 = sscanf(buffer, "%*s%n", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_number_2) {
  int c1, c2;
  char *buffer = "Pfff";
  int result1 = s21_sscanf(buffer, "%n", &c1);
  int result2 = sscanf(buffer, "%n", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_number_3) {
  int c1, c2;
  int c1_s21, c2_s21;
  char *buffer = "Pfff fkdsj";
  int result1 = s21_sscanf(buffer, "%*s%n%*s%n", &c1_s21, &c2_s21);
  int result2 = sscanf(buffer, "%*s%n%*s%n", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_width_const_1) {
  int c1, c2;
  char *buffer = "65457";
  int result1 = s21_sscanf(buffer, "%3d", &c1);
  int result2 = sscanf(buffer, "%3d", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_width_const_2) {
  float c1, c2;
  char *buffer = "654.546";
  int result1 = s21_sscanf(buffer, "%4f", &c1);
  int result2 = sscanf(buffer, "%4f", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_width_const_3) {
  char c1[20];
  char c2[20];
  char *buffer = "Pffdf sdf";
  int result1 = s21_sscanf(buffer, "%7s", c1);
  int result2 = sscanf(buffer, "%7s", c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_int_h_1) {
  short int c1, c2;
  char *buffer = "54467841154";
  int result1 = s21_sscanf(buffer, "%hd", &c1);
  int result2 = sscanf(buffer, "%hd", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_int_l_1) {
  long int c1, c2;
  char *buffer = "54467841154";
  int result1 = s21_sscanf(buffer, "%ld", &c1);
  int result2 = sscanf(buffer, "%ld", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_test_float_l_1) {
  long double c1, c2;
  char *buffer = "54467841154.000";
  int result1 = s21_sscanf(buffer, "%Lf", &c1);
  int result2 = sscanf(buffer, "%Lf", &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_double_eq(c1, c2);
}
END_TEST
#ifdef __linux__
START_TEST(sscanf_test_few_specifier_1) {
  int c1, c2, c1_21, c2_21;
  char c3[20];
  char c3_21[20];
  char c4[20];
  char c4_21[20];
  char *buffer = "Why 42 is`t 2";
  int result1 = s21_sscanf(buffer, "%s%d%s%d", c3_21, &c1_21, c4_21, &c2_21);
  int result2 = sscanf(buffer, "%s%d%s%d", c3, &c1, c4, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_21);
  ck_assert_int_eq(c2, c2_21);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_2) {
  int c1, c2, c1_21, c2_21;
  char c4[20];
  char c4_21[20];
  char *buffer = "Why 42 is`t 2";
  int result1 = s21_sscanf(buffer, "%*s%d%s%d", &c1_21, c4_21, &c2_21);
  int result2 = sscanf(buffer, "%*s%d%s%d", &c1, c4, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_21);
  ck_assert_int_eq(c2, c2_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST
#endif

START_TEST(sscanf_test_few_specifier_3) {
  char c3[20];
  char c3_21[20];
  char c4[20];
  char c4_21[20];
  char *buffer = "Why not";
  int result1 = s21_sscanf(buffer, "%s%s", c3_21, c4_21);
  int result2 = sscanf(buffer, "%s%s", c3, c4);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST
#ifdef __linux__
START_TEST(sscanf_test_few_specifier_4) {
  char c3[20];
  char c3_21[20];
  char c4[20];
  char c4_21[20];
  char *buffer = "Why not";
  int result1 = s21_sscanf(buffer, "%2s%s", c3_21, c4_21);
  int result2 = sscanf(buffer, "%2s%s", c3, c4);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST
#endif

START_TEST(sscanf_test_few_specifier_5) {
  char c3[20];
  char c3_21[20];
  char c4[20];
  char c4_21[20];
  char *buffer = "Why not";
  int result1 = s21_sscanf(buffer, "%5s%9s", c3_21, c4_21);
  int result2 = sscanf(buffer, "%5s%9s", c3, c4);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_6) {
  char c3[20];
  char c3_21[20];
  char c4[20];
  char c4_21[20];
  char *buffer = "Why not";
  int result1 = s21_sscanf(buffer, "%9s%9s", c3_21, c4_21);
  int result2 = sscanf(buffer, "%9s%9s", c3, c4);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_7) {
  int c1, c1_21;
  char c3[20];
  char c3_21[20];
  char c4[20];
  char c4_21[20];
  char *buffer = "Why not";
  int result1 = s21_sscanf(buffer, "%9s%n%9s", c3_21, &c1_21, c4_21);
  int result2 = sscanf(buffer, "%9s%n%9s", c3, &c1, c4);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_21);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_8) {
  int c1, c1_21, c2, c2_21;
  char c3[20];
  char c3_21[20];
  char c4[20];
  char c4_21[20];
  char *buffer = "Why not";
  int result1 = s21_sscanf(buffer, "%10s%n%9s%n", c3_21, &c1_21, c4_21, &c2_21);
  int result2 = sscanf(buffer, "%10s%n%9s%n", c3, &c1, c4, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_21);
  ck_assert_int_eq(c2, c2_21);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_9) {
  char c3[20];
  char c3_21[20];
  char c4[20] = "shouldnt using";
  char c4_21[20] = "shouldnt using";
  char *buffer = "becouse";
  int result1 = s21_sscanf(buffer, "%9s%s", c3_21, c4_21);
  int result2 = sscanf(buffer, "%9s%s", c3, c4);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_10) {
  char c3[20];
  char c3_21[20];
  char c4[20] = "shouldnt using";
  char c4_21[20] = "shouldnt using";
  char *buffer = "becouse";
  int result1 = s21_sscanf(buffer, "%9s %s", c3_21, c4_21);
  int result2 = sscanf(buffer, "%9s %s", c3, c4);
  ck_assert_int_eq(result1, result2);
  ck_assert_str_eq(c3, c3_21);
  ck_assert_str_eq(c4, c4_21);
}
END_TEST
#ifdef __linux__
START_TEST(sscanf_test_few_specifier_11) {
  int c1, c2, c3, c1_s21, c2_s21, c3_s21;
  char *buffer = "150+600-700 123";
  int result1 = s21_sscanf(buffer, "%d%d%d", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%d%d%d", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
  ck_assert_int_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_12) {
  int c1, c2, c3, c1_s21, c2_s21, c3_s21;
  char *buffer = " 150  600 700";
  int result1 = s21_sscanf(buffer, "%d%d%d", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%d%d%d", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
  ck_assert_int_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_13) {
  int c1, c2, c3, c1_s21, c2_s21, c3_s21;
  char *buffer = "150+600-700";
  int result1 = s21_sscanf(buffer, "%d%d%d", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%d%d%d", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
  ck_assert_int_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_14) {
  char c1, c2, c3, c1_s21, c2_s21, c3_s21;
  char *buffer = "   a     b c d";
  int result1 = s21_sscanf(buffer, "%c%c%c", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%c%c%c", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
  ck_assert_int_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_15) {
  char c1, c2, c3, c1_s21, c2_s21, c3_s21;
  char *buffer = "\\\n\t\t\t";
  int result1 = s21_sscanf(buffer, "%c%c%c", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%c%c%c", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
  ck_assert_int_eq(c3, c3_s21);
}
END_TEST
#endif
START_TEST(sscanf_test_few_specifier_16) {
  float c1, c2, c3, c1_s21, c2_s21, c3_s21;
  char *buffer = "150.0+600-700";
  int result1 = s21_sscanf(buffer, "%f%f%f", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%f%f%f", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_int_eq(c1, c1_s21);
  ck_assert_int_eq(c2, c2_s21);
  ck_assert_int_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_17) {
  float c1 = 0.0, c2 = 0.0, c3 = 0.0, c1_s21 = 0.0, c2_s21 = 0.0, c3_s21 = 0.0;
  char *buffer = ". . .";
  int result1 = s21_sscanf(buffer, "%f%f%f", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%f%f%f", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
  ck_assert_float_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_few_specifier_18) {
  float c1, c2, c3, c1_s21, c2_s21, c3_s21;
  char *buffer = "inF InF inF INF";
  int result1 = s21_sscanf(buffer, "%G%G%G", &c1_s21, &c2_s21, &c3_s21);
  int result2 = sscanf(buffer, "%G%G%G", &c1, &c2, &c3);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
  ck_assert_float_eq(c3, c3_s21);
}
END_TEST

START_TEST(sscanf_test_format_substring_1) {
  float c1 = 0, c2 = 0, c1_s21 = 0, c2_s21 = 0;
  char *buffer = "%5.55.6";
  int result1 = s21_sscanf(buffer, "%%5%2f %f", &c1_s21, &c2_s21);
  int result2 = sscanf(buffer, "%%5%2f %f", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_format_substring_2) {
  float c1 = 0, c2 = 0, c1_s21 = 0, c2_s21 = 0;
  char *buffer = "485.5% 5.6";
  int result1 = s21_sscanf(buffer, "485%f  %% 5%f", &c1_s21, &c2_s21);
  int result2 = sscanf(buffer, "485%f  %% 5%f", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_format_substring_3) {
  float c1 = 0, c2 = 0, c1_s21 = 0, c2_s21 = 0;
  char *buffer = "485.5%5.6";
  int result1 = s21_sscanf(buffer, "485%f%%5%f", &c1_s21, &c2_s21);
  int result2 = sscanf(buffer, "485%f%%5%f", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
}
END_TEST

START_TEST(sscanf_test_format_substring_4) {
  float c1 = 0, c2 = 0, c1_s21 = 0, c2_s21 = 0;
  char *buffer = "485.5%5.6";
  int result1 = s21_sscanf(buffer, "4 8 5 %f %% 5%f", &c1_s21, &c2_s21);
  int result2 = sscanf(buffer, "4 8 5 %f %% 5%f", &c1, &c2);
  ck_assert_int_eq(result1, result2);
  ck_assert_float_eq(c1, c1_s21);
  ck_assert_float_eq(c2, c2_s21);
}
END_TEST

Suite *suite_s21_sscanf(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tcase = tcase_create("case_sprintf");

  tcase_add_test(tcase, sscanf_test_char_1);
  tcase_add_test(tcase, sscanf_test_char_2);
#ifdef __linux__
  tcase_add_test(tcase, sscanf_test_char_3);
#endif
  tcase_add_test(tcase, sscanf_test_str_1);
  tcase_add_test(tcase, sscanf_test_str_2);
  tcase_add_test(tcase, sscanf_test_str_3);
  tcase_add_test(tcase, sscanf_test_str_4);
  tcase_add_test(tcase, sscanf_test_str_5);
  tcase_add_test(tcase, sscanf_test_int_1);
  tcase_add_test(tcase, sscanf_test_int_2);
  tcase_add_test(tcase, sscanf_test_int_3);
  tcase_add_test(tcase, sscanf_test_oct_1);
  tcase_add_test(tcase, sscanf_test_xeh_1);
  tcase_add_test(tcase, sscanf_test_xeh_2);
  tcase_add_test(tcase, sscanf_test_xeh_3);
  tcase_add_test(tcase, sscanf_test_xeh_4);
  tcase_add_test(tcase, sscanf_test_float_1);
  tcase_add_test(tcase, sscanf_test_float_2);
  tcase_add_test(tcase, sscanf_test_float_3);
  tcase_add_test(tcase, sscanf_test_float_4);
  tcase_add_test(tcase, sscanf_test_float_5);
  tcase_add_test(tcase, sscanf_test_float_6);
  tcase_add_test(tcase, sscanf_test_float_7);
  tcase_add_test(tcase, sscanf_test_pointer_1);
  tcase_add_test(tcase, sscanf_test_pointer_2);
  tcase_add_test(tcase, sscanf_test_number_1);
  tcase_add_test(tcase, sscanf_test_number_2);
  tcase_add_test(tcase, sscanf_test_number_3);
  tcase_add_test(tcase, sscanf_test_width_const_1);
  tcase_add_test(tcase, sscanf_test_width_const_2);
  tcase_add_test(tcase, sscanf_test_width_const_3);
  tcase_add_test(tcase, sscanf_test_int_h_1);
  tcase_add_test(tcase, sscanf_test_int_l_1);
  tcase_add_test(tcase, sscanf_test_float_l_1);
#ifdef __linux__
  tcase_add_test(tcase, sscanf_test_few_specifier_1);

  tcase_add_test(tcase, sscanf_test_few_specifier_2);
#endif
  tcase_add_test(tcase, sscanf_test_few_specifier_3);
#ifdef __linux__
  tcase_add_test(tcase, sscanf_test_few_specifier_4);
#endif
  tcase_add_test(tcase, sscanf_test_few_specifier_5);
  tcase_add_test(tcase, sscanf_test_few_specifier_6);
  tcase_add_test(tcase, sscanf_test_few_specifier_7);
  tcase_add_test(tcase, sscanf_test_few_specifier_8);
  tcase_add_test(tcase, sscanf_test_few_specifier_9);
  tcase_add_test(tcase, sscanf_test_few_specifier_10);
#ifdef __linux__
  tcase_add_test(tcase, sscanf_test_few_specifier_11);
  tcase_add_test(tcase, sscanf_test_few_specifier_12);
  tcase_add_test(tcase, sscanf_test_few_specifier_13);
  tcase_add_test(tcase, sscanf_test_few_specifier_14);
  tcase_add_test(tcase, sscanf_test_few_specifier_15);
#endif
  tcase_add_test(tcase, sscanf_test_few_specifier_16);
  tcase_add_test(tcase, sscanf_test_few_specifier_17);
  tcase_add_test(tcase, sscanf_test_few_specifier_18);
  tcase_add_test(tcase, sscanf_test_format_substring_1);
  tcase_add_test(tcase, sscanf_test_format_substring_2);
  tcase_add_test(tcase, sscanf_test_format_substring_3);
  tcase_add_test(tcase, sscanf_test_format_substring_4);

  suite_add_tcase(s, tcase);
  return s;
}
