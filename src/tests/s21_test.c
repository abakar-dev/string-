#include "s21_test.h"

int main(void) {
  run_tests();
  return 0;
}

void run_tests(void) {
  Suite *list_cases[] = {suite_s21_sprintf(),  suite_s21_memchr(),
                         suite_s21_memcmp(),   suite_s21_memcpy(),
                         suite_s21_memset(),   suite_s21_strncat(),
                         suite_s21_strchr(),   suite_s21_strncmp(),
                         suite_s21_strncpy(),  suite_s21_to_upper(),
                         suite_s21_to_lower(), suite_s21_strcspn(),
                         suite_s21_strerror(), suite_s21_strlen(),
                         suite_s21_strpbrk(),  suite_s21_strrchr(),
                         suite_s21_strstr(),   suite_s21_strtok(),
                         suite_s21_sscanf(),   suite_s21_insert(),
                         suite_s21_trim(),     S21_NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;
  if (counter_testcase > 1) putchar('\n');
  printf("CURRENT TEST: %d\n", counter_testcase);
  counter_testcase++;

  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}
