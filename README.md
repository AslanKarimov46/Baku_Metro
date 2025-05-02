# 🚇 Baku Metro Simulator

Многопоточная симуляция движения поездов Бакинского метрополитена с логированием и синхронизацией. Учебный проект на C++17.

[![CMake](https://img.shields.io/badge/CMake-3.10+-064F8C?logo=cmake)](https://cmake.org)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg?logo=c%2B%2B)](https://en.cppreference.com/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

![Пример лога поезда](https://via.placeholder.com/800x200.png?text=Логи+поездов+в+train_*.txt)

## 🌟 Особенности

- Моделирование 4 линий метро:
  - Фиолетовая (6 поездов)
  - Зеленая (10 поездов)
  - Красная (10 поездов)
  - Салатовая (2 поезда)
- Реализация:
  - Синхронизация потоков с помощью `std::mutex`
  - Логирование в файлы для каждого поезда
  - Динамический расчет времени движения
  - Обработка исключений
- Генерация логов в формате:



## 📥 Установка

### Требования:
- Компилятор с поддержкой C++17 (GCC 9+, Clang 10+)
- CMake 3.10+

### Сборка:
```bash
https://github.com/AslanKarimov46/Baku_Metro.git
cd Baku_Metro
mkdir build && cd build
cmake ..
make



## 🚀 Запуск:
```bash
./BMetro


