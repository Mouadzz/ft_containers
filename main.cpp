/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:07:30 by mlasrite          #+#    #+#             */
/*   Updated: 2021/09/22 12:29:03 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> obj(10, 100);

    std::cout << "size --> " << obj.size() << std::endl;
    std::cout << "capacity --> " << obj.max_size() << std::endl;

    obj.resize(5);
    std::cout << "size --> " << obj.size() << std::endl;
    std::cout << "capacity --> " << obj.max_size() << std::endl;

    obj.resize(10);
    std::cout << "size --> " << obj.size() << std::endl;
    std::cout << "capacity --> " << obj.max_size() << std::endl;

    obj.resize(20);
    std::cout << "size --> " << obj.size() << std::endl;
    std::cout << "capacity --> " << obj.max_size() << std::endl;

    system("leaks a.out");
}