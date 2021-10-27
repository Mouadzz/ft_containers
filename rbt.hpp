/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/27 19:11:26 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

namespace ft
{
    template <class Key, class T>
    class RBT
    {
        typedef ft::pair<const Key, T> value_type;

    private:
        struct Node
        {
            value_type *data;
            Node *parent;
            Node *left;
            Node *right;
            int color;
        };
        Node *ptr;
        Node *root;

    public:
        RBT()
        {
            std::cout << "RBT Constructor\n";
            // ptr = new Node;
            // ptr->color = 0;
            // ptr->parent = nullptr;
            // ptr->left = nullptr;
            // ptr->right = nullptr;
            // root = ptr;
        }
        void insert(value_type val)
        {
            std::cout << "Key --> " << val.first << std::endl;
            std::cout << "Value --> " << val.second << std::endl;
        }

        ~RBT() {}
    };
}