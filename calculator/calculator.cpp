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
bool ReadChar(std::string& operation, std::vector<std::string>& symbol){
    if(std::cin >> operation){
        auto indx = std::find(symbol.begin(), symbol.end(), operation);
        if(indx != symbol.end()){
            return true;
        }
    }
    std::cerr << "Error: Unknown token " << operation << std::endl;
    return false;
}

//Арифметические функции
void Add(Number& accumulator, Number value){
    accumulator += value;
}

void Subtract(Number& accumulator, Number value){
    accumulator -= value;
}

void Multiply(Number& accumulator, Number value){
    accumulator *= value;
}

void Divide(Number& accumulator, Number value){
    accumulator /= value;
}

void Power(Number& accumulator, Number value){
    accumulator = std::pow(accumulator, value);
}


//Функции калькулятора
void QuitCalculator() {
    exit(0);
}

void ShowResult(Number& accumulator){
    std::cout << accumulator << std::endl;
}

void SetNumber(Number& accumulator, Number value){
    accumulator = value;
}

void ZeroAccumulator(Number& accumulator){
    accumulator = 0;
}

void SaveNumber(Number& accumulator, Number& memory, bool& isMemorySet){
    memory = accumulator;
    isMemorySet = true;
}

void LoadFromMemory(Number& memory, Number& accumulator, bool& isMemorySet){
    if(isMemorySet){
        accumulator = memory;
    }else{
        std::cerr << "Error: Memory is empty" << std::endl;
        exit(0);
    }
}

//Выбор операции
bool SelectOperation(Number& accumulator, Number& value, Number& memory, std::string& operation, bool& isMemorySet){
    if (operation == "*" || operation == "+" || operation == "-" || operation == "/" || operation == "**" || operation == ":") {
        if (!ReadNumber(value)) {
            return false;
        }
    }
    if(operation == "*"){
        Multiply(accumulator, value);
    }else if(operation == "+"){
        Add(accumulator, value);
    }else if(operation == "-"){
        Subtract(accumulator, value);
    }else if(operation == "/"){
        Divide(accumulator, value);
    }else if(operation == "**"){
        Power(accumulator, value);
    }else if(operation == "q"){
        QuitCalculator();
    }else if(operation == "="){
        ShowResult(accumulator);
    }else if(operation == ":"){
        SetNumber(accumulator, value);
    }else if(operation == "c"){
        ZeroAccumulator(accumulator);
    }else if(operation == "s"){
        SaveNumber(accumulator, memory, isMemorySet);
    }else if(operation == "l"){
        LoadFromMemory(memory, accumulator, isMemorySet);
    }
    return true;
}

//Основной цикл
void RunCalculatorCycle(){
    std::vector<std::string> symbol = {"*", "+", "-", "/", "**", "q", "=", ":", "c", "s", "l"};
    std::string operation = ""; // Присвоено значение по умолчанию
    Number accumulator, value, memory;
    bool work = true, isMemorySet = false;
    if(!ReadNumber(accumulator)){
        return;
    }
    while (work) {
        if(!ReadChar(operation, symbol)){
            break;
        }
        work = SelectOperation(accumulator, value, memory, operation, isMemorySet);
    }
}
