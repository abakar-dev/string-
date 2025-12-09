#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

Suite *suite_s21_sprintf(void);
Suite *suite_s21_memchr(void);
Suite *suite_s21_memcmp(void);
Suite *suite_s21_memcpy(void);
Suite *suite_s21_memset(void);
Suite *suite_s21_strncat(void);
Suite *suite_s21_strchr(void);
Suite *suite_s21_strncmp(void);
Suite *suite_s21_strncpy(void);
Suite *suite_s21_to_upper(void);
Suite *suite_s21_to_lower(void);
Suite *suite_s21_strcspn(void);
Suite *suite_s21_strerror(void);
Suite *suite_s21_strlen(void);
Suite *suite_s21_strpbrk(void);
Suite *suite_s21_strrchr(void);
Suite *suite_s21_strstr(void);
Suite *suite_s21_strtok(void);
Suite *suite_s21_insert(void);
Suite *suite_s21_trim(void);
Suite *suite_s21_sscanf(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // S21_TESTS_H
