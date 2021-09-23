/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:07:30 by mlasrite          #+#    #+#             */
/*   Updated: 2021/09/23 12:22:20 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> obj(3);

    obj[0] = 1;
    obj[1] = 2;
    obj[2] = 3;
    std::cout << "size --> " << obj.size() << std::endl;
    std::cout << "capacity --> " << obj.capacity() << std::endl;
    std::cout << "max size --> " << obj.max_size() << std::endl;

    std::cout << obj.front() << std::endl;
    std::cout << obj.back() << std::endl;
}