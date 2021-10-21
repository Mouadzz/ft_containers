/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:01:43 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/21 12:02:02 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;

    public:
        // reverse_iterator()
        // {

        // }
        // explicit reverse_iterator(iterator_type it)
        // {

        // }
        // template <class Iter>
        // reverse_iterator(const reverse_iterator<Iter> &rev_it)
        // {

        // }
    };
}