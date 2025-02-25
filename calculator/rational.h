#pragma once

#include <numeric>
#include <stdexcept>
#include <compare>
#include <iostream>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}
    Rational(int num) : numerator_(num), denominator_(1) {}
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }
    Rational(const Rational& other) = default;
    Rational& operator=(const Rational& other) = default;

    int GetNumerator() const {
        return numerator_;
    }
    bool isInteger() const {
        return (GetDenominator() == 1) || (GetNumerator() == 0);
    }


    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        if (numerator_ == 0) {
            std::abort();
        }
        Rational tmp(denominator_, numerator_);
        tmp.Reduction();
        return tmp;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    Rational operator+(const Rational& other) const {
        Rational temp(*this);
        temp += other;
        return temp;
    }

    Rational operator-(const Rational& other) const {
        Rational temp(*this);
        temp -= other;
        return temp;
    }

    Rational operator*(const Rational& other) const {
        Rational temp(*this);
        temp *= other;
        return temp;
    }

    Rational operator/(const Rational& other) const {
        Rational temp(*this);
        temp /= other;
        return temp;
    }

    Rational& operator+=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        if (other.numerator_ == 0) {
            std::abort();
        }
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        Reduction();
        return *this;
    }

    bool operator==(const Rational& other) const {
        return static_cast<int64_t>(numerator_) * other.denominator_ ==
               static_cast<int64_t>(other.numerator_) * denominator_;
    }

    std::strong_ordering operator<=>(const Rational& other) const {
        int64_t lhs = static_cast<int64_t>(numerator_)   * other.denominator_;
        int64_t rhs = static_cast<int64_t>(other.numerator_) * denominator_;
        if (lhs < rhs) {
            return std::strong_ordering::less;
        } else if (lhs > rhs) {
            return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        int gcd_val = std::gcd(numerator_, denominator_);
        numerator_ /= gcd_val;
        denominator_ /= gcd_val;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.GetDenominator() == 1) {
        os << r.GetNumerator();
    } else {
        os << r.GetNumerator() << " / " << r.GetDenominator();
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int n, d;
    char div;
    if (!(is >> n)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    if (!(is >> std::ws >> div)) {
        r = Rational(n, 1);
        is.clear();
        return is;
    }
    if (div != '/') {
        r = Rational(n, 1);
        is.unget();
        return is;
    }
    if (!(is >> d) || d == 0) {
        is.setstate(std::ios::failbit);
        return is;
    }
    r = Rational(n, d);
    return is;
}

