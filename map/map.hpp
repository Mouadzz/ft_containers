/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:06:14 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 13:28:37 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <iostream>
#include "pair.hpp"
#include "rbt.hpp"
#include <math.h>
#include "bidirectional_iterator.hpp"
#include "../utils/reverse_iterator.hpp"

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
        typedef ft::map_iterator<value_type> iterator;
        typedef ft::map_iterator<value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
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
        ft::RBT<value_type, Key, T, Alloc, Compare>
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
            *this = x;
        }

        map &operator=(const map &x)
        {
            tree.clean_tree();

            if (x.size() > 0)
            {
                iterator begin(x.tree.leftmost());
                iterator end(x.tree.rightmost(), x.tree.rightmost()->right);
                while (begin != end)
                {
                    tree.insert(*begin);
                    begin++;
                }
            }
            return *this;
        }

        // Destroys the container object.
        ~map()
        {
            tree.clean_tree();
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

        //Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
        reverse_iterator rbegin()
        {
            return reverse_iterator(this->end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(this->end());
        }

        // Returns a reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).

        reverse_iterator rend()
        {
            return reverse_iterator(this->begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(this->begin());
        }

        /*----------------[ END OF ITERATOR FUNCTIONS ]----------------*/

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

        /*----------------[ CAPACITY FUNCTIONS ]----------------*/

        // Returns the number of elements in the map container.
        size_type size() const
        {
            return tree.get_size();
        }

        bool empty() const
        {
            return (tree.get_size() == 0) ? true : false;
        }

        size_type max_size() const
        {
            size_t maxvalue = std::numeric_limits<size_t>::max();
            size_type res = maxvalue / sizeof(mapped_type);
            return res / 10;
        }

        /*----------------[ END OF CAPACITY FUNCTIONS ]----------------*/
    };
}