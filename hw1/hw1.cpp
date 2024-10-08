﻿#include <iostream>
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
    bool negative = false; // 用來處理負號

    while (iss >> ch) {
        if (ch == '-') {
            negative = true; // 遇到負號，標記為負數
        }
        else if (ch == '(' || ch == ',') {
            continue; // 跳過不必要的符號
        }
        else if (isdigit(ch)) {
            iss.putback(ch); // 將數字放回流中以便下一步讀取
            iss >> coefficient >> ch >> exponent; // 讀入係數和指數
            if (negative) {
                coefficient = -coefficient; // 如果之前標記為負數，將係數轉為負數
                negative = false; // 重置負號標記
            }
            polynomial.emplace_back(coefficient, exponent); // 將係數和指數加入多項式
        }
    }
    return polynomial;
}

// 將多項式轉換為字串格式
std::string polynomialToString(const std::vector<std::pair<int, int>>& polynomial) {
    std::ostringstream oss;
    bool firstTerm = true; // 用來處理第一個項目

    for (const auto& term : polynomial) {
        if (term.first == 0) continue; // 跳過係數為0的項
        if (term.first > 0 && !firstTerm) oss << "+"; // 如果不是第一個項目且係數為正數，前面加上'+'
        oss << term.first;
        if (term.second != 0) {
            oss << "x"; // 如果指數不為0，顯示x
            if (term.second != 1) oss << "^" << term.second; // 如果指數不是1，顯示指數
        }
        firstTerm = false; // 第一項處理完畢
    }
    return oss.str();
}

// 多項式相加
std::vector<std::pair<int, int>> addPolynomials(const std::vector<std::pair<int, int>>& poly1, const std::vector<std::pair<int, int>>& poly2) {
    std::map<int, int> result;

    // 將第一個多項式的項加入結果
    for (const auto& term : poly1) {
        result[term.second] += term.first;
    }

    // 將第二個多項式的項加入結果
    for (const auto& term : poly2) {
        result[term.second] += term.first;
    }

    // 將結果轉換為向量
    std::vector<std::pair<int, int>> sum;
    for (const auto& term : result) {
        if (term.second != 0) {
            sum.emplace_back(term.second, term.first);
        }
    }

    // 按指數降序排序
    std::sort(sum.begin(), sum.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    return sum;
}

// 多項式相乘
std::vector<std::pair<int, int>> multiplyPolynomials(const std::vector<std::pair<int, int>>& poly1, const std::vector<std::pair<int, int>>& poly2) {
    std::map<int, int> result;

    // 計算每一項的乘積並加入結果
    for (const auto& term1 : poly1) {
        for (const auto& term2 : poly2) {
            result[term1.second + term2.second] += term1.first * term2.first;
        }
    }

    // 將結果轉換為向量
    std::vector<std::pair<int, int>> product;
    for (const auto& term : result) {
        if (term.second != 0) {
            product.emplace_back(term.second, term.first);
        }
    }

    // 按指數降序排序
    std::sort(product.begin(), product.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    return product;
}

int main() {
    std::string input1, input2;

    // 提示使用者輸入多項式
    std::cout << "請輸入第一個多項式 (格式: (係數, 指數, 係數, 指數, ...)): ";
    std::getline(std::cin, input1);
    std::cout << "請輸入第二個多項式 (格式: (係數, 指數, 係數, 指數, ...)): ";
    std::getline(std::cin, input2);

    // 解析輸入的多項式
    auto poly1 = parsePolynomial(input1);
    auto poly2 = parsePolynomial(input2);

    // 顯示解析後的多項式
    std::cout << "多項式1: " << polynomialToString(poly1) << std::endl;
    std::cout << "多項式2: " << polynomialToString(poly2) << std::endl;

    // 計算並顯示相加結果
    auto sum = addPolynomials(poly1, poly2);
    std::cout << "相加結果: " << polynomialToString(sum) << std::endl;

    // 計算並顯示相乘結果
    auto product = multiplyPolynomials(poly1, poly2);
    std::cout << "相乘結果: " << polynomialToString(product) << std::endl;

    return 0;
}
