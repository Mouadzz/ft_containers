/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:21 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/21 12:02:02 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

        m_iterator(const m_iterator &copy)
        {
            *this = copy;
        }

        operator m_iterator<const T>() const
        {
            return m_iterator<const T>(this->_it);
        }

        m_iterator &operator=(const m_iterator &copy)
        {
            this->_it = copy._it;
            return *this;
        }

        bool operator==(const m_iterator &copy)
        {
            return (this->_it == copy._it);
        }

        bool operator!=(const m_iterator &copy)
        {
            return (this->_it != copy._it);
        }

        T &operator*()
        {
            return *this->_it;
        }

        pointer operator->()
        {
            return this->_it;
        }

        T &operator=(T &value)
        {
            this->*_it = value;
            return this->*_it;
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

        m_iterator operator+(const T &n)
        {
            m_iterator tmp(*this);
            tmp._it += n;
            return tmp;
        }

        m_iterator operator-(const T &n)
        {
            m_iterator tmp(*this);
            tmp._it -= n;
            return tmp;
        }

        difference_type operator-(m_iterator &copy)
        {
            return this->_it - copy._it;
        }

        bool operator<(const m_iterator &copy)
        {
            return (this->_it < copy._it);
        }

        bool operator>(const m_iterator &copy)
        {
            return (this->_it > copy._it);
        }

        bool operator<=(const m_iterator &copy)
        {
            return (this->_it <= copy._it);
        }

        bool operator>=(const m_iterator &copy)
        {
            return (this->_it >= copy._it);
        }

        m_iterator &operator+=(const T &n)
        {
            *this = *this + n;
            return *this;
        }

        m_iterator &operator-=(const T &n)
        {
            *this = *this - n;
            return *this;
        }

        T &operator[](const T &n)
        {
            return this->_it[n];
        }

        ~m_iterator() {}
    };

    template <class T>
    ft::m_iterator<T> operator+(const T &n, const m_iterator<T> &y)
    {
        m_iterator<T> tmp(y);
        tmp += n;
        return tmp;
    }
}