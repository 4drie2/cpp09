/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 14:52:10 by abidaux           #+#    #+#             */
/*   Updated: 2026/08/28 16:20:35 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <stdexcept>
#include <cstdlib>
#include <climits>
#include <ctime>

class PmergeMe {
    std::vector<int> _vec;
    std::deque<int> _deq;

    static int _toInt(const std::string &arg);
    static double _now();
    static void _sort(std::vector<int> &v);
    static void _sort(std::deque<int> &d);

public :
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void run(int ac, char **av);
} ;

#endif
