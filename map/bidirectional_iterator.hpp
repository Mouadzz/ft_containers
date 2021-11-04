/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:52:45 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/04 13:10:39 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector/random_access_iterator.hpp"
#include "rbt.hpp"

namespace ft
{
    template <class Key, class T>
    class map_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
    {

        typedef ft::Node<Key, T> node_type;

    private:
        node_type *_node;

    public:
        map_iterator() : _node(NULL) {}

        map_iterator(node_type *node)
        {
            this->_node = node;
        }

        ~map_iterator() {}
    };
}
