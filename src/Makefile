SRC=$(wildcard s21_*.c)
TEST_SRC=$(wildcard tests/s21_*test.c)

OBJ=$(patsubst %.c,%.o,$(SRC))
TEST_OBJ=$(patsubst tests/%.c,%.o,$(TEST_SRC))
GCOV_TEST_OBJ=$(patsubst %, gcov_%, $(OBJ))

# CFLAGS=-Wall -Werror -Wextra -std=c11
CFLAGS=-Wall -Werror -Wextra -std=c11
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
TEST_FLAGS=-lcheck
OPEN=open
else ifeq ($(shell hostnamectl | grep -o 'Ubuntu'), Ubuntu)
TEST_FLAGS=-lpthread -lcheck  -Wno-nonnull -Wno-memset-transposed-args -lm -lsubunit
OPEN=open
else
TEST_FLAGS=-lpthread -lm -lcheck  -Wno-nonnull -Wno-memset-transposed-args
OPEN=xdg-open
endif
GCOV_FLAGS=-ftest-coverage --coverage
CC=gcc

all: s21_string.a

s21_string.a: $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

test: s21_string.a $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ)  s21_string.a -o ./s21_tests $(TEST_FLAGS)
	./s21_tests

gcov_report: s21_string.a $(GCOV_TEST_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(GCOV_TEST_OBJ) $(TEST_OBJ) -o ./gcov_unit_tests $(TEST_FLAGS)
	./gcov_unit_tests
	lcov -t "s21_string_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN) report/index.html

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: tests/%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(TEST_FLAGS)

gcov_%.o: %.c
	$(CC) -c $(CFLAGS) $(GCOV_FLAGS) $< -o ./$@ $(TEST_FLAGS)

clang-format:
	clang-format -i *.c *.h ./tests/*.c ./tests/*.h

clean:
	rm -rf report/
	rm -rf *.o *.a *.gcno *.gcda s21_tests gcov_unit_tests *.info
