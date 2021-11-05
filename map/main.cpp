/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:43:53 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 12:02:29 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "map.hpp"

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};

int main()
{
    ft::map<char, int> first;

    first.insert(ft::make_pair('a', 10));
    first.insert(ft::make_pair('b', 30));
    first.insert(ft::make_pair('c', 50));
    first.insert(ft::make_pair('d', 70));

    ft::map<char, int> second(first.begin(), first.end());

    ft::map<char, int> third(second);

    ft::map<char, int>::iterator it = third.begin();

    while (it != third.end())
    {
        std::cout << it->first << std::endl;
        it++;
    }

    ft::map<char, int, classcomp> fourth; // class as Compare

    bool (*fn_pt)(char, char) = fncomp;
    ft::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare

    return 0;
}