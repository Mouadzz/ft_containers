/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/28 19:16:50 by mlasrite         ###   ########.fr       */
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
        size_t len;

        node_type *create_new_node(value_type val)
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

        void add_new_node(node_type *parent, node_type *new_node)
        {
            std::cout << new_node->data->first << " " << parent->data->first << std::endl;
            if (ft::my_compare(new_node->data->first, parent->data->first, key_compare()) == 0)
            {
                if (parent->right == nullptr)
                {
                    std::cout << "add new node to the right\n";
                    parent->right = new_node;
                    new_node->parent = parent;
                }
            }
        }

    public:
        RBT() {}
        ~RBT() {}

        void insert(value_type val)
        {
            if (!this->_root)
            {
                std::cout << "Tree is Empty -> make new node our root\n";
                this->_root = this->create_new_node(val);
                len++;
            }
            // else
            // {
            //     std::cout << "Tree is not Empty -> add new node as leaf\n";
            //     // node_type *new_node = this->create_new_node(val);

            //     // std::cout << new_node->data->first << std::endl;
            //     // add_new_node(this->_root, new_node);
            //     len++;
            // }
            std::cout << "root key --> " << this->_root->data->first << "len -->" << len << std::endl;
        }
    };
}

// if (ft::my_compare(a, b, key_compare()) == 1)
//     std::cout << "a < b \n";
// else if (!ft::my_compare(a, b, key_compare()) && !ft::my_compare(b, a, key_compare()))
//     std::cout << "a = b \n";
// else if (ft::my_compare(a, b, key_compare()) == 0)
//     std::cout << "a > b \n";