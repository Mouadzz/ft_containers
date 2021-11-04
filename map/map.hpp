/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:06:14 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 10:25:25 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <iostream>
#include "pair.hpp"
#include "rbt.hpp"

namespace ft
{
    template <class Key,                                            // map::key_type
              class T,                                              // map::mapped_type
              class Compare = std::less<Key>,                       // map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
              >
    class map
    {
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;

    private:
        ft::RBT<const Key, T, Alloc, Compare> tree;
        allocator_type _allocator;

    public:
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
        {
        }

        // template <class InputIterator>
        // map(InputIterator first, InputIterator last,
        //     const key_compare &comp = key_compare(),
        //     const allocator_type &alloc = allocator_type())
        //     {

        //     }

        void insert(const value_type &val)
        {
            tree.insert(val);
        }

        void remove(const key_type &k)
        {
            tree.remove(k);
        }

        void print_tree()
        {
            tree.print_tree();
        }
    };
}