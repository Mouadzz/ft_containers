/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:52:45 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/06 17:35:47 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../vector/random_access_iterator.hpp"
#include "pair.hpp"
#include "node.hpp"

namespace ft
{
    template <class Pair>
    class map_iterator : public ft::iterator<std::bidirectional_iterator_tag, Pair>
    {
    public:
        typedef ft::Node<Pair> node_type;
        typedef Pair value_type;
        typedef Pair *pointer;

    private:
        node_type *_node;
        node_type *_before_end;
        node_type *_before_rend;

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
        map_iterator() : _node(NULL), _before_end(NULL), _before_rend(NULL) {}

        map_iterator(node_type *node)
        {
            this->_node = node;
            this->_before_end = NULL;
            this->_before_rend = NULL;
        }

        map_iterator(node_type *begin, node_type *before, bool diff)
        {
            if (diff)
            {
                this->_node = begin;
                this->_before_rend = before;
                this->_before_end = NULL;
            }
        }

        map_iterator(node_type *before, node_type *end)
        {
            this->_node = end;
            this->_before_end = before;
            this->_before_rend = NULL;
        }

        map_iterator(map_iterator const &copy)
        {
            *this = copy;
        }

        map_iterator &operator=(map_iterator const &copy)
        {
            this->_node = copy._node;
            this->_before_end = copy._before_end;
            this->_before_rend = copy._before_rend;
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

        pointer operator->() const
        {
            return this->_node->data;
        }

        map_iterator operator++(int)
        {
            map_iterator tmp(*this);
            node_type *ret = NULL;
            if (this->_before_rend)
            {
                this->_node = this->_before_rend;
                this->_before_rend = NULL;
                return tmp;
            }
            if (this->_node)
                ret = get_successor(this->_node->right);
            if (ret)
                this->_node = ret;
            else if (this->_node)
            {
                if (this->_node && this->_node->isleft)
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
            if (this->_before_rend)
            {
                this->_node = this->_before_rend;
                this->_before_rend = NULL;
                return *this;
            }
            if (this->_node)
                ret = get_successor(this->_node->right);
            if (ret)
                this->_node = ret;
            else if (this->_node)
            {
                if (this->_node && this->_node->isleft)
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
