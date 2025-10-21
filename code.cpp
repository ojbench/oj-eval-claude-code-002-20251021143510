#pragma once
#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

// Integer 1:
// 实现一个有符号的大整数类，只需支持简单的加减

// Integer 2:
// 实现一个有符号的大整数类，支持加减乘除，并重载相关运算符

// 请不要使用除了以下头文件之外的其它头文件
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

// 请不要使用 using namespace std;

namespace sjtu {
class int2048 {
private:
    bool sign;  // true for positive, false for negative
    std::vector<int> digits;  // digits in base BASE, least significant digit first

public:
  // 构造函数
  int2048();
  int2048(long long);
  int2048(const std::string &);
  int2048(const int2048 &);

  // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
  // 如果需要，可以自行增加其他所需的函数
  // ===================================
  // Integer1
  // ===================================

  // 读入一个大整数
  void read(const std::string &);
  // 输出储存的大整数，无需换行
  void print();

  // 加上一个大整数
  int2048 &add(const int2048 &);
  // 返回两个大整数之和
  friend int2048 add(int2048, const int2048 &);

  // 减去一个大整数
  int2048 &minus(const int2048 &);
  // 返回两个大整数之差
  friend int2048 minus(int2048, const int2048 &);

  // ===================================
  // Integer2
  // ===================================

  int2048 operator+() const;
  int2048 operator-() const;

  int2048 &operator=(const int2048 &);

  int2048 &operator+=(const int2048 &);
  friend int2048 operator+(int2048, const int2048 &);

  int2048 &operator-=(const int2048 &);
  friend int2048 operator-(int2048, const int2048 &);

  int2048 &operator*=(const int2048 &);
  friend int2048 operator*(int2048, const int2048 &);

  int2048 &operator/=(const int2048 &);
  friend int2048 operator/(int2048, const int2048 &);

  int2048 &operator%=(const int2048 &);
  friend int2048 operator%(int2048, const int2048 &);

  friend std::istream &operator>>(std::istream &, int2048 &);
  friend std::ostream &operator<<(std::ostream &, const int2048 &);

  friend bool operator==(const int2048 &, const int2048 &);
  friend bool operator!=(const int2048 &, const int2048 &);
  friend bool operator<(const int2048 &, const int2048 &);
  friend bool operator>(const int2048 &, const int2048 &);
  friend bool operator<=(const int2048 &, const int2048 &);
  friend bool operator>=(const int2048 &, const int2048 &);
};
} // namespace sjtu

#endif

// Implementation
namespace sjtu {

// Use base 1000000000 (10^9) for digit compression
static const int BASE = 1000000000;
static const int BASE_DIGITS = 9;

// Helper functions
int compare_abs(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size() ? -1 : 1;
    }
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    return 0;
}

void remove_leading_zeros(std::vector<int>& num) {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
    if (num.size() == 1 && num[0] == 0) {
        // Zero is positive
    }
}

// Constructors
int2048::int2048() : sign(true), digits(1, 0) {}

int2048::int2048(long long val) {
    if (val == 0) {
        sign = true;
        digits.push_back(0);
        return;
    }

    sign = val >= 0;
    if (val < 0) val = -val;

    while (val > 0) {
        digits.push_back(val % BASE);
        val /= BASE;
    }
}

int2048::int2048(const std::string& str) {
    read(str);
}

int2048::int2048(const int2048& other) : sign(other.sign), digits(other.digits) {}

// Basic operations
void int2048::read(const std::string& str) {
    digits.clear();

    size_t start = 0;
    sign = true;

    if (str.empty()) {
        sign = true;
        digits.push_back(0);
        return;
    }

    if (str[0] == '-') {
        sign = false;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }

    // Handle zero
    bool all_zero = true;
    for (size_t i = start; i < str.size(); ++i) {
        if (str[i] != '0') {
            all_zero = false;
            break;
        }
    }

    if (all_zero) {
        sign = true;
        digits.push_back(0);
        return;
    }

    // Process digits in groups of BASE_DIGITS
    for (int i = str.size() - 1; i >= (int)start; i -= BASE_DIGITS) {
        int val = 0;
        int left = std::max((int)start, i - BASE_DIGITS + 1);
        for (int j = left; j <= i; ++j) {
            val = val * 10 + (str[j] - '0');
        }
        digits.push_back(val);
    }
}

void int2048::print() {
    if (!sign && !(digits.size() == 1 && digits[0] == 0)) {
        std::cout << '-';
    }

    std::cout << digits.back();

    for (int i = digits.size() - 2; i >= 0; --i) {
        std::cout.width(BASE_DIGITS);
        std::cout.fill('0');
        std::cout << digits[i];
    }
}

int2048& int2048::add(const int2048& other) {
    if (sign == other.sign) {
        // Same sign, add absolute values
        std::vector<int> result;
        int carry = 0;
        int max_len = std::max(digits.size(), other.digits.size());

        for (int i = 0; i < max_len || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];

            result.push_back(sum % BASE);
            carry = sum / BASE;
        }

        digits = result;
        return *this;
    } else {
        // Different signs, subtract
        int cmp = compare_abs(digits, other.digits);

        if (cmp == 0) {
            sign = true;
            digits.assign(1, 0);
            return *this;
        }

        std::vector<int> result;
        bool result_sign = (cmp > 0) ? sign : other.sign;
        const std::vector<int>& larger = (cmp > 0) ? digits : other.digits;
        const std::vector<int>& smaller = (cmp > 0) ? other.digits : digits;

        int borrow = 0;
        for (int i = 0; i < larger.size(); ++i) {
            int diff = larger[i] - borrow;
            if (i < smaller.size()) diff -= smaller[i];

            if (diff < 0) {
                diff += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back(diff);
        }

        remove_leading_zeros(result);
        sign = result_sign;
        digits = result;
        return *this;
    }
}

int2048 add(int2048 a, const int2048& b) {
    return a.add(b);
}

int2048& int2048::minus(const int2048& other) {
    int2048 temp(other);
    temp.sign = !temp.sign;
    return add(temp);
}

int2048 minus(int2048 a, const int2048& b) {
    return a.minus(b);
}

// Operator overloading
int2048 int2048::operator+() const {
    return *this;
}

int2048 int2048::operator-() const {
    int2048 result(*this);
    if (!(digits.size() == 1 && digits[0] == 0)) {
        result.sign = !sign;
    }
    return result;
}

int2048& int2048::operator=(const int2048& other) {
    if (this != &other) {
        sign = other.sign;
        digits = other.digits;
    }
    return *this;
}

int2048& int2048::operator+=(const int2048& other) {
    return add(other);
}

int2048 operator+(int2048 a, const int2048& b) {
    return a.add(b);
}

int2048& int2048::operator-=(const int2048& other) {
    return minus(other);
}

int2048 operator-(int2048 a, const int2048& b) {
    return a.minus(b);
}

// Multiplication
int2048& int2048::operator*=(const int2048& other) {
    if ((digits.size() == 1 && digits[0] == 0) ||
        (other.digits.size() == 1 && other.digits[0] == 0)) {
        sign = true;
        digits.assign(1, 0);
        return *this;
    }

    std::vector<int> result(digits.size() + other.digits.size(), 0);

    for (int i = 0; i < digits.size(); ++i) {
        long long carry = 0;
        for (int j = 0; j < other.digits.size() || carry; ++j) {
            long long product = result[i + j] + carry;
            if (j < other.digits.size()) {
                product += (long long)digits[i] * other.digits[j];
            }
            result[i + j] = product % BASE;
            carry = product / BASE;
        }
    }

    remove_leading_zeros(result);
    sign = sign == other.sign;
    digits = result;
    return *this;
}

int2048 operator*(int2048 a, const int2048& b) {
    return a *= b;
}

// Division
int2048& int2048::operator/=(const int2048& other) {
    *this = *this / other;
    return *this;
}

int2048 operator/(int2048 a, const int2048& b) {
    if (b.digits.size() == 1 && b.digits[0] == 0) {
        throw std::runtime_error("Division by zero");
    }

    // Handle division by 1 or -1
    if (b.digits.size() == 1 && b.digits[0] == 1) {
        int2048 result(a);
        result.sign = (a.sign == b.sign);
        return result;
    }

    int cmp = compare_abs(a.digits, b.digits);

    if (cmp < 0) {
        return int2048(0);
    }

    if (cmp == 0) {
        int2048 result(1);
        result.sign = (a.sign == b.sign);
        return result;
    }

    // Perform long division
    std::vector<int> quotient;
    std::vector<int> remainder;

    for (int i = a.digits.size() - 1; i >= 0; --i) {
        remainder.insert(remainder.begin(), a.digits[i]);
        remove_leading_zeros(remainder);

        if (compare_abs(remainder, b.digits) < 0) {
            if (!quotient.empty()) {
                quotient.push_back(0);
            }
            continue;
        }

        // Binary search for the current quotient digit
        int left = 0, right = BASE - 1;
        int best = 0;

        while (left <= right) {
            int mid = (left + right) / 2;

            // Calculate mid * b
            std::vector<int> product;
            long long carry = 0;
            for (int j = 0; j < b.digits.size() || carry; ++j) {
                long long val = carry;
                if (j < b.digits.size()) {
                    val += (long long)mid * b.digits[j];
                }
                product.push_back(val % BASE);
                carry = val / BASE;
            }

            if (compare_abs(product, remainder) <= 0) {
                best = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        quotient.push_back(best);

        // Update remainder = remainder - best * b
        std::vector<int> product;
        long long carry = 0;
        for (int j = 0; j < b.digits.size() || carry; ++j) {
            long long val = carry;
            if (j < b.digits.size()) {
                val += (long long)best * b.digits[j];
            }
            product.push_back(val % BASE);
            carry = val / BASE;
        }

        // Subtract product from remainder
        int borrow = 0;
        for (int j = 0; j < remainder.size(); ++j) {
            int diff = remainder[j] - borrow;
            if (j < product.size()) diff -= product[j];

            if (diff < 0) {
                diff += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
            remainder[j] = diff;
        }
        remove_leading_zeros(remainder);
    }

    // Reverse quotient since we built it backwards
    std::reverse(quotient.begin(), quotient.end());
    remove_leading_zeros(quotient);

    int2048 result(0);
    result.digits = quotient;
    result.sign = (a.sign == b.sign);

    // Handle floor division for cases where rounding toward negative infinity is needed
    if (!remainder.empty() && compare_abs(remainder, b.digits) != 0) {
        // If signs are different and there's a remainder, we need to subtract 1
        if (a.sign != b.sign) {
            result = result - int2048(1);
        }
    }

    return result;
}

int2048& int2048::operator%=(const int2048& other) {
    *this = *this % other;
    return *this;
}

int2048 operator%(int2048 a, const int2048& b) {
    int2048 quotient = a / b;
    int2048 product = quotient * b;
    int2048 remainder = a - product;
    return remainder;
}

// Stream operators
std::istream& operator>>(std::istream& is, int2048& num) {
    std::string str;
    is >> str;
    num.read(str);
    return is;
}

std::ostream& operator<<(std::ostream& os, const int2048& num) {
    if (!num.sign && !(num.digits.size() == 1 && num.digits[0] == 0)) {
        os << '-';
    }

    os << num.digits.back();

    for (int i = num.digits.size() - 2; i >= 0; --i) {
        char buf[BASE_DIGITS + 1];
        snprintf(buf, sizeof(buf), "%09d", num.digits[i]);
        os << buf;
    }

    return os;
}

// Comparison operators
bool operator==(const int2048& a, const int2048& b) {
    if (a.sign != b.sign) return false;
    return compare_abs(a.digits, b.digits) == 0;
}

bool operator!=(const int2048& a, const int2048& b) {
    return !(a == b);
}

bool operator<(const int2048& a, const int2048& b) {
    if (a.sign != b.sign) {
        return a.sign < b.sign;  // true < false, so positive < negative
    }

    int cmp = compare_abs(a.digits, b.digits);
    if (a.sign) {  // Both positive
        return cmp < 0;
    } else {  // Both negative
        return cmp > 0;
    }
}

bool operator>(const int2048& a, const int2048& b) {
    return b < a;
}

bool operator<=(const int2048& a, const int2048& b) {
    return !(a > b);
}

bool operator>=(const int2048& a, const int2048& b) {
    return !(a < b);
}

} // namespace sjtu