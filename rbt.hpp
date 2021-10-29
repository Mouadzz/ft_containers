/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/29 17:01:52 by mlasrite         ###   ########.fr       */
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
        int isleft;
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

        node_type *create_new_node(const value_type &val)
        {
            node_type *ptr;
            ptr = this->_node_allocator.allocate(1);
            ptr->color = 0;
            ptr->isleft = 1;
            ptr->parent = nullptr;
            ptr->left = nullptr;
            ptr->right = nullptr;
            ptr->data = this->_allocator.allocate(1);
            this->_allocator.construct(ptr->data, val);
            return ptr;
        }

        void rotate(node_type *node)
        {
        }

        void correct_tree(node_type *node)
        {
            if (node->parent->isleft)
            {
                if (node->parent->parent && (node->parent->parent->right == nullptr || node->parent->parent->right == 0))
                    return rotate(node);
                else if (node->parent->parent)
                {
                    if (node->parent->parent->right)
                        node->parent->parent->right->color = 0;
                    node->parent->parent->color = 1;
                    node->parent->color = 0;
                }
            }
            else
            {
                if (node->parent->parent && (node->parent->parent->left == nullptr || node->parent->parent->left == 0))
                    return rotate(node);
                else if (node->parent->parent)
                {
                    if (node->parent->parent->left)
                        node->parent->parent->left->color = 0;
                    node->parent->parent->color = 1;
                    node->parent->color = 0;
                }
            }
        }

        void check_color(node_type *node)
        {
            if (node != this->_root)
            {
                if (node->color == 1 && node->parent->color == 1)
                    correct_tree(node);
                check_color(node->parent);
            }
        }

        void add_new_node(node_type *parent, node_type *new_node)
        {
            if (ft::my_compare(new_node->data->first, parent->data->first, key_compare()) == 0 &&
                !(!ft::my_compare(new_node->data->first, parent->data->first, key_compare()) &&
                  !ft::my_compare(parent->data->first, new_node->data->first, key_compare())))
            {
                if (parent->right == nullptr)
                {
                    parent->right = new_node;
                    new_node->parent = parent;
                    new_node->isleft = 0;
                }
                else
                    return add_new_node(parent->right, new_node);
            }
            else if (ft::my_compare(new_node->data->first, parent->data->first, key_compare()) == 1)
            {
                if (parent->left == nullptr)
                {
                    parent->left = new_node;
                    new_node->parent = parent;
                    new_node->isleft = 1;
                }
                else
                    return add_new_node(parent->left, new_node);
            }
        }

        void print_helper(const std::string &prefix, const node_type *node, bool isLeft)
        {
            if (node != nullptr)
            {
                std::cout << prefix;

                std::cout << (isLeft ? "├──" : "└──");

                // print the value of the node
                std::cout << node->data->first << " ";
                std::cout << (isLeft ? "(L)" : "(R)") << std::endl;
                // enter the next tree level - left and right branch
                print_helper(prefix + (isLeft ? "│   " : "    "), node->left, true);
                print_helper(prefix + (isLeft ? "│   " : "    "), node->right, false);
            }
        }

    public:
        RBT() {}
        ~RBT() {}

        void insert(const value_type &val)
        {
            if (!this->_root)
            {
                std::cout << "Tree is Empty -> make new node our root\n";
                this->_root = this->create_new_node(val);
                len++;
            }
            else
            {
                std::cout << "Tree is not Empty -> add new node as leaf\n";
                node_type *new_node = this->create_new_node(val);
                new_node->color = 1;
                add_new_node(this->_root, new_node);
                len++;
            }
        }

        void print_tree()
        {
            std::cout << '\n';
            print_helper("", this->_root, false);
        }
    };
}