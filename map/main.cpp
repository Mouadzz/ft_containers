/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:43:53 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 12:16:50 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "map.hpp"

int main()
{
    std::map<char, int> first;
    std::map<char, int> second;

    first.insert(std::make_pair('a', 10));
    first.insert(std::make_pair('b', 30));
    first.insert(std::make_pair('c', 50));
    first.insert(std::make_pair('d', 70));

    second = first; // second now contains 3 ints

    first = std::map<char, int>(); // and first is now empty

    std::cout << "Size of first: " << first.size() << '\n';
    std::cout << "Size of second: " << second.size() << '\n';
    return 0;
}