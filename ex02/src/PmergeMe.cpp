/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:07:33 by abidaux           #+#    #+#             */
/*   Updated: 2026/08/28 23:23:06 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

int PmergeMe::_toInt(const std::string &arg) {
    if (arg.empty() || arg.find_first_not_of("0123456789") != std::string::npos)
        throw std::runtime_error("Error");

    long nb = std::strtol(arg.c_str(), NULL, 10);
    if (nb > INT_MAX)
        throw std::runtime_error("Error");
    return static_cast<int>(nb);
}

double PmergeMe::_now() {
    return static_cast<double>(std::clock()) * 1000000.0 / CLOCKS_PER_SEC;
}

void PmergeMe::_sort(std::vector<int> &v) {
    if (v.size() < 2)
        return;

    std::vector<int> chain, pend;
    for (size_t i = 0; i + 1 < v.size(); i += 2) {
        chain.push_back(std::max(v[i], v[i + 1]));
        pend.push_back(std::min(v[i], v[i + 1]));
    }
    if (v.size() % 2)
        pend.push_back(v.back());
    _sort(chain);

    size_t prev = 1, cur = 1, done = 0;
    while (done < pend.size()) {
        size_t group = std::min(cur, pend.size());
        for (size_t i = group; i > done; --i)
            chain.insert(std::upper_bound(chain.begin(), chain.end(), pend[i - 1]), pend[i - 1]);
        done = group;
        size_t next = cur + 2 * prev;
        prev = cur;
        cur = next;
    }
    v = chain;
}

void PmergeMe::_sort(std::deque<int> &d) {
    if (d.size() < 2)
        return;

    std::deque<int> chain, pend;
    for (size_t i = 0; i + 1 < d.size(); i += 2) {
        chain.push_back(std::max(d[i], d[i + 1]));
        pend.push_back(std::min(d[i], d[i + 1]));
    }
    if (d.size() % 2)
        pend.push_back(d.back());
    _sort(chain);

    size_t prev = 1, cur = 1, done = 0;
    while (done < pend.size()) {
        size_t group = std::min(cur, pend.size());
        for (size_t i = group; i > done; --i)
            chain.insert(std::upper_bound(chain.begin(), chain.end(), pend[i - 1]), pend[i - 1]);
        done = group;
        size_t next = cur + 2 * prev;
        prev = cur;
        cur = next;
    }
    d = chain;
}

void PmergeMe::run(int ac, char **av) {
    for (int i = 1; i < ac; ++i)
        _toInt(av[i]);

    std::cout << "Before:";
    for (int i = 1; i < ac; ++i)
        std::cout << " " << av[i];
    std::cout << std::endl;

    double start = _now();
    for (int i = 1; i < ac; ++i)
        _vec.push_back(_toInt(av[i]));
    _sort(_vec);
    double vecTime = _now() - start;

    start = _now();
    for (int i = 1; i < ac; ++i)
        _deq.push_back(_toInt(av[i]));
    _sort(_deq);
    double deqTime = _now() - start;

    std::cout << "After:";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << " " << _vec[i];
    std::cout << std::endl << std::fixed << std::setprecision(5)
              << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << vecTime << " us" << std::endl
              << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << deqTime << " us" << std::endl;
}
