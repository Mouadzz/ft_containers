/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/27 16:47:53 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
    class RBT
    {
    private:
        struct Node
        {
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
        void insert()
        {
            std::cout << "New node inseterted! \n";
        }

        ~RBT() {}
    };
}