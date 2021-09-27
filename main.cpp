/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:07:30 by mlasrite          #+#    #+#             */
/*   Updated: 2021/09/25 12:17:50 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <vector>

int main()
{
  ft::vector<int> foo(3, 199); // three ints with a value of 100
  ft::vector<int> bar(3, 200); // two ints with a value of 200

  if (foo == bar)
    std::cout << "foo and bar are equal\n";
  if (foo != bar)
    std::cout << "foo and bar are not equal\n";
  if (foo < bar)
    std::cout << "foo is less than bar\n";
  if (foo > bar)
    std::cout << "foo is greater than bar\n";
  if (foo <= bar)
    std::cout << "foo is less than or equal to bar\n";
  if (foo >= bar)
    std::cout << "foo is greater than or equal to bar\n";

  std::cout << "--------------------------------------------\n";

  std::vector<int> foof(3, 199); // three ints with a value of 100
  std::vector<int> barr(3, 200); // two ints with a value of 200

  if (foof == barr)
    std::cout << "foo and bar are equal\n";
  if (foof != barr)
    std::cout << "foo and bar are not equal\n";
  if (foof < barr)
    std::cout << "foo is less than bar\n";
  if (foof > barr)
    std::cout << "foo is greater than bar\n";
  if (foof <= barr)
    std::cout << "foo is less than or equal to bar\n";
  if (foof >= barr)
    std::cout << "foo is greater than or equal to bar\n";

  return 0;
}