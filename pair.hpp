/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:03:08 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/27 15:49:03 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

    public:
        pair() {}

        template <class U, class V>
        pair(const pair<U, V> &pr)
        {
            *this = pr;
        }

        pair(const first_type &a, const second_type &b) : first(a), second(b) {}

        pair &operator=(const pair &pr)
        {
            this->first = pr.first;
            this->second = pr.second;
            return *this;
        }

        friend bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }

        friend bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return !(lhs == rhs);
        }

        friend bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
        }

        friend bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return !(rhs < lhs);
        }

        friend bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return rhs < lhs;
        }

        friend bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
        {
            return !(lhs < rhs);
        }
    };

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (ft::pair<T1, T2>(x, y));
    }
}