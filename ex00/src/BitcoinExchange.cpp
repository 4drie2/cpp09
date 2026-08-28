/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 17:48:43 by abidaux           #+#    #+#             */
/*   Updated: 2026/08/25 11:41:53 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other)
        _db = other._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::_trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";
    return str.substr(first, last - first + 1);
}

bool BitcoinExchange::_isValidDate(const std::string &date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    std::string digits = date.substr(0, 4) + date.substr(5, 2) + date.substr(8, 2);
    if (digits.find_first_not_of("0123456789") != std::string::npos)
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    int lengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        lengths[1] = 29;
    return month >= 1 && month <= 12 && day >= 1 && day <= lengths[month - 1];
}

bool BitcoinExchange::_isValidValue(const std::string &str, double &value) {
    if (str.empty() || str.find_first_not_of("0123456789+-.") != std::string::npos)
        return false;

    char *end;
    value = std::strtod(str.c_str(), &end);
    return *end == '\0';
}

bool BitcoinExchange::loadDatabase(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open database." << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        size_t sep = line.find(',');
        if (sep != std::string::npos)
            _db[_trim(line.substr(0, sep))] = std::strtod(line.substr(sep + 1).c_str(), NULL);
    }
    return !_db.empty();
}

void BitcoinExchange::processInput(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = _trim(line);
        if (line.empty() || line == "date | value")
            continue;

        size_t sep = line.find('|');
        if (sep == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        double value;
        std::string date = _trim(line.substr(0, sep));
        if (!_isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        std::string amount = _trim(line.substr(sep + 1));
        if (!_isValidValue(amount, value)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (amount[0] == '-') {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        std::map<std::string, double>::const_iterator it = _db.lower_bound(date);
        if (it == _db.end() || it->first != date) {
            if (it == _db.begin()) {
                std::cerr << "Error: no data before => " << date << std::endl;
                continue;
            }
            --it;
        }
        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    }
}
