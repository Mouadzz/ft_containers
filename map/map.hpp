/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:06:14 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 13:23:47 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <iostream>
#include "pair.hpp"
#include "rbt.hpp"
#include "bidirectional_iterator.hpp"

namespace ft
{
    template <class Key,                                            // map::key_type
              class T,                                              // map::mapped_type
              class Compare = std::less<Key>,                       // map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
              >
    class map
    {
        /*----------------[ MEMBER TYPES ]----------------*/

        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef ft::map_iterator<const Key, T> iterator;
        typedef ft::map_iterator<const Key, const T> const_iterator;
        typedef size_t size_type;

        /*----------------[ END OF MEMBER TYPES ]----------------*/

    private:
        ft::RBT<const Key, T, Alloc, Compare> tree;
        allocator_type _allocator;

    public:
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
        {
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
        {
        }

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

        /*----------------[ ITERATOR FUNCTIONS ]----------------*/

        // Returns an iterator referring to the first element in the map container.
        iterator begin()
        {
            iterator it(tree.leftmost());
            return it;
        }

        const_iterator begin() const
        {
            const_iterator it(tree.leftmost());
            return it;
        }

        // Returns an iterator referring to the past-the-end element in the map container.
        iterator end()
        {
            iterator it(tree.rightmost()->right);
            return it;
        }

        const_iterator end() const
        {
            const_iterator it(tree.rightmost()->right);
            return it;
        }

        /*----------------[ END OF ITERATOR FUNCTIONS ]----------------*/
    };
}