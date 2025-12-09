#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef size_t s21_size_t;

#define S21_NULL NULL

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);

// sprintf

typedef struct numInfo {
  long double numOrig;
  long double num;
  long double numExponent;
  int negate;
  int isUpper;
  int type;

  int exponent;

  int len;
} numInfo;

typedef struct strInfo {
  int len;
  int maxLen;
  char *str;
} strInfo;

typedef struct specInfo {
  int fDefis;
  int fPlus;
  int fHashtag;
  int fZero;
  int fSpace;

  int width;
  int isWidth;

  int accuracy;
  int isAccuracy;

  char mods[3];

  char type[2];
} specInfo;

int s21_sprintf(char *buffer, const char *str, ...);

void strInfoIni(strInfo *str, int inputLen, int *errCode);
void strInfoMem(strInfo *str, int inputLen, int *errCode);
void strUnion(strInfo *str1, strInfo *str2, int *errCode);
void strUnionChar(strInfo *str1, char str2, int *errCode);
void strUnionStr(strInfo *str1, const char *str2, int strLen, int *errCode);
void strUnionToBuff(strInfo *str1, char *buff, int *buffCol);
void strUnionToBeginStr(strInfo *str1, const char *str2, int str2Len,
                        int *errCode);
numInfo numInfoIni(specInfo info, long double num, int *errCode);
void argInfoResult(strInfo *retStr, va_list *args, specInfo info, int *errCode);
void addEmptSpace(strInfo *retStr, specInfo info, int *errCode);
void strWithFlags(strInfo *retStr, char *str, specInfo info, int *errCode);
void ptrWithFlags(void *iptr, strInfo *result, int *errCode, specInfo info);
int flagStrComp(char f, char *posF, int posFCol);
void extractNum(specInfo info, va_list *args, int *errCode,
                long double *result);
void extractSignedInt(specInfo info, va_list *args, long double *arg);
void extractUnsignedInt(specInfo info, va_list *args, long double *arg);
void extractFloat(specInfo info, va_list *args, long double *arg);
void sysNumChange(numInfo *num, strInfo *result, specInfo info, int *errCode);
void eFormatNum(numInfo *num, strInfo *result, specInfo info, int *errCode);
void numUnitPart(numInfo *unit, strInfo *result, specInfo info, int *errCode);
void reverseSNC(numInfo *num, strInfo *result, specInfo info, int *errCode);
void numFracPart(numInfo *frac, strInfo *result, specInfo info, int *errCode);
void formatNum(numInfo *num, strInfo *result, specInfo info, int *errCode);
void myRoundLD(long double *num, int type, specInfo info);
int spec(const char *str, va_list *args, int *errCode, strInfo *returnStr);
int iniFlagSpec(const char *str, specInfo *info, int *errCode, va_list *args);
int iniWidthSpec(const char *str, specInfo *info, int *errCode, va_list *args);
int iniAccSpec(const char *str, specInfo *info, int *errCode, va_list *args);
int iniModSpec(const char *str, specInfo *info, int *errCode);
int iniTypeSpec(const char *str, specInfo *info, int *errCode);
int readNum(const char *str, int *lenNum);
char intToChar(int num, int isUpper);
int notEndStr(const char *str, int *errCode);
void swapCh(char *a, char *b);

// sscanf

int s21_sscanf(const char *str, const char *format, ...);

typedef struct {
  int bufPos;
  int pos;
  int minusFlag;
  int dotWidth;
  int error;
  int hLength;
  int lLength;
  int LLength;
  int unsignedOFlag;
  int unsignedUFlag;
  int flagP;
  int counter;
  int hexadecimalStep;
  int specifierCounter;
} specifierInfo;
void integerAndChar(va_list A, const char *buf, const char *format,
                    specifierInfo *info);
void floatAndHexadecimal(va_list A, const char *buf, const char *format,
                         specifierInfo *info);
// additions functions
void additions(const char *buf, const char *format, specifierInfo *info);
void star(specifierInfo *info, const char *buf);
void resetToZero(specifierInfo *info);
void plusAndMinusChecker(const char *buf, specifierInfo *info);
void widthParser(const char *format, specifierInfo *info);
void nCounter(va_list A, specifierInfo *info);
// char functions
void stringReader(va_list A, const char *buf, specifierInfo *info);
void symbolReader(va_list A, const char *buf, specifierInfo *info);
// integer functions
void integerProcessor(va_list A, const char *buf, specifierInfo *info);
void integerReader(va_list A, const char *buf, specifierInfo *info);
void integerReturner(va_list A, specifierInfo *info, long int *first);
void iSpecifier(va_list A, const char *buf, specifierInfo *info);
// float functions
void floatProcessor(va_list A, const char *buf, specifierInfo *info);
void floatReader(va_list A, const char *buf, specifierInfo *info);
void floatCountingFirst(const char *buf, specifierInfo *info,
                        long double *firstFloat, long double *secondFloat);
void floatCountingSecond(const char *buf, specifierInfo *info,
                         long double *firstFloat, long double *secondFloat,
                         int *counter);
void floatReturner(va_list A, specifierInfo *info, long double *firstFloat);
// hexadecimal functions
void hexadecimalProcessor(va_list A, const char *buf, specifierInfo *info);
void pointerReader(va_list A, const char *buf, specifierInfo *info);
void hexadecimalReader(const char *buf, specifierInfo *info,
                       unsigned long int *first);
void hexadecimalReaderWidth(const char *buf, specifierInfo *info,
                            unsigned long int *first);
void hexadecimalReturner(va_list A, specifierInfo *info,
                         unsigned long int *first);
void nullAndXChecker(const char *buf, specifierInfo *info, int *widthFlag);
#endif