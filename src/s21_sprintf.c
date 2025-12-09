#include "s21_string.h"

int s21_sprintf(char *buffer, const char *str, ...) {
  int errCode = 0, buffLen = 0, stop = 0;
  va_list args;
  strInfo specStr;

  va_start(args, str);
  strInfoIni(&specStr, 256, &errCode);
  for (int i = 0; !stop && str[i] != '\0'; i++) {
    if (str[i] != '%') {
      buffer[buffLen] = str[i];
      buffLen++;
    } else {
      i += spec(str + i, &args, &errCode, &specStr);
      if (!errCode) strUnionToBuff(&specStr, buffer, &buffLen);
      i--;
    }
    if (errCode != 0 && errCode != 29) {  // код ошибки
      stop = 1;  // если неизвестный спецификатор то пропуститьь и продолжить?
    } else {
      errCode = 0;  // warning
    }
  }
  buffer[buffLen] = '\0';
  va_end(args);
  strInfoMem(&specStr, 0, &errCode);
  if (errCode) printf("|errCode %d|", errCode);  // deb
  return buffLen;
}

void strInfoIni(strInfo *str, int inputLen, int *errCode) {
  if (*errCode == 0) {
    str->maxLen = inputLen;
    str->len = 0;
    /* cppcheck-suppress cstyleCast */
    str->str = (char *)calloc(inputLen, sizeof(char));  // функция из stdlib.h
    if (str->str == NULL) {
      (*errCode) = 222;  // код ошибки
    } else {
      str->str[0] = '\0';
    }
  }
}

void strInfoMem(strInfo *str, int inputLen, int *errCode) {
  if (inputLen < 0) inputLen *= -1;
  if (!(*errCode) && inputLen > 0) {
    /* cppcheck-suppress cstyleCast */
    char *newStr = (char *)realloc(str->str, inputLen);
    if ((newStr) == NULL) {
      (*errCode) = 234;  // код ошибки
    } else {
      str->str = newStr;
      str->maxLen = inputLen;
      if (inputLen < str->len) str->len = inputLen;
    }
  } else if (inputLen == 0) {
    free(str->str);
    str->str = NULL;
    str->len = 0;
    str->maxLen = 0;
  }
}

void strUnion(strInfo *str1, strInfo *str2, int *errCode) {
  while (!(*errCode) && (str1->len + str2->len + 5) >= str1->maxLen) {
    strInfoMem(str1, (str1->len) * 2, errCode);
  }
  if (!(*errCode)) {
    for (int i = 0; i < str2->len; i++) {
      str1->str[str1->len] = str2->str[i];
      (str1->len)++;
    }
    strInfoMem(str2, 0, errCode);
  }
}

void strUnionChar(strInfo *str1, char str2, int *errCode) {
  while (!(*errCode) && (str1->len + 6) >= str1->maxLen) {
    strInfoMem(str1, (str1->len) * 2, errCode);
  }
  if (!(*errCode)) {
    str1->str[str1->len] = str2;
    (str1->len)++;
  }
}

void strUnionStr(strInfo *str1, const char *str2, int strLen, int *errCode) {
  for (int i = 0; !(*errCode) && i < strLen; i++) {
    strUnionChar(str1, str2[i], errCode);
  }
}

void strUnionToBuff(strInfo *str1, char *buff, int *buffCol) {
  for (int i = 0; i < str1->len; i++, (*buffCol)++) {
    buff[(*buffCol)] = str1->str[i];
  }
  str1->len = 0;
}

void strUnionToBeginChar(strInfo *str1, char str2, int *errCode) {
  strUnionChar(str1, str2, errCode);
  for (int i = str1->len - 1; !(*errCode) && i > 0; i--)
    swapCh(&(str1->str[i]), &(str1->str[i - 1]));
}

void strUnionToBeginStr(strInfo *str1, const char *str2, int str2Len,
                        int *errCode) {
  strUnionStr(str1, str2, str2Len, errCode);
  for (int i = (str1->len) - 1; i >= str2Len; i--) {
    swapCh(&(str1->str[i]), &(str1->str[i - str2Len]));
  }
  for (int i = 0; !(*errCode) && i < str2Len; i++) {
    str1->str[i] = str2[i];
  }
}

void argInfoResult(strInfo *retStr, va_list *args, specInfo info,
                   int *errCode) {
  if (info.type[0] == '%') {
    retStr->len = 1;
    retStr->str[0] = '%';
  } else if (info.type[0] == 'c') {
    retStr->len = 1;
    char sym = (char)va_arg((*args), int);
    retStr->str[0] = sym;
  } else if (info.type[0] == 's') {
    strWithFlags(retStr, va_arg((*args), char *), info, errCode);
  } else if (info.type[0] == 'p') {
    void *ptr = va_arg((*args), void *);
    ptrWithFlags(ptr, retStr, errCode, info);
    /*} else if (flagStrComp(info.type[0], "eEgG", 2)) {
      strUnionChar(retStr, '&', errCode); */
  } else {
    long double lNum = 0L;
    extractNum(info, args, errCode, &lNum);
    numInfo dNum = numInfoIni(info, lNum, errCode);
    sysNumChange(&dNum, retStr, info, errCode);
  }
  addEmptSpace(retStr, info, errCode);
}

numInfo numInfoIni(specInfo info, long double num, int *errCode) {
  numInfo newNum;
  newNum.len = 0;
  newNum.exponent = 0;
  newNum.numOrig = num;
  newNum.type = info.type[0] == 'o' ? 8 : 10;
  if (flagStrComp(info.type[0], "xsXp", 4)) newNum.type = 16;
  newNum.isUpper = flagStrComp(info.type[0], "GEX", 3);
  newNum.negate = (num < 0);
  newNum.num = num * ((newNum.negate) ? -1 : 1);
  myRoundLD(&(newNum.num), newNum.type, info);
  newNum.numExponent = newNum.num;
  while (!(*errCode) && newNum.numExponent >= 10L)
    newNum.numExponent /= 10, newNum.exponent++;
  while (!(*errCode) && newNum.numExponent < 1L && newNum.numExponent != 0L)
    newNum.numExponent *= 10, newNum.exponent--;
  return newNum;
}

void myRoundLD(long double *num, int type, specInfo info) {
  long double fracPart = 1L, numCopy = (*num);
  if (flagStrComp(info.type[0], "gGeE", 4)) {
    while (numCopy >= 10L) fracPart *= type, numCopy /= type;
    while (numCopy < 1L && numCopy != 0) fracPart /= type, numCopy *= type;
    if (flagStrComp(info.type[0], "gG", 2)) info.accuracy--;
  }
  for (int i = 0; i <= info.accuracy; i++)
    fracPart /= type, numCopy *= type;  // type или 10?
  if (fmodl(numCopy, (long double)type) >= (long double)(type / 2)) {
    (*num) += fracPart * (type - (int)fmodl(numCopy, (long double)type));
  }
}

void addEmptSpace(strInfo *retStr, specInfo info, int *errCode) {
  int lenPast = retStr->len;
  char empt = (info.fZero) ? '0' : ' ';  // если приставка 0 или 0x то ' '
  /*if(flagStrComp(info.type[0], "xX", 2) && info.fHashtag) {
    strUnionChar(retStr, info.type[0], errCode);
    strUnionChar(retStr, '0', errCode);
    lenSpace += 2;
    lenPast += 2;
  }*/ // переделать для префикс вывода
  if (info.isWidth && !(*errCode)) {
    int lenSpace = 0;
    if (flagStrComp(info.type[0], "diouxX", 6) && info.isAccuracy) empt = ' ';
    for (int i = retStr->len; i < info.width; i++) {
      strUnionChar(retStr, empt, errCode);
      lenSpace++;
    }
    for (int i = lenPast - 1; i >= 0 && !(info.fDefis); i--) {
      swapCh(&(retStr->str[i]), &(retStr->str[i + lenSpace]));
    }  // доделать
  }
}

void strWithFlags(strInfo *retStr, char *str, specInfo info, int *errCode) {
  int lenWF = 0, i;

  for (; str[lenWF] != '\0' && ((lenWF < info.accuracy) || !(info.isAccuracy));
       lenWF++)
    ;
  for (i = 0; !(*errCode) && i < lenWF; i++) {
    strUnionChar(retStr, str[i], errCode);
  }
}

void ptrWithFlags(void *iptr, strInfo *result, int *errCode, specInfo info) {
  //? проверить функцию
  unsigned long long int usIntPtr = (unsigned long long int)iptr;
  numInfo numPtr = numInfoIni(info, (long double)usIntPtr, errCode);
  sysNumChange(&numPtr, result, info, errCode);
  for (int i = result->len; i < info.accuracy && info.isAccuracy; i++)
    strUnionChar(result, '0', errCode);
  strUnionChar(result, 'x', errCode);
  strUnionChar(result, '0', errCode);
  for (int j = 0; j * 2 < result->len; j++)
    swapCh(&(result->str[j]), &(result->str[result->len - j - 1]));
}

int flagStrComp(char f, char *posF, int posFCol) {
  int coin = 0;
  for (int i = 0; i < posFCol && !coin && posF[i] != '\0'; i++) {
    coin = (f == posF[i]) ? 1 : 0;
  }
  return coin;
}

void extractNum(specInfo info, va_list *args, int *errCode,
                long double *result) {
  if (flagStrComp(info.type[0], "di", 2)) {
    extractSignedInt(info, args, result);
  } else if (flagStrComp(info.type[0], "uoxX", 4)) {
    extractUnsignedInt(info, args, result);
  } else if (flagStrComp(info.type[0], "feEgG", 5)) {
    extractFloat(info, args, result);
  } else {
    *errCode = 122;  // код ошибки
  }
}

void extractSignedInt(specInfo info, va_list *args, long double *arg) {
  if (info.mods[0] == 'h' && info.mods[1] == 'h') {
    (*arg) = (long double)(signed char)(va_arg((*args), int));
  } else if (info.mods[0] == 'h') {
    (*arg) = (long double)(short)(va_arg((*args), int));
  } else if (info.mods[0] == 'l' && info.mods[1] == 'l') {
    (*arg) = (long double)(va_arg((*args), long long int));
  } else if (info.mods[0] == 'l') {
    (*arg) = (long double)(va_arg((*args), long int));
  } else if (info.mods[0] == 'L') {  // warning
    (*arg) = (long double)(va_arg((*args), long long int));
  } else {
    (*arg) = (long double)(va_arg((*args), int));
  }
}

void extractUnsignedInt(specInfo info, va_list *args, long double *arg) {
  if (info.mods[0] == 'h' && info.mods[1] == 'h') {
    (*arg) = (long double)(unsigned char)(va_arg((*args), int));
  } else if (info.mods[0] == 'h') {
    (*arg) = (long double)(unsigned short)(va_arg((*args), unsigned int));
  } else if (info.mods[0] == 'l' && info.mods[1] == 'l') {
    (*arg) = (long double)(va_arg((*args), unsigned long long int));
  } else if (info.mods[0] == 'l') {
    (*arg) = (long double)(va_arg((*args), unsigned long int));
  } else if (info.mods[0] == 'L') {  // warning
    (*arg) = (long double)(va_arg((*args), unsigned long long int));
  } else {
    (*arg) = (long double)(va_arg((*args), unsigned int));
  }
}

void extractFloat(specInfo info, va_list *args, long double *arg) {
  if (info.mods[0] == 'L') {
    (*arg) = (long double)(va_arg((*args), long double));
  } else if (info.mods[0] != 'h' && info.mods[0] != 'l') {
    (*arg) = (long double)(va_arg((*args), double));
  } else {  // warning
    (*arg) = (long double)(va_arg((*args), double));
  }
}

void sysNumChange(numInfo *num, strInfo *result, specInfo info, int *errCode) {
  int P = (info.accuracy) ? info.accuracy : 1;
  int ans = (P > num->exponent && num->exponent >= -4);
  if (flagStrComp(info.type[0], "eE", 2)) {
    eFormatNum(num, result, info, errCode);
  } else if (flagStrComp(info.type[0], "gG", 2) && !ans) {
    info.accuracy = P - 1;
    eFormatNum(num, result, info, errCode);
  } else if (flagStrComp(info.type[0], "gG", 2) && ans) {
    info.accuracy = P - 1 - num->exponent;
    numUnitPart(num, result, info, errCode);
    reverseSNC(num, result, info, errCode);
    numFracPart(num, result, info, errCode);
    formatNum(num, result, info, errCode);
  } else {
    numUnitPart(num, result, info, errCode);
    reverseSNC(num, result, info, errCode);
    numFracPart(num, result, info, errCode);
    formatNum(num, result, info, errCode);
  }
}

void eFormatNum(numInfo *num, strInfo *result, specInfo info, int *errCode) {
  num->len = 0;
  int pointCount = 0, zeroCount = 0, i;
  if (num->negate) strUnionChar(result, '-', errCode);
  if (!(num->negate) && info.fPlus) strUnionChar(result, '+', errCode);
  if (!(num->negate) && info.fSpace) strUnionChar(result, ' ', errCode);
  int sym = fmodl(num->numExponent, num->type);  // функция из math
  char ch = intToChar(sym, num->isUpper);
  strUnionChar(result, ch, errCode);
  if (info.fHashtag) strUnionChar(result, '.', errCode);
  for (i = 0; i < info.accuracy; i++) {
    num->numExponent *= 10;
    sym = fmodl(num->numExponent, num->type);
    ch = intToChar(sym, num->isUpper);
    if (ch == '0') zeroCount++;
    if (zeroCount == i && !(info.fHashtag) && !pointCount) {
      strUnionChar(result, '.', errCode);
      pointCount++;
    }
    for (; ch != '0' && zeroCount > 0; zeroCount--)
      strUnionChar(result, '0', errCode);
    if (ch != '0') strUnionChar(result, ch, errCode);
  }
  if (!(info.fHashtag) && zeroCount && !pointCount) {
    strUnionChar(result, '.', errCode);
  }
  for (; zeroCount > 0; zeroCount--)
    strUnionChar(result, '0', errCode);  // отмена непечати незначащих нулей
  strUnionChar(result, (num->isUpper ? 'E' : 'e'), errCode);
  strUnionChar(result, (num->exponent >= 0 ? '+' : '-'), errCode);
  int expABS = num->exponent > 0 ? num->exponent : -(num->exponent);
  char exp[5] = "0000";
  for (int div = 1, i = 3; i >= 0; i--, div *= 10)
    exp[i] = '0' + ((expABS / div) % 10);
  for (int notFZero = 0, i = 0; i < 4; i++) {
    if ((!notFZero && exp[i] != '0') || (i == 2)) notFZero++;
    if (notFZero) strUnionChar(result, exp[i], errCode);
  }
}

void numUnitPart(numInfo *unit, strInfo *result, specInfo info, int *errCode) {
  unit->len = 0;
  long double numCp = unit->num;

  for (; !(*errCode) && numCp >= 1L; unit->len++, numCp /= unit->type) {
    int sym = fmodl(numCp, unit->type);  // функция из math
    char ch = intToChar(sym, unit->isUpper);
    strUnionChar(result, ch, errCode);
  }
  if (!(*errCode) && unit->len == 0) {
    strUnionChar(result, '0', errCode);
    unit->len++;
  }
  if (flagStrComp(info.type[0], "duoxX", 5) && info.isAccuracy) {
    for (; !(*errCode) && unit->len < info.accuracy; unit->len++)
      strUnionChar(result, '0', errCode);
  }
}

void reverseSNC(numInfo *num, strInfo *result, specInfo info, int *errCode) {
  int count = num->len;
  if (!(*errCode) && info.type[0] != 'p') {
    if (count <= 0) {
      result->len = 1;
      result->str[0] = '0';
    }
    for (int j = 0; j * 2 < count; j++)
      swapCh(&(result->str[j]), &(result->str[count - j - 1]));
  }
}

void numFracPart(numInfo *frac, strInfo *result, specInfo info, int *errCode) {
  long double numCp = frac->num;
  if (!(*errCode) && (info.accuracy > 0 || info.fHashtag) &&
      flagStrComp(info.type[0], "feEgG", 5)) {  // условие?
    int count = 0, ZCount = 0;
    strUnionChar(result, '.', errCode);
    for (; !(*errCode) && info.accuracy > count; count++) {
      numCp *= frac->type;
      int fracRes = fmodl(numCp, frac->type);  // функция из math
      char ch = intToChar(fracRes, frac->isUpper);
      for (; !(*errCode) && ch != '0' && ZCount; ZCount--)
        strUnionChar(result, '0', errCode);
      if (ch != '0') {
        strUnionChar(result, ch, errCode);
      } else {
        ZCount++;
      }
    }
    if (info.type[0] == 'f' ||
        (flagStrComp(info.type[0], "gG", 2) && info.fHashtag)) {
      for (; !(*errCode) && ZCount; ZCount--)
        strUnionChar(result, '0', errCode);  // deb */
    }
    if (result->str[result->len - 1] == '.' && !(info.fHashtag))
      (result->len)--;  // удаление точки, если без хештег флага и нет нулей
  }
}

void formatNum(numInfo *num, strInfo *result, specInfo info, int *errCode) {
  int firstMinus = num->negate;
  if (!(*errCode) && info.fHashtag) {
    if (info.type[0] == 'o' && result->str[0] != '0') {
      strUnionToBeginChar(result, '0', errCode);
    } else if (info.type[0] == 'x') {
      strUnionToBeginStr(result, "0x", 2, errCode);
    } else if (info.type[0] == 'X') {
      strUnionToBeginStr(result, "0X", 2, errCode);
    }
  }
  if (!(*errCode) && flagStrComp(info.type[0], "difeEgG", 7)) {
    if (firstMinus) {
      strUnionToBeginChar(result, '-', errCode);
    } else if (info.fPlus) {
      strUnionToBeginChar(result, '+', errCode);
    } else if (info.fSpace) {  // с fZero конфликт
      strUnionToBeginChar(result, ' ', errCode);
    }
  }
}

int spec(const char *str, va_list *args, int *errCode, strInfo *returnStr) {
  int specLen = 1;
  specInfo info;
  if (!(*errCode)) {
    specLen += iniFlagSpec(str + 1, &info, errCode, args);  //+1?
    if (!(*errCode)) {
      argInfoResult(returnStr, args, info, errCode);
    }
  }
  return specLen;
}

int iniFlagSpec(const char *str, specInfo *info, int *errCode, va_list *args) {
  int flagCount = 0;
  info->fDefis = 0;
  info->fHashtag = 0;
  info->fPlus = 0;
  info->fZero = 0;
  info->fSpace = 0;
  notEndStr(str, errCode);
  for (int isFlag = 1; isFlag && notEndStr(str + flagCount, errCode);) {
    if (flagStrComp(str[flagCount], "+-#0 ", 5)) {
      info->fPlus += str[flagCount] == '+' ? 1 : 0;
      info->fDefis += str[flagCount] == '-' ? 1 : 0;
      info->fHashtag += str[flagCount] == '#' ? 1 : 0;
      info->fZero += str[flagCount] == '0' ? 1 : 0;
      info->fSpace += str[flagCount] == ' ' ? 1 : 0;
      flagCount++;
    } else {
      isFlag = 0;
    }
  }
  if (info->fPlus && info->fSpace) {
    //(*errCode) = ;  //код ошибки
    info->fSpace = 0;  // deb
  } else if (info->fZero) {
    if (notEndStr(str + flagCount, errCode) &&
        flagStrComp(str[flagCount], ".", 9) && str[flagCount - 1] == '0') {
      info->fZero--;
      flagCount--;  // если '0' перед '.' это точно ширина
    }
    if (!(errCode) && info->fDefis && info->fZero)
      //(*errCode) = ;  //код ошибки
      info->fZero = 0;  // deb
  }
  flagCount += iniWidthSpec(str + flagCount, info, errCode, args);
  if (flagStrComp(info->type[0], "uoxX", 4)) {  // deb diouxX
    if (info->fPlus) info->fPlus = 0;           // warning
    if (info->fSpace) info->fSpace = 0;         // warning
  }
  if (flagStrComp(info->type[0], "p", 1) && info->fZero)
    info->fZero = 0;  // warning
  return flagCount;
}

int iniWidthSpec(const char *str, specInfo *info, int *errCode, va_list *args) {
  int num = 0, lenNum = 0;
  info->isWidth = 0;
  info->width = 0;

  if (notEndStr(str, errCode) && !(*errCode)) {
    lenNum = readNum(str, &num);
    if (lenNum == -1) {
      (*errCode) = 123;  // код ошибки
    } else if (lenNum > 0) {
      info->isWidth = 1;
      info->width = num;
    } else if (str[0] == '*') {
      info->width = va_arg(*args, int);
      info->isWidth = 1;
      lenNum++;
    }
  }
  if (!(*errCode) && notEndStr(str + lenNum, errCode)) {
    lenNum += iniAccSpec(str + lenNum, info, errCode, args);
  }
  return lenNum;
}

int iniAccSpec(const char *str, specInfo *info, int *errCode, va_list *args) {
  int lenNum = 0, num = 6;
  info->accuracy = 1;
  info->isAccuracy = 0;
  notEndStr(str, errCode);

  if (str[0] == '.' && notEndStr(str + 1, errCode)) {
    lenNum = readNum(str + 1, &num);
    info->accuracy = 0;
    if (lenNum == -1) {
      (*errCode) = 220;
    } else if (lenNum > 0) {
      info->accuracy = num;
      info->isAccuracy = 1;
    } else if (str[1] == '*') {
      info->accuracy = va_arg(*args, int);
      info->isAccuracy = 1;
      lenNum++;
    }
    lenNum++;
  }
  if (!(*errCode) && str[0] != '.') {
    lenNum += iniModSpec(str, info, errCode);
  } else if (!(*errCode) && notEndStr(str + lenNum, errCode)) {
    lenNum += iniModSpec(str + lenNum, info, errCode);
  }
  if (!(*errCode) && !(info->isAccuracy)) {
    if (flagStrComp(info->type[0], "eEfgG", 5)) info->accuracy = 6;
  }
  if (!(*errCode) && flagStrComp(info->type[0], "c%", 3))
    info->isAccuracy = 0;  // точность не имеет смысла
  return lenNum;
}

int iniModSpec(const char *str, specInfo *info, int *errCode) {
  int modNum = 0;
  info->mods[0] = '\0';
  info->mods[1] = '\0';
  info->mods[2] = '\0';
  //
  if (notEndStr(str, errCode) && flagStrComp(str[0], "hlL", 3)) {
    info->mods[0] = str[0];
    modNum++;
    if (notEndStr(str + 1, errCode) && flagStrComp(str[1], "hl", 2)) {
      info->mods[1] = str[1];
      modNum++;
    }
  }
  // заранее проверка что есть спецификатор
  notEndStr(str + modNum, errCode);
  if (!(*errCode)) {
    modNum += iniTypeSpec(str + modNum, info, errCode);
  } else {
    modNum = -1;
  }
  return modNum;
}

int iniTypeSpec(const char *str, specInfo *info, int *errCode) {
  info->type[0] = '\0';
  info->type[1] = '\0';
  if (flagStrComp(str[0], "cdfsu%gGeExXop", 14)) {
    info->type[0] = str[0];
  } else if (str[0] != '\n') {
    (*errCode) = 29;  // код ошибки
  } else {
    (*errCode) = 229;  // код ошибки
  }
  return (str[0] == '\n') ? 0 : 1;
}

int readNum(const char *str, int *num) {  // а если |%010.| ...? |%000.| ...?
  int result = 0, firstMinus, count = 0;
  firstMinus = str[count] == '-' ? 1 : 0;
  for (; flagStrComp(str[count], "0123456789", 10); count++) {
    result = result * 10 + (int)(str[count] - '0');
  }
  *num = firstMinus ? (-1 * result) : result;
  if (firstMinus && !count) count = -1;
  return count;
}

char intToChar(int num, int isUpper) {
  char ch;
  if (num >= 10 && !isUpper) {
    ch = num + 'a' - 10;
  } else if (num >= 10) {
    ch = num + 'A' - 10;
  } else {
    ch = num + '0';
  }
  return ch;
}

int notEndStr(const char *str, int *errCode) {
  if (str[0] == '\0') *errCode = 100;  // код ошибки
  return str[0] == '\0' ? 0 : 1;
}

void swapCh(char *a, char *b) {
  char temp = (*a);
  (*a) = (*b);
  (*b) = temp;
}

/*int main() {
  char str1[1024] = "";
  char str2[1024] = "";
  double x = 10000000.0;
  char *format = "|%g|\n";
  s21_sprintf(str1, format, x);
  sprintf(str2, format, x);

  printf("%s\n%s", str1, str2);
}
*/
/*
int main() {
  char flags[6] = "#+-0 ";
  int width[4] = {0, 1, 5, 10};
  int acc[4] = {0, 1, 5, 10};
  char mode[4][4] = {"h", "l", "ll", "L"};
  char type[15] = "%cspdufgGeExXo";
  FILE *file = fopen("output.txt", "w");
  if (file == NULL) {
    perror("Не удалось открыть файл");
  } else {
    char buffOrig[100], buffS21[100];
    int f, w, a, m, t, x = -1, y = -1;
    for (int i = 0; i < 5 * 4 * 4 * 4 * 14; i++) {
      for (int q = 0; q < 99; q++)
        buffOrig[q] = ' ', buffS21[q] = ' ';  //зачистка буфера
      if (i == 3500) {
        int deb;
      }  // deb
      f = i % 5;
      w = (i / 5) % 4;
      a = (i / 20) % 4;
      m = (i / 80) % 4;
      t = (i / 320);
      int dodge = 0;  //(t >= 7 && t <= 10);
      char test[100];
      snprintf(test, 100, "t%d) %%%c%d.%d%s%c", i, flags[f], width[w], acc[a],
               mode[m], type[t]);
      fprintf(file, "%s", test);
      if (flagStrComp(type[t], "%%", 2)) {
        x = snprintf(buffOrig, 100, test);
        y = s21_sprintf(buffS21, test);
        fprintf(file, "|%%|\n");
      } else if (flagStrComp(type[t], "c", 1)) {
        x = snprintf(buffOrig, 100, test, 'A');
        y = s21_sprintf(buffS21, test, 'A');
        fprintf(file, "|A|\n");
      } else if (flagStrComp(type[t], "duxXo", 5)) {
        x = snprintf(buffOrig, 100, test, 1230);
        y = s21_sprintf(buffS21, test, 1230);
        fprintf(file, "|%d|\n", 1230);
      } else if (flagStrComp(type[t], "gGeE", 4) ||
                 (type[t] == 'f' && m != 4)) {
        x = snprintf(buffOrig, 100, test, 123.0004560);
        y = s21_sprintf(buffS21, test, 123.0004560);
        fprintf(file, "|%f|\n", 123.4560);
      } else if (flagStrComp(type[t], "f", 5)) {
        x = snprintf(buffOrig, 100, test, 123.4560L);
        y = s21_sprintf(buffS21, test, 123.4560L);
        fprintf(file, "|%Lf|\n", 123.4560L);
      } else if (flagStrComp(type[t], "s", 1)) {
        x = snprintf(buffOrig, 100, test, "test");
        y = s21_sprintf(buffS21, test, "test");
        fprintf(file, "|test|\n");
      } else if (flagStrComp(type[t], "p", 1)) {
        void *ptr = (void *)0xf;
        x = snprintf(buffOrig, 100, test, ptr);
        y = s21_sprintf(buffS21, test, ptr);
        fprintf(file, "|0x12345678|\n");
      }
      fprintf(file, "%s\n", buffOrig);
      fprintf(file, "%s\n", buffS21);
      if (!(strcmp(buffOrig, buffS21))) {
        fprintf(file, " -> sucsess");
      } else if (dodge) {
        fprintf(file, " -> dodge %d", strcmp(buffOrig, buffS21));
      } else {
        fprintf(file, " -> fall %d", strcmp(buffOrig, buffS21));
      }
      fprintf(file, " | oring = %d | s21_ = %d |\n", x, y);
    }
    fclose(file);
  }
}
*/
/*
2

Флаги: -, +, (пробел)
Ширина: (число)
Точность: .(число)
Длина: h, l
Спецификаторы: c, d, f, s, u, %

3

Флаги: #, 0
Ширина: *
Точность: .*
Длина: L
Спецификаторы: g, G, e, E, x, X, o, p
*/
