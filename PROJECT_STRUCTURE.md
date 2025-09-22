# Project Structure

This project implements a comprehensive multiset operations system with proper C++ architecture.

## File Organization

```
lab1/
├── funcs.h                # Header file with class declaration and function prototypes
├── funcs.cpp              # Implementation of all class methods and functions
├── main.cpp               # Main program entry point with user interface
├── test.cpp               # Comprehensive test suite
├── CMakeLists.txt         # CMake build configuration
├── Makefile               # Legacy Makefile (optional)
├── README.md              # Project documentation
└── PROJECT_STRUCTURE.md   # This file
```

## Build and Run (CMake)

```bash
# From project root
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Run
./lab1
./test_program
```

Optional debug build:
```bash
mkdir -p build-debug
cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

## Program Modes

### 1. Main Program Mode
- Interactive user interface
- Gray code generation with user-specified bit width
- Manual or automatic multiset creation
- Complete set and arithmetic operations (multiplicity-based and Gray-weighted)
- Input validation and error handling

### 2. Test Mode
- Comprehensive test suite
- Automated verification of all functionality
- Edge case testing

## Key Features

### Gray Code Generation
- Recursive algorithm implementation
- Support for 1-10 bit widths
- Proper Gray code properties (consecutive elements differ by one bit)

### Multiset Operations
- **Set Operations**: Union, intersection, difference, symmetric difference, complement
- **Arithmetic Operations**: Sum, difference, product, division (multiplicity-only and Gray-weighted)
- **Input Methods**: Manual entry or automatic random generation

### Error Handling
- Comprehensive input validation
- Division by zero protection
- Clear error messages and user guidance

## Testing

The test suite covers:
- Gray code generation for various bit widths
- All multiset operations with known test cases
- Arithmetic operations with edge cases
- Error handling scenarios
- Empty and single-element multisets

## Architecture Benefits

1. **Separation of Concerns**: Header, implementation, and main are properly separated
2. **Modularity**: Easy to extend and maintain
3. **Testability**: Comprehensive test suite ensures reliability
4. **Build System**: CMake provides portable builds; Makefile kept for convenience
5. **Documentation**: Clear documentation for all components

## Dependencies

- C++11 or later
- Standard C++ library
- No external dependencies required

---

# Структура проекта (RU)

Этот проект реализует операции над мультимножествами на основе кода Грея с корректной архитектурой C++.

## Организация файлов

```
lab1/
├── funcs.h                # Заголовочный файл (объявления класса и функций)
├── funcs.cpp              # Реализация методов класса и функций
├── main.cpp               # Точка входа и пользовательский интерфейс
├── test.cpp               # Набор тестов
├── CMakeLists.txt         # Конфигурация сборки CMake
├── Makefile               # Унаследованный Makefile (по желанию)
├── README.md              # Документация проекта
└── PROJECT_STRUCTURE.md   # Этот файл
```

## Сборка и запуск (CMake)

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

./lab1
./test_program
```

Отладочная сборка:
```bash
mkdir -p build-debug
cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

## Режимы программы

### 1. Основной режим
- Интерактивный интерфейс
- Генерация кода Грея с вводом разрядности
- Заполнение мультимножеств вручную или автоматически
- Полный набор операций над множествами и арифметики (по кратностям и взвешенной по Грею)
- Проверка корректности ввода

### 2. Режим тестов
- Автоматические тесты функциональности
- Проверка крайних случаев

## Преимущества архитектуры
- Разделение ответственности (заголовки/реализация/UI)
- Модульность и расширяемость
- Наличие набора тестов
- Портируемая сборка через CMake (Makefile сохранён для удобства)
