/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:01:43 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/24 13:44:10 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;

    private:
        iterator_type _rit;

    public:
        reverse_iterator() : _rit() {}

        explicit reverse_iterator(iterator_type it)
        {
            iterator_type tmp = it;
            this->_rit = --tmp;
        }

        reverse_iterator(const reverse_iterator &rev_it)
        {
            this->_rit = rev_it._rit;
        }

        template <typename riter>
        reverse_iterator(reverse_iterator<riter> const& rit)
        {
            _rit = --rit.base();
        }
        
        iterator_type base() const
        {
            iterator_type tmp = this->_rit;
            return ++tmp;
        }
        
        reference operator*() const
        {
            return *_rit;
        }

        reverse_iterator operator+(difference_type n) const
        {
            reverse_iterator tmp(*this);
            tmp._rit -= n;
            return tmp;
        }

        reverse_iterator &operator++()
        {
            --this->_rit;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            --this->_rit;
            return tmp;
        }

        reverse_iterator &operator+=(difference_type n)
        {
            this->_rit = this->_rit - n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const
        {
            reverse_iterator tmp(*this);
            tmp._rit += n;
            return tmp;
        }

        reverse_iterator &operator--()
        {
            ++this->_rit;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp(*this);
            ++this->_rit;
            return tmp;
        }

        reverse_iterator &operator-=(difference_type n)
        {
            this->_rit = this->_rit + n;
            return *this;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reference operator[](difference_type n) const
        {
            return this->_rit[-n];
        }

        friend bool operator==(const reverse_iterator &lhs,
                               const reverse_iterator &rhs)
        {
            return (lhs._rit == rhs._rit);
        }
        friend bool operator!=(const reverse_iterator &lhs,
                               const reverse_iterator &rhs)
        {
            return (lhs._rit != rhs._rit);
        }
        friend bool operator<(const reverse_iterator &lhs,
                              const reverse_iterator &rhs)
        {
            return (lhs._rit > rhs._rit);
        }
        friend bool operator<=(const reverse_iterator &lhs,
                               const reverse_iterator &rhs)
        {
            return (lhs._rit >= rhs._rit);
        }
        friend bool operator>(const reverse_iterator &lhs,
                              const reverse_iterator &rhs)
        {
            return (lhs._rit < rhs._rit);
        }
        friend bool operator>=(const reverse_iterator &lhs,
                               const reverse_iterator &rhs)
        {
            return (lhs._rit <= rhs._rit);
        }
        friend difference_type operator-(
            const reverse_iterator &lhs,
            const reverse_iterator &rhs)
        {
            return (rhs._rit - lhs._rit);
        }
        friend reverse_iterator operator+(
            difference_type n,
            const reverse_iterator &rev_it)
        {
            reverse_iterator tmp(rev_it);
            tmp += n;
            return tmp;
        }
    };

}