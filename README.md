# Multiset Operations Program

This program implements a comprehensive multiset operations system based on binary Gray codes.

## Features

### Core Functionality
- **Binary Gray Code Generation**: Generates Gray codes of user-specified bit width (1-10 bits)
- **Multiset Creation**: Two methods available:
  - **Manual**: User inputs multiplicity for each universe element
  - **Automatic**: Randomly distributes specified cardinality across universe elements

### Set Operations
- **Union**: Combines multisets, taking maximum multiplicity for each element
- **Intersection**: Takes minimum multiplicity for common elements
- **Difference**: Two variants (M1 - M2 and M2 - M1)
- **Symmetric Difference**: Elements in exactly one multiset
- **Complement**: Elements not in the multiset (assumes max multiplicity of 1)

### Arithmetic Operations (two modes)
- **Multiplicity-only**: Sum, arithmetic difference, product, division using multiplicities
- **Gray-weighted**: Same operations using integer values derived from Gray codes

### Input Validation
- Comprehensive error checking for all user inputs
- Protection against invalid data types and ranges
- Clear error messages and input prompts

## Build and Run (CMake)

```bash
# From the project root
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Run
./lab1
./test_program
```

Optional: Debug build
```bash
mkdir -p build-debug
cd build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

## Program Flow

1. **Input Bit Width**: Enter desired Gray code bit width (1-10)
2. **Display Universe**: Shows all possible Gray codes for the given bit width
3. **Create Multiset 1**: Choose manual or automatic creation
4. **Create Multiset 2**: Choose manual or automatic creation
5. **Display Results**: Shows set operations, multiplicity-based arithmetic, and Gray-weighted arithmetic

## Example Usage

For a 2-bit Gray code system:
- Universe: {00, 01, 11, 10}
- Manual multiset creation allows you to specify multiplicity for each element
- Automatic creation randomly distributes a given cardinality

## Technical Details

- **Language**: C++
- **Data Structures**: `std::map` for multisets, `std::vector` for universe
- **Random Generation**: Uses modern `std::shuffle` with `std::mt19937`
- **Gray-weighted mode**: Converts Gray→binary with prefix XOR and uses integer values
- **Error Handling**: Comprehensive input validation

## Gray Code Properties

Gray codes ensure that consecutive elements differ by exactly one bit, making them useful for:
- Digital communication systems
- Error detection and correction
- Combinatorial optimization
- Multiset universe generation

The program generates Gray codes recursively using the standard algorithm:
- For n=1: {0, 1}
- For n>1: {0 + prev_codes, 1 + reversed_prev_codes}

---

# Программа операций над мультимножествами (RU)

Эта программа реализует операции над мультимножествами на основе бинарных кодов Грея.

## Возможности

### Основное
- **Генерация кода Грея** указанной разрядности (1–10)
- **Формирование мультимножеств**:
  - **Вручную**: ввод кратностей для каждого элемента универсума
  - **Автоматически**: случайное распределение заданной мощности

### Операции над множествами
- **Объединение**: максимум кратностей по элементу
- **Пересечение**: минимум кратностей по общим элементам
- **Разность**: оба варианта (A−B, B−A)
- **Симметрическая разность**: элементы, входящие ровно в одно мультимножество
- **Дополнение**: элементы универсума, отсутствующие в множестве (макс. кратность = 1)

### Арифметика (2 режима)
- **По кратностям**: сумма, разность, произведение, деление по суммам кратностей
- **С взвешиванием по Грею**: те же операции, но значения элементов получены из Gray→целое

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

## Свойства кода Грея
- Последовательные элементы отличаются ровно в одном бите
- Построение рекурсивное: для n>1 — 0+предыдущие, затем 1+развернутые предыдущие
