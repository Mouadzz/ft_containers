/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:21 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/24 13:44:16 by mlasrite         ###   ########.fr       */
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
    class m_iterator : public ft::iterator<std::random_access_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer pointer;
        typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;

    private:
        pointer _it;

    public:
        m_iterator() : _it(nullptr) {}

        m_iterator(T *arr, size_t pos)
        {
            this->_it = &arr[pos];
        }

        m_iterator(pointer it)
        {
            this->_it = it;
        }

        m_iterator(m_iterator const &copy)
        {
            *this = copy;
        }

        operator m_iterator<const T>() const
        {
            return m_iterator<const T>(this->_it);
        }

        m_iterator &operator=(m_iterator const &copy)
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

        m_iterator operator++(int)
        {
            m_iterator tmp(*this);
            ++this->_it;
            return tmp;
        }

        m_iterator &operator++()
        {
            ++this->_it;
            return *this;
        }

        m_iterator operator--(int)
        {
            m_iterator tmp(*this);
            --this->_it;
            return tmp;
        }

        m_iterator &operator--()
        {
            --this->_it;
            return *this;
        }

        m_iterator operator+(const size_t n)
        {
            m_iterator tmp(*this);
            tmp._it += n;
            return tmp;
        }

        m_iterator operator-(const size_t n) const
        {
            m_iterator tmp(*this);
            tmp._it -= n;
            return tmp;
        }

        difference_type operator-(const m_iterator &copy) const
        {
            return this->_it - copy._it;
        }

        friend bool operator==(const m_iterator &lhs, const m_iterator &rhs)
        {
            return (lhs._it == rhs._it);
        }

        friend bool operator!=(const m_iterator &lhs, const m_iterator &rhs)
        {
            return (lhs._it != rhs._it);
        }

        friend bool operator<(const m_iterator &lhs, const m_iterator &rhs)
        {
            return (lhs._it < rhs._it);
        }

        friend bool operator>(const m_iterator &lhs, const m_iterator &rhs)
        {
            return (lhs._it > rhs._it);
        }

        friend bool operator<=(const m_iterator &lhs, const m_iterator &rhs)
        {
            return (lhs._it <= rhs._it);
        }

        friend bool operator>=(const m_iterator &lhs, const m_iterator &rhs)
        {
            return (lhs._it >= rhs._it);
        }

        m_iterator &operator+=(const size_t n)
        {
            *this = *this + n;
            return *this;
        }

        m_iterator &operator-=(const size_t n)
        {
            *this = *this - n;
            return *this;
        }

        T &operator[](const size_t n) const
        {
            return this->_it[n];
        }
        ~m_iterator() {}
    };

    template <class T>
    ft::m_iterator<T> operator+(size_t n, const m_iterator<T> &y)
    {
        m_iterator<T> tmp(y);
        tmp += n;
        return tmp;
    }
}