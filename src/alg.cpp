// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <map>
#include <functional>
#include <stack>
#include <sstream>
#include "../include/tstack.h"
int getPriority(char op) {
    std::map<char, int> priorities = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };
    return priorities[op];
}
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> operators;
    std::string result;
    for (size_t i = 0; i < inf.length(); i++) {
        char c = inf[i];
        if (c == ' ') {
            continue;
        }
        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                i++;
            }
            result += ' ';
            i--;
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.isEmpty() && operators.top() != '(') {
                result += operators.pop();
                result += ' ';
            }
            if (!operators.isEmpty() && operators.top() == '(') {
                operators.pop();
            }
        }
        else if (isOperator(c)) {
            while (!operators.isEmpty() && operators.top() != '(' && 
                   getPriority(operators.top()) >= getPriority(c)) {
                result += operators.pop();
                result += ' ';
            }
            operators.push(c);
        }
    }
    while (!operators.isEmpty()) {
        result += operators.pop();
        result += ' ';
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}
int eval(const std::string& post) {
    TStack<int, 100> values;
    std::stringstream ss(post);
    std::string token;
    while (ss >> token) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            values.push(std::stoi(token));
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            int b = values.pop();
            int a = values.pop();
            int result = 0;
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            values.push(result);
        }
    }
    return values.pop();
}
