/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:38:20 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/05 16:39:16 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
namespace ft
{
    template <class Pair>
    struct Node
    {
        typedef Pair value_type;
        value_type *data;
        Node *parent;
        Node *left;
        Node *right;
        int isleft;
        int color;
        int isdb;
    };
}