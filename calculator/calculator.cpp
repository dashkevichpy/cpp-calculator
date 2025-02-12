#include "calculator.h"
#include <cmath>

void Calculator::Set(Number number){

    acum_ = number;
}

Number Calculator::GetNumber() const{

    return acum_;
}

void Calculator::Add(Number number){

    acum_ += number;
}

void Calculator::Sub(Number number){

    acum_ -= number;
}

void Calculator::Div(Number number){

    acum_ /= number;
}

void Calculator::Mul(Number number){

    acum_ *= number;
}

void Calculator::Pow(Number exponent){

    acum_ = std::pow(acum_, exponent);
}

