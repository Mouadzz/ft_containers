/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:06:14 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/06 18:21:44 by mlasrite         ###   ########.fr       */
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
    template <class Key,                                            // Map::key_type
              class T,                                              // Map::mapped_type
              class Compare = std::less<Key>,                       // Map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> > // Map::allocator_type
              >
    class Map
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

        typedef class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class Map;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        } value_compare;

        /*----------------[ END OF MEMBER TYPES ]----------------*/

    private:
        ft::RBT<value_type, Key, T, Alloc, Compare> _tree;
        allocator_type _allocator;
        key_compare _kcomp;

    public:
        /*----------------[ CONSTRUCTORS ]----------------*/

        explicit Map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
        {
            this->_kcomp = comp;
            this->_allocator = alloc;
        }

        template <class InputIterator>
        Map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
        {
            this->_kcomp = comp;
            this->_allocator = alloc;
            while (first != last)
            {
                _tree.help_insert(*first);
                first++;
            }
        }

        Map(const Map &x)
        {
            *this = x;
        }

        Map &operator=(const Map &x)
        {
            _tree.clean_tree();

            if (x.size() > 0)
            {
                iterator begin(x._tree.leftmost());
                iterator end(x._tree.rightmost(), x._tree.rightmost()->right);
                while (begin != end)
                {
                    _tree.help_insert(*begin);
                    begin++;
                }
            }
            return *this;
        }

        // Destroys the container object.
        ~Map()
        {
            _tree.clean_tree();
        }
        /*----------------[ END OF CONSTRUCTORS ]----------------*/

        /*----------------[ ITERATOR FUNCTIONS ]----------------*/

        // Returns an iterator referring to the first element in the Map container.
        iterator begin()
        {
            iterator it(_tree.leftmost());
            return it;
        }

        const_iterator begin() const
        {
            const_iterator it(_tree.leftmost());
            return it;
        }

        // Returns an iterator referring to the past-the-end element in the Map container.
        iterator end()
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *ret = _tree.rightmost();
            iterator it(ret, (ret != NULL) ? ret->right : ret);
            return it;
        }

        const_iterator end() const
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *ret = _tree.rightmost();
            const_iterator it(ret, (ret != NULL) ? ret->right : ret);
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

        // Returns a reverse iterator pointing to the theoretical element right before the first element in the Map container (which is considered its reverse end).
        reverse_iterator rend()
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *ret = _tree.leftmost();
            iterator it(ret, ret, true);
            return reverse_iterator(it);
        }

        const_reverse_iterator rend() const
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *ret = _tree.leftmost();
            const_iterator it(ret, ret, true);
            return const_reverse_iterator(it);
        }

        /*----------------[ END OF ITERATOR FUNCTIONS ]----------------*/

        /*----------------[ CAPACITY FUNCTIONS ]----------------*/

        // Returns the number of elements in the Map container.
        size_type size() const
        {
            return _tree.get_size();
        }

        bool empty() const
        {
            return (_tree.get_size() == 0) ? true : false;
        }

        size_type max_size() const
        {
            size_t maxvalue = std::numeric_limits<size_t>::max();
            size_type res = maxvalue / sizeof(mapped_type);
            return res / 10;
        }

        /*----------------[ END OF CAPACITY FUNCTIONS ]----------------*/

        /*----------------[ ELEMENT ACCESS ]----------------*/

        // If k matches the key of an element in the container, the function returns a reference to its mapped value.
        mapped_type &operator[](const key_type &k)
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *ret = _tree.search_node(k);
            if (ret)
                return ret->data->second;
            else
                return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
        }

        /*----------------[ END OF ELEMENT ACCESS ]----------------*/

        /*----------------[ MODIFIERS ]----------------*/

        ft::pair<iterator, bool> insert(const value_type &val)
        {
            return (_tree.insert(val));
        }

        iterator insert(iterator position, const value_type &val)
        {
            ft::pair<iterator, bool> ret = this->insert(val);
            return ret.first;
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                _tree.help_insert(*first);
                first++;
            }
        }

        void erase(iterator position)
        {
            this->_tree.remove(position->first);
        }

        size_type erase(const key_type &k)
        {
            this->_tree.remove(k);
            return 1;
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                this->_tree.remove(first->first);
                first++;
            }
        }

        void swap(Map &x)
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;

            node_type *tmp = x._tree.get_root();
            x._tree.set_root(this->_tree.get_root());
            this->_tree.set_root(tmp);
        }

        void clear()
        {
            _tree.clean_tree();
        }
        /*----------------[ END OF  MODIFIERS ]----------------*/

        /*----------------[ OBSERVERS ]----------------*/

        key_compare key_comp() const
        {
            return this->_kcomp;
        }

        value_compare value_comp() const
        {
            return value_compare(this->_kcomp);
        }

        /*----------------[ END OF OBSERVERS ]----------------*/

        /*----------------[ OPERATIONS ]----------------*/

        iterator find(const key_type &k)
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;

            node_type *ret = _tree.search_node(k);
            iterator tmp(ret);
            return tmp;
        }
        const_iterator find(const key_type &k) const
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;

            node_type *ret = _tree.search_node(k);
            const_iterator tmp(ret);
            return tmp;
        }

        size_type count(const key_type &k) const
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *ret = _tree.search_node(k);
            if (ret)
                return 1;
            else
                return 0;
        }

        iterator lower_bound(const key_type &k)
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *save;
            node_type *ret = this->_tree.lower_bound(k, &save);
            if (ret)
            {
                iterator tmp(ret);
                return tmp;
            }
            if (save)
            {
                iterator tmp(save);
                return tmp;
            }
            iterator tmp(save);
            return tmp;
        }

        const_iterator lower_bound(const key_type &k) const
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *save;
            node_type *ret = this->_tree.lower_bound(k, &save);
            if (ret)
            {
                const_iterator tmp(ret);
                return tmp;
            }
            if (save)
            {
                const_iterator tmp(save);
                return tmp;
            }
            const_iterator tmp(save);
            return tmp;
        }

        iterator upper_bound(const key_type &k)
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *save;
            node_type *ret = this->_tree.lower_bound(k, &save);
            if (ret)
            {
                iterator tmp(ret);
                tmp++;
                return tmp;
            }
            return this->end();
        }

        const_iterator upper_bound(const key_type &k) const
        {
            typedef typename ft::RBT<value_type, Key, T, Alloc, Compare>::node_type node_type;
            node_type *save;
            node_type *ret = this->_tree.lower_bound(k, &save);
            if (ret)
            {
                const_iterator tmp(ret);
                tmp++;
                return tmp;
            }
            return this->end();
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            ft::pair<const_iterator, const_iterator> ret;

            ret.first = lower_bound(k);
            ret.second = upper_bound(k);
            return ret;
        }

        ft::pair<iterator, iterator> equal_range(const key_type &k)
        {
            ft::pair<iterator, iterator> ret;

            ret.first = lower_bound(k);
            ret.second = upper_bound(k);
            return ret;
        }

        /*----------------[ END OF OPERATIONS ]----------------*/

        /*----------------[ ALLOCATOR ]----------------*/

        // Returns a copy of the allocator object associated with the Vector.
        allocator_type get_allocator() const
        {
            return this->_allocator;
        }

        /*----------------[ END OF ALLOCATOR ]----------------*/
    };

    template <class Key, class T, class Compare, class Alloc>
    void swap(Map<Key, T, Compare, Alloc> &x, Map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const Map<Key, T, Compare, Alloc> &lhs,
                    const Map<Key, T, Compare, Alloc> &rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const Map<Key, T, Compare, Alloc> &lhs,
                    const Map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const Map<Key, T, Compare, Alloc> &lhs,
                   const Map<Key, T, Compare, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const Map<Key, T, Compare, Alloc> &lhs,
                    const Map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs > rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const Map<Key, T, Compare, Alloc> &lhs,
                   const Map<Key, T, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const Map<Key, T, Compare, Alloc> &lhs,
                    const Map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }
}