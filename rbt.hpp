/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/28 17:15:17 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "map.hpp"
#include "utils.hpp"

namespace ft
{
    template <class Key,
              class T>
    struct Node
    {
        typedef ft::pair<const Key, T> value_type;
        value_type *data;
        Node *parent;
        Node *left;
        Node *right;
        int color;
    };

    template <class Key,
              class T,
              class Alloc,
              class Compare>
    class RBT
    {
        typedef ft::pair<const Key, T> value_type;
        typedef ft::Node<Key, T> node_type;
        typedef Alloc allocator_type;
        typedef Compare key_compare;
        typedef typename Alloc::template rebind<ft::Node<Key, T> >::other allocator_other_type;

    private:
        node_type *_root;
        allocator_type _allocator;
        allocator_other_type _node_allocator;

        node_type *create_node(value_type val)
        {
            node_type *ptr;
            ptr = this->_node_allocator.allocate(1);
            ptr->color = 0;
            ptr->parent = nullptr;
            ptr->left = nullptr;
            ptr->right = nullptr;
            ptr->data = this->_allocator.allocate(1);
            ptr->data = &val;
            return ptr;
        }

    public:
        RBT() : _root(nullptr) {}

        void insert(value_type val)
        {
            if (!this->_root)
            {
                this->_root = this->create_node(val);
            }

            std::cout << this->_root->data->second << std::endl;

            // int a = 4;
            // int b = 3;
            // if (ft::my_compare(a, b, key_compare()) == 1)
            //     std::cout << "a < b \n";
            // else if (!ft::my_compare(a, b, key_compare()) && !ft::my_compare(b, a, key_compare()))
            //     std::cout << "a = b \n";
            // else if (ft::my_compare(a, b, key_compare()) == 0)
            //     std::cout << "a > b \n";
        }

        ~RBT() {}
    };
}