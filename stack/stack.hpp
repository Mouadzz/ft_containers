/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:59:33 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 10:48:52 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../vector/vector.hpp"

namespace ft
{

    template <class T, class Container = ft::Vector<T> >
    class Stack
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

    public:
        explicit Stack(const container_type &ctnr = container_type()) : _container(ctnr) {}

        bool empty() const { return this->_container.empty(); }
        size_type size() const { return this->_container.size(); }

        value_type &top() { return this->_container.back(); }
        const value_type &top() const { return this->_container.back(); }

        void push(const value_type &val) { this->_container.push_back(val); }

        void pop() { this->_container.pop_back(); }

        friend bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
        {
            return (lhs._container == rhs._container);
        }
        friend bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
        {
            return (lhs._container != rhs._container);
        }
        friend bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
        {
            return (lhs._container < rhs._container);
        }
        friend bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
        {
            return (lhs._container <= rhs._container);
        }
        friend bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
        {
            return (lhs._container > rhs._container);
        }
        friend bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
        {
            return (lhs._container >= rhs._container);
        }

    protected:
        container_type _container;
    };
}