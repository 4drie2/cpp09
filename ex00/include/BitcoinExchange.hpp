/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 17:29:15 by abidaux           #+#    #+#             */
/*   Updated: 2026/08/25 11:22:41 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

class BitcoinExchange {
    std::map<std::string, double> _db;

    static std::string _trim(const std::string &str);
    static bool _isValidDate(const std::string &date);
    static bool _isValidValue(const std::string &str, double &value);

public :
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    bool loadDatabase(const std::string &filename);
    void processInput(const std::string &filename);
} ;
