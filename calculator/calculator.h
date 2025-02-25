
#pragma once

#include <optional>
#include <string>
#include <cmath>
#include <type_traits>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
public:
    Calculator() = default;

    void Set(Number number) {
        acum_ = number;
    }

    Number GetNumber() const {
        return acum_;
    }

    void Save() {
        mem_ = acum_;
    }

    void Load() {
        if (mem_.has_value()) {
            acum_ = *mem_;
        }
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

    std::optional<Error> Add(Number number) {
        acum_ += number;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number number) {
        acum_ -= number;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number number) {
        acum_ *= number;
        return std::nullopt;
    }

    std::optional<Error> Div(Number number) {
        if constexpr (std::is_floating_point_v<Number>) {
            acum_ /= number;
            return std::nullopt;
        } else if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (number == 0) {
                return "Division by zero";
            }
            acum_ /= number;
            return std::nullopt;
        }
    }

    std::optional<Error> Pow(Number exponent) {
        if constexpr (std::is_floating_point_v<Number>) {
            acum_ = std::pow(acum_, exponent);
            return std::nullopt;
        } else if constexpr (std::is_integral_v<Number>) {
            if (acum_ == 0 && exponent == 0) {
                return "Zero power to zero";
            }
            if (exponent < 0) {
                return "Integer negative power";
            }
            acum_ = ::IntegerPow(acum_, exponent);
            return std::nullopt;
        } else if constexpr (std::is_same_v<Number, Rational>) {
            if (acum_ == Rational(0) && exponent == Rational(0)) {
                return "Zero power to zero";
            }
            if (!exponent.isInteger()) {
                return "Fractional power is not supported";
            }
            acum_ = ::Pow(acum_, exponent);
            return std::nullopt;
        }
    }

private:
    Number acum_;
    std::optional<Number> mem_;
};
