#ifndef CALCULATOR_H
#define CALCULATOR_H


using Number = double;

class Calculator{

public:
    Calculator() = default;

    // Устанавливает текущее число
    void Set(Number number);

    // Возвращает текущее число
    Number GetNumber() const;

    // Арифметические операции
    void Add(Number number);
    void Sub(Number number);
    void Div(Number number);
    void Mul(Number number);
    void Pow(Number exponent);

private:
    Number acum_ = 0;
};

#endif // CALCULATOR_H
