/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:06:14 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 12:02:14 by mlasrite         ###   ########.fr       */
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
    public:
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

        class value_compare : public std::binary_function<value_type, value_type, bool>
        { // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class map;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        /*----------------[ END OF MEMBER TYPES ]----------------*/

    private:
        ft::RBT<const Key, T, Alloc, Compare>
            tree;
        allocator_type _allocator;

    public:
        /*----------------[ CONSTRUCTORS ]----------------*/

        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
        {
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
        {
            while (first != last)
            {
                tree.insert(*first);
                first++;
            }
        }

        map(const map &x)
        {
            tree.clean_tree();
            iterator begin(x.tree.leftmost());
            iterator end(x.tree.rightmost(), x.tree.rightmost()->right);
            while (begin != end)
            {
                tree.insert(*begin);
                begin++;
            }
        }

        // Destroys the container object.
        ~map()
        {
            tree.clean_tree();
        }

        /*----------------[ END OF CONSTRUCTORS ]----------------*/

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
            iterator it(tree.rightmost(), tree.rightmost()->right);
            return it;
        }

        const_iterator end() const
        {
            const_iterator it(tree.rightmost(), tree.rightmost()->right);
            return it;
        }

        /*----------------[ END OF ITERATOR FUNCTIONS ]----------------*/
    };
}