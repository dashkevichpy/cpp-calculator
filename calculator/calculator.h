#include <string>

using Number = double;

// Функции чтения
bool ReadNumber(Number& result);
bool ReadChar(std::string& ch);

// Арифметические операции
void Add(Number& x, Number y);
void Subtract(Number& x, Number y);
void Multiply(Number& x, Number y);
void Divide(Number& x, Number y);
void Power(Number& x, Number y);

// Операции калькулятора
void QuitCalculator();
void ShowResult(Number& x);
void SetNumber(Number& x, Number y);
void ZeroX(Number& x);
void SaveNumber(Number& y, Number& s, bool& saveNumber);
void LoadFromMemory(Number& s, Number& y, bool& saveNumber);

// Основной цикл и выбор операций
bool SelectOperation(Number& x, Number& y, Number& s, std::string& ch, bool& saveNumber);
void RunCalculatorCycle();
