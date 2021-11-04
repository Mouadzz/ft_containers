/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:43:53 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 16:59:31 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "map.hpp"

int main()
{
    ft::map<int, int> first;

    for (int i = 0; i < 20; i++)
    {
        first.insert(ft::make_pair(i, i + 43));
    }

    // ft::map<char, int> second(first.begin(), first.end());

    ft::map<int, int>::iterator it = first.begin();

    while (it != first.end())
    {
        std::cout << it->first << std::endl;
        it++;
    }

    return 0;
}