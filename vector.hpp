/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 11:01:38 by mlasrite          #+#    #+#             */
/*   Updated: 2021/09/22 12:27:24 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef size_t size_type;

        //----------------

        explicit vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0) {}

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
        {
            this->_capacity = n;
            this->_size = n;
            this->_arr = this->_allocator.allocate(n);
            for (int i = 0; i < n; i++)
                _arr[i] = val;
        }

        size_type size() const { return this->_size; }
        size_type max_size() const { return this->_capacity; }

        void resize(size_type n, value_type val = value_type())
        {
            if (n < this->_size)
            {
                this->_size = n;
                for (int i = n; i < this->_size; i++)
                    this->_arr[i].~value_type();
            }
            else if (n > this->_size)
            {
                if (n > this->_capacity)
                {
                    value_type *tmp = this->_allocator.allocate(n);
                    for (int i = 0; i < this->_size; i++)
                        tmp[i] = this->_arr[i];

                    this->_allocator.deallocate(this->_arr, this->_capacity);

                    for (int i = this->_size; i < n; i++)
                        tmp[i] = val;

                    this->_capacity = n;
                    this->_size = n;
                    this->_arr = tmp;
                }
                else
                {
                    this->_size = n;
                    for (int i = this->_size; i < this->_capacity; i++)
                        this->_arr[i] = val;
                }
            }
        }

    private:
        value_type *_arr;
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;
    };

}