/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:43:53 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 20:38:31 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "map.hpp"

int main()
{
    ft::map<char, int> mymap;

    // first insert function version (single parameter):
    mymap.insert(ft::pair<char, int>('a', 100));
    mymap.insert(ft::pair<char, int>('z', 200));

    ft::pair<ft::map<char, int>::iterator, bool> ret;
    ret = mymap.insert(ft::pair<char, int>('z', 500));
    if (ret.second == false)
    {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    ft::map<char, int>::iterator it = mymap.begin();
    mymap.insert(it, ft::pair<char, int>('b', 300)); // max efficiency inserting
    mymap.insert(it, ft::pair<char, int>('c', 400)); // no max efficiency inserting

    // third insert function version (range insertion):
    ft::map<char, int> anothermap;
    ft::map<char, int>::iterator be = mymap.begin();
    be++;
    be++;
    anothermap.insert(mymap.begin(), be);
    // showing contents:
    std::cout << "mymap contains:\n";
    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    std::cout << "anothermap contains:\n";
    for (it = anothermap.begin(); it != anothermap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}