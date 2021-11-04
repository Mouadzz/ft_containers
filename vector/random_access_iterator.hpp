/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:53:24 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 11:08:00 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
namespace ft
{
    template <class Category, class T, class Distance = ptrdiff_t,
              class Pointer = T *, class Reference = T &>
    struct iterator
    {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

    template <class T>
    class vector_iterator : public ft::iterator<std::random_access_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer pointer;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;

    private:
        pointer _it;

    public:
        vector_iterator() : _it(nullptr) {}

        vector_iterator(T *arr, size_t pos)
        {
            this->_it = &arr[pos];
        }

        vector_iterator(pointer it)
        {
            this->_it = it;
        }

        vector_iterator(vector_iterator const &copy)
        {
            *this = copy;
        }

        operator vector_iterator<const T>() const
        {
            return vector_iterator<const T>(this->_it);
        }

        vector_iterator &operator=(vector_iterator const &copy)
        {
            this->_it = copy._it;
            return *this;
        }

        T &operator*() const
        {
            return *this->_it;
        }

        pointer operator->()
        {
            return this->_it;
        }

        vector_iterator operator++(int)
        {
            vector_iterator tmp(*this);
            ++this->_it;
            return tmp;
        }

        vector_iterator &operator++()
        {
            ++this->_it;
            return *this;
        }

        vector_iterator operator--(int)
        {
            vector_iterator tmp(*this);
            --this->_it;
            return tmp;
        }

        vector_iterator &operator--()
        {
            --this->_it;
            return *this;
        }

        vector_iterator operator+(const size_t n)
        {
            vector_iterator tmp(*this);
            tmp._it += n;
            return tmp;
        }

        vector_iterator operator-(const size_t n) const
        {
            vector_iterator tmp(*this);
            tmp._it -= n;
            return tmp;
        }

        difference_type operator-(const vector_iterator &copy) const
        {
            return this->_it - copy._it;
        }

        friend bool operator==(const vector_iterator &lhs, const vector_iterator &rhs)
        {
            return (lhs._it == rhs._it);
        }

        friend bool operator!=(const vector_iterator &lhs, const vector_iterator &rhs)
        {
            return (lhs._it != rhs._it);
        }

        friend bool operator<(const vector_iterator &lhs, const vector_iterator &rhs)
        {
            return (lhs._it < rhs._it);
        }

        friend bool operator>(const vector_iterator &lhs, const vector_iterator &rhs)
        {
            return (lhs._it > rhs._it);
        }

        friend bool operator<=(const vector_iterator &lhs, const vector_iterator &rhs)
        {
            return (lhs._it <= rhs._it);
        }

        friend bool operator>=(const vector_iterator &lhs, const vector_iterator &rhs)
        {
            return (lhs._it >= rhs._it);
        }

        vector_iterator &operator+=(const size_t n)
        {
            *this = *this + n;
            return *this;
        }

        vector_iterator &operator-=(const size_t n)
        {
            *this = *this - n;
            return *this;
        }

        T &operator[](const size_t n) const
        {
            return this->_it[n];
        }
        ~vector_iterator() {}
    };

    template <class T>
    ft::vector_iterator<T> operator+(size_t n, const vector_iterator<T> &y)
    {
        vector_iterator<T> tmp(y);
        tmp += n;
        return tmp;
    }
}