/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:43:53 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 16:45:24 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "map.hpp"

int main()
{
    ft::map<char, int> mymap;

    mymap.insert(ft::make_pair('a', 3232));

    ft::pair<ft::map<char, int>::iterator, bool> ret;

    ret = mymap.insert(ft::make_pair('a', 10));

    std::cout << ret.first->first << " " << ret.second << std::endl;

    return 0;
}