/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:52:45 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 11:06:48 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector/random_access_iterator.hpp"

namespace ft
{
    template <class T>
    class map_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer pointer;
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type difference_type;

    private:
        pointer _it;

    public:
        map_iterator() : _it(nullptr) {}

        map_iterator(T *arr, size_t pos)
        {
            this->_it = &arr[pos];
        }

        map_iterator(pointer it)
        {
            this->_it = it;
        }

        map_iterator(map_iterator const &copy)
        {
            *this = copy;
        }

        operator map_iterator<const T>() const
        {
            return map_iterator<const T>(this->_it);
        }

        map_iterator &operator=(map_iterator const &copy)
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

        map_iterator operator++(int)
        {
            map_iterator tmp(*this);
            ++this->_it;
            return tmp;
        }

        map_iterator &operator++()
        {
            ++this->_it;
            return *this;
        }

        map_iterator operator--(int)
        {
            map_iterator tmp(*this);
            --this->_it;
            return tmp;
        }

        map_iterator &operator--()
        {
            --this->_it;
            return *this;
        }

        friend bool operator==(const map_iterator &lhs, const map_iterator &rhs)
        {
            return (lhs._it == rhs._it);
        }

        friend bool operator!=(const map_iterator &lhs, const map_iterator &rhs)
        {
            return (lhs._it != rhs._it);
        }

        ~map_iterator() {}
    };
}
