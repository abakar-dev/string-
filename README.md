# String+ (s21_string+)

![CI](https://github.com/abakar-dev/string-/workflows/C%20CI%20Pipeline/badge.svg)
![C Language](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![School21](https://img.shields.io/badge/School21-000000?style=for-the-badge)
![Tests](https://img.shields.io/badge/tests-85%25%20coverage-green?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-blue?style=for-the-badge)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=for-the-badge)

Custom implementation of string.h library with additional functions in C (C11 standard).

## 📋 Description

This project provides a custom implementation of the standard string.h library with added `sprintf`, `sscanf` functions and special string processing utilities. Developed as part of **School 21** programming school curriculum.

## 🚀 Features

- Complete implementation of standard string.h functions
- Additional string processing functions (inspired by C# String class)
- Partial/full implementation of sprintf and sscanf
- Cross-platform support (Linux/macOS)
- Unit test coverage (>80%)
- Makefile-based build system

## 📚 Contents

### 📁 Project Structure

```src/
├── s21_string.h # Main header file
├── Makefile # Build file
├── *.c # Implementation source files
└── tests/ # Unit tests
```

### 🔧 Functions

#### Standard string.h functions

- **Search and comparison**: `memchr`, `memcmp`, `strchr`, `strncmp`, `strstr`, `strpbrk`
- **Copy and fill**: `memcpy`, `memset`, `strncpy`
- **Concatenation and length**: `strncat`, `strlen`, `strcspn`
- **Error handling**: `strerror`

#### Formatted I/O

- `sprintf` - formatted output to string
- `sscanf` - formatted input from string

#### Special functions (C# String inspired)

- `to_upper` - convert to uppercase
- `to_lower` - convert to lowercase
- `insert` - insert substring
- `trim` - trim characters

## 🛠️ Build and Usage

### Compile library

```bash
cd src
make s21_string.a
```

### Run tests

```bash
make test
```

### Generate coverage report

```bash
make gcov_report
```

### Full build

```bash
make all
```

### Clean

```bash
make clean
```

## 📊 Supported Format Specifiers

### For sprintf/sscanf

Specifiers: `c`, `d`, `i`, `e`, `E`, `f`, `g`, `G`, `o`, `s`, `u`, `x`, `X`, `p`, `n`, `%`
Flags: `-`, `+`, ` ` (space), `#`, `0`
Width: number, `*`
Precision: `.number`, `.*`
Length: `h`, `l`, `L`

## 🧪 Testing

The project includes comprehensive unit test coverage using the Check library. Tests compare the implementation with the standard string.h library.

### Testing requirements

Function coverage ≥80%
Cross-platform testing (Linux/macOS)
Edge case testing
Error handling validation

## 📝 Code Requirements

Language standard: C11
Compiler: gcc
Code style: Google C Style
Principles: Structured programming
Prohibited: using standard string.h in implementation

## 🏫 Project Information

- **Educational institution**: School 21
- **Track**: C Programming
- **Project**: String+ (s21_string+)
- **Author**: cadwynga

## 📄 License

Project is distributed under the license specified in [LICENSE](LICENSE) file.

---

*This project is an educational work created for learning purposes.*
