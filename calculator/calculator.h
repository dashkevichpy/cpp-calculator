#pragma once

#include <string>
#include <vector>

using Number = double;

// Функции чтения
bool ReadNumber(Number& result);
bool ReadChar(std::string& operation, std::vector<std::string>& symbol);

// Арифметические операции
void Add(Number& accumulator, Number value);
void Subtract(Number& accumulator, Number value);
void Multiply(Number& accumulator, Number value);
void Divide(Number& accumulator, Number value);
void Power(Number& accumulator, Number value);

// Операции калькулятора
void QuitCalculator();
void ShowResult(Number& accumulator);
void SetNumber(Number& accumulator, Number value);
void ZeroAccumulator(Number& accumulator);
void SaveNumber(Number& accumulator, Number& memory, bool& isMemorySet);
void LoadFromMemory(Number& memory, Number& accumulator, bool& isMemorySet);

// Основной цикл и выбор операций
bool SelectOperation(Number& accumulator, Number& value, Number& memory, std::string& operation, bool& isMemorySet);
void RunCalculatorCycle();
