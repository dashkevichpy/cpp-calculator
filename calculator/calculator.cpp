#include "calculator.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

//Читаем число
bool ReadNumber(Number& result) {
    return (std::cin >> result) ? true : (std::cerr << "Error: Numeric operand expected" << std::endl, false);
}

//Читаем операцию
bool ReadChar(std::string& ch){
    std::vector<std::string> symbol = {"*", "+", "-", "/", "**", "q", "=", ":", "c", "s", "l"};
    if(std::cin >> ch){
        auto indx = std::find(symbol.begin(), symbol.end(), ch);
        if(indx != symbol.end()){
            return true;
        }else{
            std::cerr << "Error: Unknown token " << ch << std::endl;
            return false;
        }

    }else{
        std::cerr << "Error: Unknown token " << ch << std::endl;
        return false;
    }
}

//Арифметические функции
void Add(Number& x, Number y){
    x += y;
}

void Subtract(Number& x, Number y){
    x -= y;
}

void Multiply(Number& x, Number y){
    x *= y;
}

void Divide(Number& x, Number y){
    x/=y;
}

void Power(Number& x, Number y){
    x = std::pow(x, y);
}


//Функции калькултора
void QuitCalculator() {
    exit(0);
}

void ShowResult(Number& x){
    std::cout << x << std::endl;
}

void SetNumber(Number& x, Number y){
    x = y;
}

void ZeroX(Number& x){
    x = 0;
}

void SaveNumber(Number& x, Number& s, bool& saveNumber){
    s = x;
    saveNumber = true;
}

void LoadFromMemory(Number& s, Number& x, bool& saveNumber){
    if(saveNumber){
        x = s;
    }else{
        std::cerr << "Error: Memory is empty" << std::endl;
        exit(0);
    }
}

//Выбор операции
bool SelectOperation(Number& x, Number& y, Number& s, std::string& ch, bool& saveNumber){
    if (ch == "*" || ch == "+" || ch == "-" || ch == "/" || ch == "**" || ch == ":") {
        if (!ReadNumber(y)) {
            return false;
        }
    }
    if(ch == "*"){
        Multiply(x, y);
    }else if(ch == "+"){
        Add(x, y);
    }else if(ch == "-"){
        Subtract(x, y);
    }else if(ch == "/"){
        Divide(x, y);
    }else if(ch == "**"){
        Power(x, y);
    }else if(ch == "q"){
        QuitCalculator();
    }else if(ch == "="){
        ShowResult(x);
    }else if(ch == ":"){
        SetNumber(x, y);
    }else if(ch == "c"){
        ZeroX(x);
    }else if(ch == "s"){
        SaveNumber(x, s, saveNumber);
    }else if(ch == "l"){
        LoadFromMemory(s, x, saveNumber);
    }
    return true;
}

//Основной цикл
void RunCalculatorCycle(){
    std::string ch;
    Number x, y, s;
    bool work = true, saveNumber = false;
    if(!ReadNumber(x)){
        return;
    }
    while (work) {
        if(!ReadChar(ch)){
            break;
        }
        work = SelectOperation(x, y, s, ch, saveNumber);
    }
}
