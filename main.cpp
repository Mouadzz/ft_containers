/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:07:30 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/05 14:33:54 by mlasrite         ###   ########.fr       */
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

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

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

int main()
{
  // std::cout << RED << "*------------------------ Testing the vector ------------------------*" << RESET << std::endl;
  // // sleep(1);
  // signal(SIGALRM, alarm_handler);
  // // iterator_tests();

  std::vector<int> real_vector;
  for (int i = 1; i <= 5; i++)
    real_vector.push_back(i);

  std::cout << "real_vector contains :";
  for (std::vector<int>::iterator it = real_vector.begin(); it != real_vector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::vector<int>::iterator real_it = real_vector.end();
  --real_it;
  std::cout << *real_it << std::endl;
  std::cout << *real_it++ << std::endl;
  std::cout << *real_it << std::endl;
  --real_it;
  std::cout << *--real_it << std::endl;
  std::cout << *real_it-- << std::endl;
  std::cout << *real_it << std::endl;

  std::vector<int>::iterator c_real_it = real_vector.begin();

  if (c_real_it == real_it)
    std::cout << "equal \n";

  if (c_real_it != real_it)
    std::cout << "unequal \n";

  if (c_real_it > real_it)
    std::cout << "copy > real \n";

  if (c_real_it < real_it)
    std::cout << "copy < real \n";

  if (c_real_it >= real_it)
    std::cout << "copy >= real \n";

  if (c_real_it <= real_it)
    std::cout << "copy <= real \n";

  *c_real_it = 696;

  c_real_it += 3;

  std::cout << *c_real_it << std::endl;

  c_real_it -= 2;

  std::cout << *c_real_it << std::endl;

  std::cout << c_real_it[0] << std::endl;

  std::vector<int>::iterator real_res = c_real_it - 4;
  std::cout << *real_res << std::endl;
  real_res = c_real_it + 1;
  std::cout << *real_res << std::endl;

  std::cout << "------------------------------------------\n";

  ft::vector<int> my_vector;
  for (int i = 1; i <= 5; i++)
    my_vector.push_back(i);

  std::cout << "my_vector contains   :";
  for (ft::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  ft::vector<int>::iterator my_it = my_vector.end();
  --my_it;
  std::cout << *my_it << std::endl;
  std::cout << *my_it++ << std::endl;
  std::cout << *my_it << std::endl;
  --my_it;
  std::cout << *--my_it << std::endl;
  std::cout << *my_it-- << std::endl;
  std::cout << *my_it << std::endl;

  ft::vector<int>::iterator c_my_it = my_vector.begin();

  if (c_my_it == my_it)
    std::cout << "equal \n";

  if (c_my_it != my_it)
    std::cout << "unequal \n";

  if (c_my_it > my_it)
    std::cout << "copy > real \n";

  if (c_my_it < my_it)
    std::cout << "copy < real \n";

  if (c_my_it >= my_it)
    std::cout << "copy >= real \n";

  if (c_my_it <= my_it)
    std::cout << "copy <= real \n";

  *c_my_it = 696;

  c_my_it += 3;

  std::cout << *c_my_it << std::endl;

  c_my_it -= 2;

  std::cout << *c_my_it << std::endl;
  std::cout << c_my_it[0] << std::endl;

  ft::vector<int>::iterator my_res = c_my_it - 4;
  std::cout << *my_res << std::endl;
  my_res = c_my_it + 1;
  std::cout << *my_res << std::endl;

  return 0;
}