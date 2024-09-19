#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

// 解析多項式字串並轉換為係數和指數的向量
std::vector<std::pair<int, int>> parsePolynomial(const std::string& input) {
    std::vector<std::pair<int, int>> polynomial;
    std::istringstream iss(input);
    char ch;
    int coefficient, exponent;
    while (iss >> ch >> coefficient >> ch >> exponent >> ch) {
        polynomial.emplace_back(coefficient, exponent);
    }
    return polynomial;
}

// 將多項式轉換為字串格式
std::string polynomialToString(const std::vector<std::pair<int, int>>& polynomial) {
    std::ostringstream oss;
    for (const auto& term : polynomial) {
        if (term.first == 0) continue;
        if (term.first > 0 && &term != &polynomial[0]) oss << "+";
        oss << term.first;
        if (term.second != 0) oss << "x^" << term.second;
    }
    return oss.str();
}

// 多項式相加
std::vector<std::pair<int, int>> addPolynomials(const std::vector<std::pair<int, int>>& poly1, const std::vector<std::pair<int, int>>& poly2) {
    std::map<int, int> result;
    for (const auto& term : poly1) {
        result[term.second] += term.first;
    }
    for (const auto& term : poly2) {
        result[term.second] += term.first;
    }
    std::vector<std::pair<int, int>> sum;
    for (const auto& term : result) {
        if (term.second != 0) {
            sum.emplace_back(term.second, term.first);
        }
    }
    std::sort(sum.begin(), sum.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    return sum;
}

// 多項式相乘
std::vector<std::pair<int, int>> multiplyPolynomials(const std::vector<std::pair<int, int>>& poly1, const std::vector<std::pair<int, int>>& poly2) {
    std::map<int, int> result;
    for (const auto& term1 : poly1) {
        for (const auto& term2 : poly2) {
            result[term1.second + term2.second] += term1.first * term2.first;
        }
    }
    std::vector<std::pair<int, int>> product;
    for (const auto& term : result) {
        if (term.second != 0) {
            product.emplace_back(term.second, term.first);
        }
    }
    std::sort(product.begin(), product.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    return product;
}

int main() {
    std::string input1, input2;

    std::cout << "請輸入第一個多項式 (格式: (係數, 指數, 係數, 指數, ...)): ";
    std::getline(std::cin, input1);
    std::cout << "請輸入第二個多項式 (格式: (係數, 指數, 係數, 指數, ...)): ";
    std::getline(std::cin, input2);

    auto poly1 = parsePolynomial(input1);
    auto poly2 = parsePolynomial(input2);

    std::cout << "多項式1: " << polynomialToString(poly1) << std::endl;
    std::cout << "多項式2: " << polynomialToString(poly2) << std::endl;

    auto sum = addPolynomials(poly1, poly2);
    auto product = multiplyPolynomials(poly1, poly2);

    std::cout << "相加結果: " << polynomialToString(sum) << std::endl;
    std::cout << "相乘結果: " << polynomialToString(product) << std::endl;

    return 0;
}
