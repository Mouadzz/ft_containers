/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:52:45 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 12:16:11 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../vector/random_access_iterator.hpp"
#include "rbt.hpp"
#include "pair.hpp"

namespace ft
{
    template <class Key, class T>
    class map_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
    {
        typedef ft::Node<Key, T> node_type;
        typedef ft::pair<const Key, T> value_type;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer pointer;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type difference_type;

    private:
        node_type *_node;
        node_type *_before_end;

        node_type *get_successor(node_type *node)
        {
            if (!node)
                return NULL;
            node_type *current = node;

            // loop to find the leftmost leaf
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        node_type *get_predecessor(node_type *node)
        {
            if (!node)
                return NULL;
            node_type *current = node;

            // loop to find the rightmost leaf
            while (current->right != NULL)
                current = current->right;
            return current;
        }

    public:
        map_iterator() : _node(NULL) {}

        map_iterator(node_type *node)
        {
            this->_node = node;
        }

        map_iterator(node_type *before, node_type *end)
        {
            this->_node = end;
            this->_before_end = before;
        }

        map_iterator(map_iterator const &copy)
        {
            *this = copy;
        }

        map_iterator &operator=(map_iterator const &copy)
        {
            this->_node = copy._node;
            return *this;
        }

        friend bool operator==(const map_iterator &lhs, const map_iterator &rhs)
        {
            return (lhs._node == rhs._node);
        }

        friend bool operator!=(const map_iterator &lhs, const map_iterator &rhs)
        {
            return (lhs._node != rhs._node);
        }

        value_type &operator*() const
        {
            return *this->_node->data;
        }

        value_type *operator->()
        {
            return this->_node->data;
        }

        map_iterator operator++(int)
        {
            map_iterator tmp(*this);
            node_type *ret = NULL;
            if (this->_node)
                ret = get_successor(this->_node->right);
            if (ret)
                this->_node = ret;
            else if (this->_node)
            {
                if (this->_node->isleft)
                    this->_node = this->_node->parent;
                else
                {
                    while (this->_node && !this->_node->isleft)
                        this->_node = this->_node->parent;
                    if (this->_node)
                        this->_node = this->_node->parent;
                }
            }
            return tmp;
        }

        map_iterator &operator++()
        {
            node_type *ret = NULL;
            if (this->_node)
                ret = get_successor(this->_node->right);
            if (ret)
                this->_node = ret;
            else if (this->_node)
            {
                if (this->_node->isleft)
                    this->_node = this->_node->parent;
                else
                {
                    while (this->_node && !this->_node->isleft)
                        this->_node = this->_node->parent;
                    if (this->_node)
                        this->_node = this->_node->parent;
                }
            }
            return *this;
        }

        map_iterator operator--(int)
        {
            map_iterator tmp(*this);
            node_type *ret = NULL;
            if (this->_node)
                ret = get_predecessor(this->_node->left);
            if (ret)
                this->_node = ret;
            else
            {
                if (this->_node && this->_node->isleft)
                {
                    while (this->_node && this->_node->isleft)
                        this->_node = this->_node->parent;
                    if (this->_node)
                        this->_node = this->_node->parent;
                }
                else
                {
                    if (this->_node && this->_node->parent)
                        this->_node = this->_node->parent;
                    else
                        this->_node = this->_before_end;
                }
            }
            return tmp;
        }

        map_iterator &operator--()
        {
            node_type *ret = NULL;
            if (this->_node)
                ret = get_predecessor(this->_node->left);
            if (ret)
                this->_node = ret;
            else
            {
                if (this->_node && this->_node->isleft)
                {
                    while (this->_node && this->_node->isleft)
                        this->_node = this->_node->parent;
                    if (this->_node)
                        this->_node = this->_node->parent;
                }
                else
                {
                    if (this->_node && this->_node->parent)
                        this->_node = this->_node->parent;
                    else
                        this->_node = this->_before_end;
                }
            }
            return *this;
        }

        ~map_iterator() {}
    };
}
