/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:07:30 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/07 13:34:28 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

// #define BLUE "\e[0;34m"
// #define RED "\e[0;31m"
// #define GREEN "\e[0;32m"
// #define YELLOW "\e[1;33m"
// #define RESET "\e[0m"

// #define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
// #define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

// void iterator_tests(void)
// {
//   std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
//   /*------------ std::vector ---------*/
//   std::vector<int> v(3, 4);
//   std::vector<int>::iterator it, it1;
//   it = v.begin();
//   it1 = v.begin() + 1;
//   /*----------------------------------*/
//   /*------------ ft::Vector ---------*/
//   ft::vector<int> my_v(3, 4);
//   ft::vector<int>::iterator my_it, my_it1, tmp;
//   my_it = my_v.begin();
//   my_it1 = my_v.begin() + 1;
//   /*----------------------------------*/
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
//             << "] --------------------]\t\t\033[0m";
//   {
//     ft::vector<int>::iterator ob(my_it);
//     EQUAL(&(*my_it) == &(*ob));
//   }
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
//             << "] --------------------]\t\t\033[0m";
//   {
//     ft::vector<int>::const_iterator c_it, c_ob(my_it);
//     c_it = my_it;
//     EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
//   }
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL((it == it1) == (my_it == my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL((it != it1) == (my_it != my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL((it > it1) == (my_it > my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL((it >= it1) == (my_it >= my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL((it < it1) == (my_it < my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL((it <= it1) == (my_it <= my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL(((*my_it = 6) == 6) && (*my_it == *(my_v.begin())));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
//             << "] --------------------]\t\t\033[0m";
//   {
//     /*--------------- std::vector-------------------- */
//     std::vector<std::string> v(3, "hello");
//     std::vector<std::string>::iterator it = v.begin();
//     /*---------------------------------------------- */
//     /*--------------- ft::vector-------------------- */
//     ft::vector<std::string> my_v(3, "hello");
//     ft::vector<std::string>::iterator my_it = my_v.begin();
//     /*---------------------------------------------- */
//     EQUAL(it->length() == my_it->length());
//   }
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL(&(*my_it) == &(*(my_it1 - 1)));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
//             << "] --------------------]\t\t\033[0m";
//   my_it += 1;
//   EQUAL(&(*my_it) == &(*my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
//             << "] --------------------]\t\t\033[0m";
//   my_it -= 1;
//   EQUAL(&(*my_it) == &(*(my_it1 - 1)));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL(((my_it[0] = 5) == 5) && (*my_it == 5));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
//             << "] --------------------]\t\t\033[0m";
//   ++my_it; // I incremented here to make sure that the object changes
//   EQUAL(&(*my_it) == &(*my_it1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
//             << "] --------------------]\t\t\033[0m";
//   --my_it; // I decremented here to make sure that the object changes
//   EQUAL(&(*my_it) == &(*(my_it1 - 1)));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
//             << "] --------------------]\t\t\033[0m";
//   EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
//             << "] --------------------]\t\t\033[0m";
//   tmp = my_it++;
//   EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
//   std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
//             << "] --------------------]\t\t\033[0m";
//   tmp = my_it--;
//   EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
//   std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
// }

// void alarm_handler(int seg)
// {
//   (void)seg;
//   std::cout << "\033[1;33mTLE\033[0m\n";
//   kill(getpid(), SIGINT);
// }

class A
{
};

int main()
{
  // std::cout << RED << "*------------------------ Testing the vector ------------------------*" << RESET << std::endl;
  // // sleep(1);
  // signal(SIGALRM, alarm_handler);
  // // iterator_tests();

  ft::vector<int> first;                              
  ft::vector<int> second(4, 100);                     
  ft::vector<int> third(second.begin(), second.end()); 
  ft::vector<int> fourth(third);      
  std::cout << fourth.size() << std::endl;                 

  int myints[] = {16, 2, 77, 29};
  ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));


  std::cout << "The contents of fifth are:";
  for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}