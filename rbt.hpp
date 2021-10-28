/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/28 12:04:50 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "map.hpp"

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
              class Alloc>
    class RBT
    {
        typedef ft::pair<const Key, T> value_type;
        typedef Alloc allocator_type;
        typedef typename Alloc::template rebind<ft::Node<Key, T> >::other allocator_other_type;

    private:
        ft::Node<Key, T> *_root;
        allocator_type _allocator;
        allocator_other_type _node_allocator;

    public:
        RBT() : _root(nullptr) {}

        void insert(value_type val)
        {
            std::cout << "Inserting New Node... " << std::endl;

            // if empty tree
            if (!this->_root)
            {
                // allocate new root;
                this->_root = this->_node_allocator.allocate(1);

                // initialize root
                this->_root->color = 0;
                this->_root->parent = nullptr;
                this->_root->left = nullptr;
                this->_root->right = nullptr;

                // allocate new pair and assign val to it
                this->_root->data = this->_allocator.allocate(1);
                this->_root->data = &val;
            }

            std::cout << this->_root->data->first << std::endl;
        }

        ~RBT() {}
    };
}