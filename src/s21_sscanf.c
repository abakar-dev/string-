#include "s21_string.h"

int s21_sscanf(const char *buf, const char *format, ...) {
  va_list A;
  specifierInfo info = {0};
  va_start(A, format);
  while (format[info.pos] != '\0') {
    if (buf[info.bufPos] == ' ' && format[info.pos + 1] != 'c' &&
        format[info.pos + 1] != 'n') {
      info.bufPos++;
    } else if (format[info.pos] == ' ') {
      info.pos++;
      continue;
    } else if (format[info.pos] == '%' &&
               !s21_memcmp(format + info.pos, "%%", 2)) {
      info.pos += 2;
      info.bufPos++;
      continue;
    } else if (format[info.pos] == '%') {
      info.pos++;
      if (format[info.pos] == ' ' || format[info.pos] == '0') break;
      additions(buf, format, &info);
      integerAndChar(A, buf, format, &info);
      floatAndHexadecimal(A, buf, format, &info);
    } else {
      info.pos++;
      info.bufPos++;
    }
  }

  va_end(A);
  return info.specifierCounter;
}

void additions(const char *buf, const char *format, specifierInfo *info) {
  if (format[info->pos] == '*') {
    star(info, buf);
  }
  if (format[info->pos] >= '1' && format[info->pos] <= '9') {  // %numbers
    widthParser(format, info);
  }
  if (format[info->pos] == 'h') {
    info->hLength = 1;
    info->pos++;
  }
  if (format[info->pos] == 'l') {
    if (format[info->pos + 1] == 'l') info->pos++;
    info->lLength = 1;
    info->pos++;
  }
  if (format[info->pos] == 'L') {
    info->LLength = 1;
    info->pos++;
  }
}

void integerAndChar(va_list A, const char *buf, const char *format,
                    specifierInfo *info) {
  if (format[info->pos] == 'c') {  // symbol
    symbolReader(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 's') {  // string
    stringReader(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 'd') {  // integer and unsigned integer
    integerProcessor(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 'i') {  // 8x 10x 16x integer
    iSpecifier(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 'o') {  // 8x signed integer
    info->unsignedOFlag = 1;
    integerProcessor(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 'u') {  // unsigned integer
    info->unsignedUFlag = 1;
    integerProcessor(A, buf, info);
    info->pos++;
  }
}

void floatAndHexadecimal(va_list A, const char *buf, const char *format,
                         specifierInfo *info) {
  if (format[info->pos] == 'e' || format[info->pos] == 'E' ||
      format[info->pos] == 'g' || format[info->pos] == 'G' ||
      format[info->pos] == 'f') {  // float variations
    floatProcessor(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 'x' ||
      format[info->pos] == 'X') {  // 16x unsigned integer
    hexadecimalProcessor(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 'p') {  // pointer
    info->flagP = 1;
    pointerReader(A, buf, info);
    info->pos++;
  }
  if (format[info->pos] == 'n') {  // specifier counter
    nCounter(A, info);
    info->pos++;
  }
}

void widthParser(const char *format, specifierInfo *info) {
  if (format[info->pos] >= '1' && format[info->pos] <= '9') {  // width
    int first = 0, second = 0;
    first = format[info->pos] - '0';
    while (format[info->pos + 1] >= '0' && format[info->pos + 1] <= '9') {
      first *= 10;
      second = format[info->pos + 1] - '0';
      first += second;
      info->pos++;
    }
    info->dotWidth = first;
    info->pos++;
  }
}

void star(specifierInfo *info, const char *buf) {
  while (buf[info->bufPos] != ' ' && buf[info->bufPos] != '\0') {
    info->bufPos++;
  }
  info->pos += 2;
}

void resetToZero(specifierInfo *info) {
  info->minusFlag = 0;
  info->dotWidth = 0;
  info->hLength = 0;
  info->lLength = 0;
  info->LLength = 0;
  info->counter = 0;
  info->unsignedOFlag = 0;
  info->unsignedUFlag = 0;
}

void plusAndMinusChecker(const char *buf, specifierInfo *info) {
  if (buf[info->bufPos] == '-') {
    info->minusFlag = 1;
    info->bufPos++;
    if (info->dotWidth > 0) info->dotWidth--;
  }
  if (buf[info->bufPos] == '+') info->bufPos++;
}

void nCounter(va_list A, specifierInfo *info) {
  int *counter = va_arg(A, int *);
  if (info->flagP)
    *counter = info->bufPos - 1;
  else
    *counter = info->bufPos;
}

void symbolReader(va_list A, const char *buf, specifierInfo *info) {
  s21_size_t q = 0;
  char *symbol = va_arg(A, char *);
  if (info->dotWidth == 0) {
    symbol[q] = buf[info->bufPos];
    info->bufPos++;
    info->specifierCounter++;
  } else {
    while (buf[info->bufPos] != '\0' && info->dotWidth--) {
      symbol[q] = buf[info->bufPos];
      q++;
      info->bufPos++;
    }
    info->specifierCounter++;
  }
}

void stringReader(va_list A, const char *buf, specifierInfo *info) {
  s21_size_t q = 0;
  int flag = 0;
  char *string = va_arg(A, char *);
  if (info->dotWidth == 0) {
    while (buf[info->bufPos] > 32) {
      flag = 1;
      string[q] = buf[info->bufPos];
      q++;
      string[q] = '\0';
      info->bufPos++;
    }
  } else {
    while (buf[info->bufPos] > 32 && info->dotWidth--) {
      flag = 1;
      string[q] = buf[info->bufPos];
      q++;
      string[q] = '\0';
      info->bufPos++;
    }
  }
  resetToZero(info);
  flag ? info->specifierCounter++ : 0;
}

void integerProcessor(va_list A, const char *buf, specifierInfo *info) {
  plusAndMinusChecker(buf, info);
  if (buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9') {
    integerReader(A, buf, info);
  } else if (buf[info->bufPos] == ' ') {
    info->specifierCounter--;
  }
  resetToZero(info);
}

void integerReader(va_list A, const char *buf, specifierInfo *info) {
  long int first = 0, second = 0;
  first = buf[info->bufPos] - '0';
  if (info->unsignedOFlag == 1 && first == 8) info->specifierCounter--;
  if (info->dotWidth == 0) {
    while (buf[info->bufPos + 1] >= '0' && buf[info->bufPos + 1] <= '9') {
      if (info->unsignedOFlag == 1)
        first *= 8;
      else
        first *= 10;
      second = buf[info->bufPos + 1] - '0';
      first += second;
      info->bufPos++;
    }
  } else {
    while (buf[info->bufPos + 1] >= '0' && buf[info->bufPos + 1] <= '9' &&
           info->dotWidth != 1) {
      if (info->unsignedOFlag == 1)
        first *= 8;
      else
        first *= 10;
      second = buf[info->bufPos + 1] - '0';
      first += second;
      info->bufPos++;
      info->dotWidth--;
    }
  }
  integerReturner(A, info, &first);
  info->bufPos++;
  info->specifierCounter++;
}

void integerReturner(va_list A, specifierInfo *info, long int *first) {
  if (info->hLength == 1) {
    short int *numberShort = va_arg(A, short int *);
    if (info->minusFlag) {
      *numberShort = -(*first);
    } else
      *numberShort = *first;
  } else if (info->lLength == 1) {
    long int *numberLong = va_arg(A, long int *);
    if (info->minusFlag) {
      *numberLong = -(*first);
    } else
      *numberLong = *first;
  } else if (info->unsignedOFlag == 1 || info->unsignedUFlag == 1) {
    unsigned int *numberUnsigned = va_arg(A, unsigned int *);
    if (info->minusFlag) {
      *numberUnsigned = -(*first);
    } else
      *numberUnsigned = *first;
  } else {
    int *number = va_arg(A, int *);
    if (info->minusFlag) {
      *number = -(*first);
    } else
      *number = *first;
  }
}

void iSpecifier(va_list A, const char *buf, specifierInfo *info) {
  if (buf[info->bufPos] == '0') {
    if (buf[info->bufPos + 1] == 'x' || buf[info->bufPos + 1] == 'X') {
      hexadecimalProcessor(A, buf, info);
    } else {
      info->unsignedOFlag = 1;
      integerProcessor(A, buf, info);
    }
  } else
    integerProcessor(A, buf, info);
}

void floatProcessor(va_list A, const char *buf, specifierInfo *info) {
  plusAndMinusChecker(buf, info);

  if ((buf[info->bufPos] == 'I' || buf[info->bufPos] == 'i') &&
      !(s21_memcmp(buf + info->bufPos, "INF", 3) &&
        s21_memcmp(buf + info->bufPos, "INf", 3) &&
        s21_memcmp(buf + info->bufPos, "Inf", 3) &&
        s21_memcmp(buf + info->bufPos, "InF", 3) &&
        s21_memcmp(buf + info->bufPos, "inf", 3) &&
        s21_memcmp(buf + info->bufPos, "iNF", 3) &&
        s21_memcmp(buf + info->bufPos, "inF", 3) &&
        s21_memcmp(buf + info->bufPos, "iNf", 3))) {
    float *number = va_arg(A, float *);
    if (info->minusFlag) {
      *number = -INFINITY;
    } else
      *number = INFINITY;
    info->bufPos += 3;
    info->specifierCounter++;
    return;
  }

  if ((buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9') ||
      buf[info->bufPos] == '.') {
    floatReader(A, buf, info);
  }
  resetToZero(info);
}

void floatReader(va_list A, const char *buf, specifierInfo *info) {
  int counter = 1;
  long double firstFloat = 0.0, secondFloat = 0.0;
  int flag = 1, flagCnt = 0;
  if (info->dotWidth == 0) {
    for (; buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9';
         info->bufPos++) {
      flagCnt++;
      floatCountingFirst(buf, info, &firstFloat, &secondFloat);
    }
    if (buf[info->bufPos] >= '.') {
      flag = 0;
      info->bufPos += 1;
      for (; buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9';
           info->bufPos++) {
        flagCnt++;
        floatCountingSecond(buf, info, &firstFloat, &secondFloat, &counter);
      }
    }
    if (buf[info->bufPos] == '.' && flag) {
      info->bufPos++;
      for (; buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9';
           info->bufPos++) {
        flagCnt++;
        floatCountingSecond(buf, info, &firstFloat, &secondFloat, &counter);
      }
    }
  } else {
    for (; buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9' &&
           info->dotWidth >= 1;
         info->bufPos++) {
      info->dotWidth--;
      flagCnt++;
      floatCountingFirst(buf, info, &firstFloat, &secondFloat);
    }
    if (!(buf[info->bufPos + 1] >= '0' && buf[info->bufPos + 1] <= '9'))
      info->dotWidth = 0;
    if (buf[info->bufPos + 1] >= '.' && info->dotWidth >= 1) {
      info->bufPos += 1;
      info->dotWidth--;
      for (; buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9' &&
             info->dotWidth--;
           info->bufPos++) {
        flagCnt++;
        floatCountingSecond(buf, info, &firstFloat, &secondFloat, &counter);
      }
    }
  }
  floatReturner(A, info, &firstFloat);
  // info->bufPos++;
  flagCnt ? info->specifierCounter++ : 0;
}

void floatCountingFirst(const char *buf, specifierInfo *info,
                        long double *firstFloat, long double *secondFloat) {
  *firstFloat *= 10;
  *secondFloat = buf[info->bufPos] - '0';
  *firstFloat += *secondFloat;
}

void floatCountingSecond(const char *buf, specifierInfo *info,
                         long double *firstFloat, long double *secondFloat,
                         int *counter) {
  *secondFloat = (buf[info->bufPos] - '0') / (pow(10, *counter));
  *firstFloat += *secondFloat;
  (*counter)++;
}

void floatReturner(va_list A, specifierInfo *info, long double *firstFloat) {
  if (info->LLength == 1) {
    long double *numberLong = va_arg(A, long double *);
    if (info->minusFlag == 1) {
      *numberLong = -(*firstFloat);
    } else
      *numberLong = *firstFloat;
  } else {
    float *number = va_arg(A, float *);
    if (info->minusFlag) {
      *number = -(*firstFloat);
    } else
      *number = *firstFloat;
  }
}

void hexadecimalProcessor(va_list A, const char *buf, specifierInfo *info) {
  int widthFlag = 0;
  info->hexadecimalStep = -1;
  unsigned long int first = 0;
  plusAndMinusChecker(buf, info);
  nullAndXChecker(buf, info, &widthFlag);
  const char *s = &buf[info->bufPos];
  for (; *s != ' ' && *s != '\0'; info->hexadecimalStep++) s++;
  if (info->dotWidth == 0) {
    hexadecimalReader(buf, info, &first);
  } else {
    for (; *s != ' ' && *s != '\0'; info->hexadecimalStep++) s++;
    if (info->hexadecimalStep >= info->dotWidth)
      info->hexadecimalStep = info->dotWidth - 1;
    hexadecimalReaderWidth(buf, info, &first);
  }
  hexadecimalReturner(A, info, &first);
  info->bufPos++;
  resetToZero(info);
  info->specifierCounter++;
}

void hexadecimalReader(const char *buf, specifierInfo *info,
                       unsigned long int *first) {
  unsigned long int second = 0;
  while (buf[info->bufPos] != ' ' && buf[info->bufPos] != '\0') {
    if (buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9') {
      second = (buf[info->bufPos] - '0') * pow(16, info->hexadecimalStep);
      *first += second;
    } else if (buf[info->bufPos] >= 'A' && buf[info->bufPos] <= 'Z') {
      second = ((buf[info->bufPos] - 65) + 10) * pow(16, info->hexadecimalStep);
      *first += second;
    } else if (buf[info->bufPos] >= 'a' && buf[info->bufPos] <= 'z') {
      second = ((buf[info->bufPos] - 97) + 10) * pow(16, info->hexadecimalStep);
      *first += second;
    } else {
      break;
    }
    info->hexadecimalStep--;
    info->bufPos++;
  }
}

void hexadecimalReaderWidth(const char *buf, specifierInfo *info,
                            unsigned long int *first) {
  unsigned long int second = 0;
  while (buf[info->bufPos] != ' ' && buf[info->bufPos] != '\0' &&
         info->dotWidth >= 1) {
    if ((buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9') ||
        (buf[info->bufPos] >= 'A' && buf[info->bufPos] <= 'F') ||
        (buf[info->bufPos] >= 'a' && buf[info->bufPos] <= 'f')) {
      if (buf[info->bufPos] >= '0' && buf[info->bufPos] <= '9') {
        second = (buf[info->bufPos] - '0') * pow(16, info->hexadecimalStep);
      } else if (buf[info->bufPos] >= 'A' && buf[info->bufPos] <= 'F') {
        second =
            ((buf[info->bufPos] - 'A') + 10) * pow(16, info->hexadecimalStep);
      } else if (buf[info->bufPos] >= 'a' && buf[info->bufPos] <= 'f') {
        second =
            ((buf[info->bufPos] - 'a') + 10) * pow(16, info->hexadecimalStep);
      }
      *first += second;
      if (info->dotWidth != 0) info->dotWidth--;
    } else {
      break;
    }
    info->hexadecimalStep--;
    info->bufPos++;
  }
}

void hexadecimalReturner(va_list A, specifierInfo *info,
                         unsigned long int *first) {
  if (info->hLength == 1) {
    unsigned short int *numberShort = va_arg(A, unsigned short int *);
    if (info->minusFlag) {
      *numberShort = (unsigned short int)-(*first);
    } else {
      *numberShort = (unsigned short int)(*first);
    }
  } else if (info->lLength == 1) {
    unsigned long int *numberLong = va_arg(A, unsigned long int *);
    if (info->minusFlag) {
      *numberLong = (long int)-(*first);
    } else {
      *numberLong = *first;
    }
  } else {
    unsigned int *number = va_arg(A, unsigned int *);
    if (info->minusFlag) {
      *number = (unsigned int)-(*first);
    } else {
      *number = (unsigned int)(*first);
    }
  }
}

void pointerReader(va_list A, const char *buf, specifierInfo *info) {
  int widthFlag = 0;
  info->hexadecimalStep = -1;
  unsigned long int first = 0;
  plusAndMinusChecker(buf, info);
  nullAndXChecker(buf, info, &widthFlag);
  const char *s = &buf[info->bufPos];
  for (; *s != ' ' && *s != '\0'; info->hexadecimalStep++) s++;
  if (info->dotWidth == 0 && widthFlag == 0) {
    hexadecimalReader(buf, info, &first);
  } else {
    for (; *s != ' ' && *s != '\0'; info->hexadecimalStep++) s++;
    if (info->hexadecimalStep >= info->dotWidth)
      info->hexadecimalStep = info->dotWidth - 1;
    hexadecimalReaderWidth(buf, info, &first);
  }
  void **number = va_arg(A, void **);
  *number = (void *)(0x0 + first);
  info->bufPos++;
  resetToZero(info);
  info->specifierCounter++;
}

void nullAndXChecker(const char *buf, specifierInfo *info, int *widthFlag) {
  if (buf[info->bufPos] == '0' &&
      (buf[info->bufPos + 1] == 'x' || buf[info->bufPos + 1] == 'X')) {
    info->bufPos += 2;
    if (info->dotWidth != 0) {
      info->dotWidth -= 2;
      if (info->dotWidth == 0) *widthFlag = 1;
    }
  }
}