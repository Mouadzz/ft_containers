/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:43:53 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 13:23:52 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "map.hpp"

int main()
{
    ft::map<char, int> first;

    first.insert(ft::make_pair('a', 10));
    first.insert(ft::make_pair('b', 30));
    first.insert(ft::make_pair('c', 50));
    first.insert(ft::make_pair('d', 70));

    ft::map<char, int> second(first.begin(), first.end());
    
    return 0;
}