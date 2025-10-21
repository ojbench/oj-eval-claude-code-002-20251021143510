#include "src/include/int2048.h"
#include <iostream>
#include <cassert>

using namespace sjtu;

void test_basic_operations() {
    std::cout << "Testing basic operations..." << std::endl;

    // Test constructors
    int2048 a;
    int2048 b(123);
    int2048 c("-456");
    int2048 d("123456789012345678901234567890");

    // Test read and print
    a.read("100");
    std::cout << "a = ";
    a.print();
    std::cout << std::endl;

    // Test addition
    int2048 e = add(a, b);
    std::cout << a << " + " << b << " = " << e << std::endl;
    assert(e == int2048(223));

    // Test subtraction
    int2048 f = minus(b, int2048(23));
    std::cout << b << " - 23 = " << f << std::endl;
    assert(f == int2048(100));

    std::cout << "Basic operations tests passed!" << std::endl;
}

void test_operator_overloading() {
    std::cout << "Testing operator overloading..." << std::endl;

    int2048 a("100000000000000000000");
    int2048 b("99999999999999999999");

    // Test arithmetic operators
    int2048 c = a + b;
    std::cout << a << " + " << b << " = " << c << std::endl;

    int2048 d = a - b;
    std::cout << a << " - " << b << " = " << d << std::endl;

    int2048 e = a * b;
    std::cout << a << " * " << b << " = " << e << std::endl;

    int2048 f = a / b;
    std::cout << a << " / " << b << " = " << f << std::endl;

    int2048 g = a % b;
    std::cout << a << " % " << b << " = " << g << std::endl;

    // Test compound assignment
    int2048 h = a;
    h += b;
    std::cout << a << " += " << b << " => " << h << std::endl;
    assert(h == c);

    // Test comparison operators
    assert(a > b);
    assert(b < a);
    assert(!(a == b));
    assert(a != b);

    std::cout << "Operator overloading tests passed!" << std::endl;
}

void test_floor_division() {
    std::cout << "Testing floor division..." << std::endl;

    // Positive division
    int2048 a(10), b(3);
    int2048 c = a / b;
    std::cout << a << " / " << b << " = " << c << " (should be 3)" << std::endl;
    assert(c == int2048(3));

    // Negative dividend, positive divisor (should round down)
    int2048 d(-10), e(3);
    int2048 f = d / e;
    std::cout << d << " / " << e << " = " << f << " (should be -4)" << std::endl;
    assert(f == int2048(-4));

    // Positive dividend, negative divisor (should round down)
    int2048 g(10), h(-3);
    int2048 i = g / h;
    std::cout << g << " / " << h << " = " << i << " (should be -4)" << std::endl;
    assert(i == int2048(-4));

    // Negative dividend, negative divisor (should round down)
    int2048 j(-10), k(-3);
    int2048 l = j / k;
    std::cout << j << " / " << k << " = " << l << " (should be 3)" << std::endl;
    assert(l == int2048(3));

    std::cout << "Floor division tests passed!" << std::endl;
}

void test_stream_operations() {
    std::cout << "Testing stream operations..." << std::endl;

    int2048 a;
    std::string input = "12345678901234567890";
    std::istringstream iss(input);
    iss >> a;
    std::cout << "Read from string: " << a << std::endl;

    std::ostringstream oss;
    oss << a;
    std::string output = oss.str();
    std::cout << "Written to string: " << output << std::endl;

    assert(input == output);

    std::cout << "Stream operations tests passed!" << std::endl;
}

int main() {
    try {
        test_basic_operations();
        test_operator_overloading();
        test_floor_division();
        test_stream_operations();

        std::cout << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}