/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:21 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/05 15:02:33 by mlasrite         ###   ########.fr       */
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

    private:
        pointer _it;
        size_t _pos;

    public:
        m_iterator() : _it(nullptr), _pos(0) {}

        m_iterator(T *arr, size_t pos)
        {
            this->_it = &arr[pos];
            this->_pos = pos;
        }

        m_iterator(const m_iterator &copy)
        {
            this->_it = copy._it;
            this->_pos = copy._pos;
        }

        m_iterator &operator=(const m_iterator &copy)
        {
            this->_it = copy._it;
            this->_pos = copy._pos;
            return *this;
        }

        pointer get_pointer()
        {
            return this->_it;
        }

        bool operator==(const m_iterator &copy)
        {
            return (this->_it == copy._it) ? true : false;
        }

        bool operator!=(const m_iterator &copy)
        {
            return (this->_it != copy._it) ? true : false;
        }

        T &operator*()
        {
            return *this->_it;
        }

        T operator->()
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

        m_iterator &operator+(const T &n)
        {
           m_iterator tmp(*this);

            return tmp += n;
        }

        m_iterator &operator-(const T &n)
        {
            m_iterator tmp(*this);
            return tmp -= n;
        }

        bool operator<(const m_iterator &copy)
        {
            return (this->_it < copy._it) ? true : false;
        }

        bool operator>(const m_iterator &copy)
        {
            return (this->_it > copy._it) ? true : false;
        }

        bool operator<=(const m_iterator &copy)
        {
            return (this->_it <= copy._it) ? true : false;
        }

        bool operator>=(const m_iterator &copy)
        {
            return (this->_it >= copy._it) ? true : false;
        }

        m_iterator &operator+=(const T &n)
        {
            this->_it += n;
            return *this;
        }

        m_iterator &operator-=(const T &n)
        {
            this->_it -= n;
            return *this;
        }

        T &operator[](const T &n)
        {
            return this->_it[n];
        }

        ~m_iterator() {}
    };
    
    template <class T>
    size_t operator-( m_iterator<T> &x,  m_iterator<T> &y)
    {
        return x.get_pointer() - y.get_pointer();
    }

    template <class T>
    ft::m_iterator<T> operator+(const T &n, const m_iterator<T> &y)
    {
        ft::m_iterator<T> tmp(y);
        return tmp += n;
    }
}