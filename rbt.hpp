/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/01 15:44:14 by mlasrite         ###   ########.fr       */
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
        typedef Key key_type;
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
            ptr->parent = NULL;
            ptr->left = NULL;
            ptr->right = NULL;
            ptr->data = this->_allocator.allocate(1);
            this->_allocator.construct(ptr->data, val);
            return ptr;
        }

        void right_left_rotate(node_type *node)
        {
            right_rotate(node->right);
            left_rotate(node);
        }

        void left_right_rotate(node_type *node)
        {
            left_rotate(node->left);
            right_rotate(node);
        }

        void right_rotate(node_type *node)
        {

            node_type *tmp = node->left;
            node->left = tmp->right;

            if (node->left)
            {
                node->left->parent = node;
                node->left->isleft = 1;
            }

            if (node->parent == NULL)
            {
                // we are the root node
                this->_root = tmp;
                tmp->parent = NULL;
            }
            else
            {
                tmp->parent = node->parent;
                if (node->isleft)
                {
                    tmp->isleft = 1;
                    tmp->parent->left = tmp;
                }
                else
                {
                    tmp->isleft = 0;
                    tmp->parent->right = tmp;
                }
            }
            tmp->right = node;
            node->isleft = 0;
            node->parent = tmp;
        }

        void left_rotate(node_type *node)
        {
            node_type *tmp = node->right;
            node->right = tmp->left;

            if (node->right)
            {
                node->right->parent = node;
                node->right->isleft = 0;
            }

            if (node->parent == NULL)
            {
                // we are the root node
                this->_root = tmp;
                tmp->parent = NULL;
            }
            else
            {
                tmp->parent = node->parent;
                if (node->isleft)
                {
                    tmp->isleft = 1;
                    tmp->parent->left = tmp;
                }
                else
                {
                    tmp->isleft = 0;
                    tmp->parent->right = tmp;
                }
            }
            tmp->left = node;
            node->isleft = 1;
            node->parent = tmp;
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
                    if (node->right)
                        node->right->color = 1;
                    if (node->left)
                        node->left->color = 1;
                }
            }
            else
            {
                if (!node->parent->isleft)
                {
                    left_rotate(node->parent->parent);
                    node->color = 1;
                    node->parent->color = 0;
                    if (node->parent->left)
                        node->parent->left->color = 1;
                }
                else
                {
                    left_right_rotate(node->parent->parent);
                    node->color = 0;
                    if (node->right)
                        node->right->color = 1;
                    if (node->left)
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
                if (node->parent->parent && (node->parent->parent->right == NULL || node->parent->parent->right->color == 0))
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
                if (node->parent->parent && (node->parent->parent->left == NULL || node->parent->parent->left->color == 0))
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
            if (node != this->_root && node != NULL)
            {
                // if we have two consecutive red nodes
                if (node->color == 1 && (node->parent && node->parent->color == 1))
                {
                    correct_tree(node);
                }

                // recursive till we reach our route
                check_color(node->parent);
            }
        }

        void add_new_node(node_type *parent, node_type *new_node)
        {
            // if the new node key is greater than the parent's node key
            if (ft::my_compare(new_node->data->first, parent->data->first, key_compare()) == 0 && !(!ft::my_compare(new_node->data->first, parent->data->first, key_compare()) && !ft::my_compare(parent->data->first, new_node->data->first, key_compare())))
            {
                // if right child exist
                if (parent->right == NULL)
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
                if (parent->left == NULL)
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
            check_color(new_node);
        }

        void print_helper(const std::string &prefix, const node_type *node, bool isLeft)
        {
            if (node != NULL)
            {
                std::cout << prefix;

                std::cout << (isLeft ? "├──" : "└──");

                // print the value of the node
                std::cout << node->data->first << " ";

                if (node == this->_root)
                    std::cout << "(Root)" << std::endl;
                else
                    std::cout << (isLeft ? "(R)" : "(L)") << std::endl;
                // enter the next tree level - left and right branch
                print_helper(prefix + (isLeft ? "│   " : "    "), node->right, true);
                print_helper(prefix + (isLeft ? "│   " : "    "), node->left, false);
            }
        }

        node_type *search_node_helper(node_type *node, const key_type &k)
        {
            if (node == NULL)
                return NULL;

            if (!ft::my_compare(k, node->data->first, key_compare()) && !ft::my_compare(node->data->first, k, key_compare()))
                return node;
            else if (ft::my_compare(k, node->data->first, key_compare()) == 1)
                return search_node_helper(node->left, k);
            else
                return search_node_helper(node->right, k);
        }

        node_type *get_successor(node_type *node)
        {
            node_type *current = node;

            // loop to find the leftmost leaf
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        node_type *get_predecessor(node_type *node)
        {
            node_type *current = node;

            // loop to find the rightmost leaf
            while (current->right != NULL)
                current = current->right;
            return current;
        }

        void free_node(node_type *node)
        {
            if (node->isleft == 1)
                node->parent->left = NULL;
            else
                node->parent->right = NULL;
            this->_allocator.destroy(node->data);
            this->_allocator.deallocate(node->data, 1);
            node->left = NULL;
            node->parent = NULL;
            node->parent = NULL;
            this->_node_allocator.destroy(node);
            this->_node_allocator.deallocate(node, 1);
        }

        void remove_helper(node_type *node)
        {
            if (node->left == NULL && node->right == NULL)
            {
                if (node->color == 0)
                {
                    std::cout << "node is black -> check all cases\n";
                }
                else
                {
                    std::cout << "node is red -> delete node and free\n";
                    free_node(node);
                }
            }
            else
            {
                node_type *ret;
                if (node->right != NULL)
                {
                    // smalest key in right subtree
                    ret = get_successor(node->right);
                    std::cout << "successor -> " << ret->data->first << std::endl;

                    // replace our node pair
                    this->_allocator.destroy(node->data);
                    this->_allocator.construct(node->data, *ret->data);

                    // recursion
                    remove_helper(ret);
                }
                else
                {
                    // largest key in left subtree
                    ret = get_predecessor(node->left);
                    std::cout << "predecessor -> " << ret->data->first << std::endl;

                    // replace our node pair
                    this->_allocator.destroy(node->data);
                    this->_allocator.construct(node->data, *ret->data);

                    // recursion
                    remove_helper(ret);
                }
            }
        }

    public:
        RBT() : _root(NULL) {}
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

        void remove(const key_type &k)
        {
            std::cout << "removing -> " << k << std::endl;
            node_type *node = search_node(k);
            if (node != NULL)
                remove_helper(node);
        }

        node_type *search_node(const key_type &k)
        {
            return search_node_helper(this->_root, k);
        }

        void print_tree()
        {
            std::cout << '\n';
            print_helper("", this->_root, false);
        }
    };
}