/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:07:30 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/21 19:20:44 by mlasrite         ###   ########.fr       */
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

void iterator_tests(void)
{
  std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
  /*------------ std::vector ---------*/
  std::vector<int> v(3, 4);
  std::vector<int>::iterator it, it1;
  it = v.begin();
  it1 = v.begin() + 1;
  /*----------------------------------*/
  /*------------ ft::vector ---------*/
  ft::vector<int> my_v(3, 4);
  ft::vector<int>::iterator my_it, my_it1, tmp;
  my_it = my_v.begin();
  my_it1 = my_v.begin() + 1;
  /*----------------------------------*/
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
            << "] --------------------]\t\t\033[0m";
  {
    ft::vector<int>::iterator ob(my_it);
    EQUAL(&(*my_it) == &(*ob));
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
            << "] --------------------]\t\t\033[0m";
  {
    ft::vector<int>::const_iterator c_it, c_ob(my_it);
    c_it = my_it;
    EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it == it1) == (my_it == my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it != it1) == (my_it != my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it > it1) == (my_it > my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it >= it1) == (my_it >= my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it < it1) == (my_it < my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it <= it1) == (my_it <= my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL(((*my_it = 6) == 6) && (*my_it == *(my_v.begin())));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
            << "] --------------------]\t\t\033[0m";
  {
    /*--------------- std::vector-------------------- */
    std::vector<std::string> v(3, "hello");
    std::vector<std::string>::iterator it = v.begin();
    /*---------------------------------------------- */
    /*--------------- ft::vector-------------------- */
    ft::vector<std::string> my_v(3, "hello");
    ft::vector<std::string>::iterator my_it = my_v.begin();
    /*---------------------------------------------- */
    EQUAL(it->length() == my_it->length());
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL(&(*my_it) == &(*(my_it1 - 1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
            << "] --------------------]\t\t\033[0m";
  my_it += 1;
  EQUAL(&(*my_it) == &(*my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
            << "] --------------------]\t\t\033[0m";
  my_it -= 1;
  EQUAL(&(*my_it) == &(*(my_it1 - 1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL(((my_it[0] = 5) == 5) && (*my_it == 5));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
            << "] --------------------]\t\t\033[0m";
  ++my_it; // I incremented here to make sure that the object changes
  EQUAL(&(*my_it) == &(*my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
            << "] --------------------]\t\t\033[0m";
  --my_it; // I decremented here to make sure that the object changes
  EQUAL(&(*my_it) == &(*(my_it1 - 1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
            << "] --------------------]\t\t\033[0m";
  EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
            << "] --------------------]\t\t\033[0m";
  EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
            << "] --------------------]\t\t\033[0m";
  tmp = my_it++;
  EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
            << "] --------------------]\t\t\033[0m";
  tmp = my_it--;
  EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
  std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void const_iterator_tests(void)
{
  std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector const_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
  /*------------ std::vector ---------*/
  std::vector<int> v(3, 4);
  std::vector<int>::const_iterator it, it1;
  it = v.begin();
  it1 = v.begin() + 1;
  /*----------------------------------*/
  /*------------ ft::vector ---------*/
  ft::vector<int> my_v(3, 4);
  ft::vector<int>::const_iterator my_it, my_it1, tmp;
  my_it = my_v.begin();
  my_it1 = my_v.begin() + 1;
  /*----------------------------------*/
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
            << "] --------------------]\t\t\033[0m";
  {
    ft::vector<int>::const_iterator ob(my_it);
    EQUAL(&(*my_it) == &(*ob));
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it == it1) == (my_it == my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it != it1) == (my_it != my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it > it1) == (my_it > my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it >= it1) == (my_it >= my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it < it1) == (my_it < my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((it <= it1) == (my_it <= my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL(*my_it == *(my_v.begin()) && (&(*my_it) == &(*(my_v.begin()))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
            << "] --------------------]\t\t\033[0m";
  {
    /*--------------- std::vector-------------------- */
    std::vector<std::string> v(3, "hello");
    std::vector<std::string>::const_iterator it = v.begin();
    /*---------------------------------------------- */
    /*--------------- ft::vector-------------------- */
    ft::vector<std::string> my_v(3, "hello");
    ft::vector<std::string>::const_iterator my_it = my_v.begin();
    /*---------------------------------------------- */
    EQUAL(it->length() == my_it->length());
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL(&(*my_it) == &(*(my_it1 - 1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
            << "] --------------------]\t\t\033[0m";
  my_it += 1;
  EQUAL(&(*my_it) == &(*my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
            << "] --------------------]\t\t\033[0m";
  my_it -= 1;
  EQUAL(&(*my_it) == &(*(my_it1 - 1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((my_it[0] == *(my_v.begin())) && (&(my_it[0]) == &(*(my_v.begin()))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
            << "] --------------------]\t\t\033[0m";
  ++my_it; // I incremented here to make sure that the object changes
  EQUAL(&(*my_it) == &(*my_it1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
            << "] --------------------]\t\t\033[0m";
  --my_it; // I decremented here to make sure that the object changes
  EQUAL(&(*my_it) == &(*(my_it1 - 1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
            << "] --------------------]\t\t\033[0m";
  EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
            << "] --------------------]\t\t\033[0m";
  EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
            << "] --------------------]\t\t\033[0m";
  tmp = my_it++;
  EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
            << "] --------------------]\t\t\033[0m";
  tmp = my_it--;
  EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
  std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void reverse_iterator_tests(void)
{
  std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
  /*------------ std::reverse_iterator ---------*/
  std::vector<int> v(3, 4);
  std::reverse_iterator<std::vector<int>::iterator> rit(v.end()), rit_1(v.end() - 1);
  /*----------------------------------*/
  /*------------ ft::reverse_iterator ---------*/
  ft::reverse_iterator<std::vector<int>::iterator> my_rit(v.end()), my_rit1(v.end() - 1);
  /*----------------------------------*/
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
            << "] --------------------]\t\t\033[0m";
  {
    ft::reverse_iterator<std::vector<int>::iterator> ob(my_rit);
    EQUAL(&(*my_rit) == &(*ob));
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " riterator to const_riterator "
            << "] --------------------]\t\t\033[0m";
  {
    ft::vector<int> v(4, 5);
    ft::vector<int>::reverse_iterator my_rit2(v.end());
    ft::vector<int>::const_reverse_iterator c_it, c_ob(v.end());
    c_it = my_rit2;
    EQUAL(&(*my_rit2) == &(*c_it) && (&(*my_rit2) == &(*c_ob)));
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
            << "] --------------------]\t\t\033[0m";
  EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((rit == rit_1) == (my_rit == my_rit1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((rit != rit_1) == (my_rit != my_rit1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((rit > rit_1) == (my_rit > my_rit1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((rit < rit_1) == (my_rit < my_rit1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL(((*my_rit == *(v.end() - 1)) && (&(*my_rit) == &(*(v.end() - 1)))) && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
            << "] --------------------]\t\t\033[0m";
  {
    std::vector<std::string> v(3, "hello");
    std::reverse_iterator<std::vector<std::string>::iterator> rit(v.end());
    ft::reverse_iterator<std::vector<std::string>::iterator> my_rit(v.end());
    EQUAL(rit->length() == my_rit->length());
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
            << "] --------------------]\t\t\033[0m";
  my_rit += 1;
  rit += 1;
  EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
            << "] --------------------]\t\t\033[0m";
  my_rit -= 1;
  rit -= 1;
  EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
            << "] --------------------]\t\t\033[0m";
  EQUAL(((my_rit[0] = 5) == 5) && (rit[0] == 5));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
            << "] --------------------]\t\t\033[0m";
  ++my_rit; // I incremented here to make sure that the object changes
  ++rit;
  EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
            << "] --------------------]\t\t\033[0m";
  --my_rit; // I incremented here to make sure that the object changes
  --rit;
  EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) "
            << "] --------------------]\t\t\033[0m";
  EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) "
            << "] --------------------]\t\t\033[0m";
  EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
            << "] --------------------]\t\t\033[0m";
  {
    std::reverse_iterator<std::vector<int>::iterator> tmp(rit++);
    ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit++);
    EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
            << "] --------------------]\t\t\033[0m";
  {
    std::reverse_iterator<std::vector<int>::iterator> tmp(rit--);
    ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit--);
    EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
  }
  std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test "
            << "] --------------------]\t\t\033[0m";
  {
    std::vector<char> v(10);
    std::string res, my_res;
    std::reverse_iterator<std::vector<char>::iterator> start(v.end()), end(v.begin());
    ft::reverse_iterator<std::vector<char>::iterator> my_start(v.end()), my_end(v.begin());

    for (size_t i = 0; i < 10; ++i)
      v[i] = '0' + i;
    while (start != end)
      res.push_back(*start++);
    while (my_start != my_end)
      my_res.push_back(*my_start++);
    EQUAL(res == my_res);
  }
  std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

// void    reverse_iterator_with_ft_vector(void)
// {
//     std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator with ft::vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
//     /*------------ std::reverse_iterator ---------*/
//     std::vector<int> v(3,4);
//     std::vector<int>::reverse_iterator rit(v.end()), rit_1(v.end() - 1);
//     /*----------------------------------*/
//     /*------------ ft::reverse_iterator ---------*/
//     ft::vector<int> my_v(3,4);
//     ft::vector<int>::reverse_iterator my_rit(my_v.end()), my_rit1(my_v.end() - 1);
//     /*----------------------------------*/
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor " << "] --------------------]\t\t\033[0m";
//     {
//         ft::vector<int>::reverse_iterator ob(my_rit);
//         EQUAL(&(*my_rit) == &(*ob));
//     }
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function " << "] --------------------]\t\t\033[0m";
//     EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator " << "] --------------------]\t\t\033[0m";
//     EQUAL((rit == rit_1) == (my_rit == my_rit1));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator " << "] --------------------]\t\t\033[0m";
//     EQUAL((rit != rit_1) == (my_rit != my_rit1));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator " << "] --------------------]\t\t\033[0m";
//     EQUAL((rit > rit_1) == (my_rit > my_rit1));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator " << "] --------------------]\t\t\033[0m";
//     EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator " << "] --------------------]\t\t\033[0m";
//     EQUAL((rit < rit_1) == (my_rit < my_rit1));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator " << "] --------------------]\t\t\033[0m";
//     EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator " << "] --------------------]\t\t\033[0m";
//     EQUAL(((*my_rit == *(my_v.end() - 1)) && (&(*my_rit) == &(*(my_v.end() - 1))))
//     && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator " << "] --------------------]\t\t\033[0m";
//     {
//         std::vector<std::string> v(3, "hello");
//         ft::vector<std::string> my_v(3, "hello");
//         std::vector<std::string>::reverse_iterator rit(v.end());
//         ft::vector<std::string>::reverse_iterator   my_rit(my_v.end());
//         EQUAL(rit->length() == my_rit->length());
//     }
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator " << "] --------------------]\t\t\033[0m";
// 	EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator " << "] --------------------]\t\t\033[0m";
// 	EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator " << "] --------------------]\t\t\033[0m";
// 	my_rit += 1;
// 	rit += 1;
// 	EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator " << "] --------------------]\t\t\033[0m";
// 	my_rit -= 1;
// 	rit -= 1;
// 	EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator " << "] --------------------]\t\t\033[0m";
// 	EQUAL((my_rit[0] = 5) == 5);
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator " << "] --------------------]\t\t\033[0m";
//     ++my_rit; // I incremented here to make sure that the object changes
//     ++rit;
// 	EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator " << "] --------------------]\t\t\033[0m";
//     --my_rit; // I incremented here to make sure that the object changes
//     --rit;
// 	EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) " << "] --------------------]\t\t\033[0m";
// 	EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) " << "] --------------------]\t\t\033[0m";
//     EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator " << "] --------------------]\t\t\033[0m";
//     {
//         std::vector<int>::reverse_iterator   tmp(rit++);
//         ft::vector<int>::reverse_iterator    my_tmp(my_rit++);
//         EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
//     }
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator " << "] --------------------]\t\t\033[0m";
//     {
//         std::vector<int>::reverse_iterator   tmp(rit--);
//         ft::vector<int>::reverse_iterator    my_tmp(my_rit--);
//         EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
//     }
//     std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test " << "] --------------------]\t\t\033[0m";
//     {
//         std::vector<char> v(10);
//         ft::vector<char> my_v(10);
//         std::string res, my_res;
//         std::vector<char>::reverse_iterator start(v.end()), end(v.begin());
//         ft::vector<char>::reverse_iterator 	my_start(my_v.end()), my_end(my_v.begin());
//         for(size_t i = 0; i < 10; ++i)
//             v[i] = '0' + i;
// 		size_t i = 0;
// 		for(ft::vector<char>::iterator it = my_v.begin(); it != my_v.end(); ++it)
// 			*it = '0' + i++;
//         while (start != end)
//             res.push_back(*start++);
//         while (my_start != my_end)
//             my_res.push_back(*my_start++);
//         EQUAL(res == my_res);
//     }
//     std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
// }

void alarm_handler(int seg)
{
  (void)seg;
  std::cout << "\033[1;33mTLE\033[0m\n";
  kill(getpid(), SIGINT);
}

int main()
{
  std::cout << RED << "*------------------------ Testing the vector ------------------------*" << RESET << std::endl;
  sleep(1);
  signal(SIGALRM, alarm_handler);
  iterator_tests();
  const_iterator_tests();
  reverse_iterator_tests();

  return 0;
}