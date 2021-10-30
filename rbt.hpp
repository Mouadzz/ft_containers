/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/30 13:25:39 by mlasrite         ###   ########.fr       */
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

        void right_rotate(node_type *node)
        {
        }

        void right_left_rotate(node_type *node)
        {
        }

        void left_rotate(node_type *node)
        {
        }

        void left_right_rotate(node_type *node)
        {
        }

        void rotate(node_type *node)
        {
            if (node->isleft)
            {
                if (node->parent->isleft)
                {
                    right_rotate(node->parent->parent);
                    node->color = 1;
                    node->parent->color = 0;
                    if (node->parent->right)
                        node->parent->right->color = 1;
                }
                else
                {
                    right_left_rotate(node->parent->parent);
                    node->color = 0;
                    node->right->color = 1;
                    node->left->color = 1;
                }
            }
            else
            {
                if (node->parent->isleft)
                {
                    left_rotate(node->parent->parent);
                    node->color = 1;
                    node->parent->color = 0;
                    if (node->parent->right)
                        node->parent->right->color = 1;
                }
                else
                {
                    left_right_rotate(node->parent->parent);
                    node->color = 0;
                    node->right->color = 1;
                    node->left->color = 1;
                }
            }
        }

        void correct_tree(node_type *node)
        {
            // if node parent is left child
            if (node->parent->isleft)
            {
                // if our aunt is black or null then we rotate | rotation -> node->parent->parent black and its both childs red
                if (node->parent->parent && (node->parent->parent->right == nullptr || node->parent->parent->right == 0))
                    rotate(node);
                // if aunt is red then we color flip | flip color -> node->parent->parent red and its both childs black
                else if (node->parent->parent)
                {
                    if (node->parent->parent->right)
                        node->parent->parent->right->color = 0;
                    node->parent->parent->color = 1;
                    node->parent->color = 0;
                }
            }
            // if node parent is right child
            else
            {
                // if our aunt is black or null then we rotate | rotation -> node->parent->parent black and its both childs red
                if (node->parent->parent && (node->parent->parent->left == nullptr || node->parent->parent->left == 0))
                    return rotate(node);
                // if aunt is red then we color flip | flip color -> node->parent->parent red and its both childs black
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
            // stop our recursive when we reach our route
            if (node != this->_root)
            {
                // if we have two consecutive red nodes
                if (node->color == 1 && node->parent->color == 1)
                    correct_tree(node);

                // recursive till we reach our route
                check_color(node->parent);
            }
        }

        void add_new_node(node_type *parent, node_type *new_node)
        {
            // if the new node key is greater than the parent's node key
            if (ft::my_compare(new_node->data->first, parent->data->first, key_compare()) == 0 &&
                !(!ft::my_compare(new_node->data->first, parent->data->first, key_compare()) &&
                  !ft::my_compare(parent->data->first, new_node->data->first, key_compare())))
            {
                // if right child exist
                if (parent->right == nullptr)
                {
                    // add our new node as a right child
                    parent->right = new_node;
                    new_node->parent = parent;

                    // new node is right child
                    new_node->isleft = 0;
                }
                else
                    // if parent's child exists then we add it to our parent's right child
                    return add_new_node(parent->right, new_node);
            }
            // if the new node key is lesser than the parent's node key
            else if (ft::my_compare(new_node->data->first, parent->data->first, key_compare()) == 1)
            {
                // if left child exist
                if (parent->left == nullptr)
                {
                    // add our new node as a left child
                    parent->left = new_node;
                    new_node->parent = parent;

                    // new node is left child
                    new_node->isleft = 1;
                }
                else
                    // if parent's child exists then we add it to our parent's left child
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
            // check if tree is empty
            if (!this->_root)
            {
                // create new node and make it our route
                this->_root = this->create_new_node(val);
                len++;
            }
            else
            {
                // create new node
                node_type *new_node = this->create_new_node(val);

                // all new nodes added are red
                new_node->color = 1;

                // add the new node as a leaf
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