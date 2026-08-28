/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:20:04 by abidaux           #+#    #+#             */
/*   Updated: 2026/08/26 11:09:17 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) {
    *this = other;
}

RPN &RPN::operator=(const RPN &other) {
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN() {}

int RPN::compute(const std::string &expr) {
    std::istringstream iss(expr);
    std::string token;

    while (iss >> token) {
        if (token.size() != 1)
            throw std::runtime_error("Error");

        char op = token[0];
        if (op >= '0' && op <= '9') {
            _stack.push(op - '0');
            continue;
        }
        if (_stack.size() < 2 || std::string("+-*/").find(op) == std::string::npos)
            throw std::runtime_error("Error");

        int b = _stack.top();
        _stack.pop();
        int a = _stack.top();
        _stack.pop();
        if (op == '/' && b == 0)
            throw std::runtime_error("Error");
        _stack.push(op == '+' ? a + b : op == '-' ? a - b : op == '*' ? a * b : a / b);
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error");
    return _stack.top();
}
