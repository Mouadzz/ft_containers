/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 11:01:38 by mlasrite          #+#    #+#             */
/*   Updated: 2021/09/23 12:22:35 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <math.h>
#include <vector>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
        /*----------------[ MEMBER TYPES ]----------------*/

        typedef T value_type;
        typedef Alloc allocator_type;
        typedef size_t size_type;

        /*----------------[ MEMBER TYPES ]----------------*/

        /*----------------[ EXCEPTIONS ]----------------*/

        class out_of_range : public std::exception
        {
        public:
            virtual const char *what() const throw()
            {
                return "Index out of range !";
            }
        };

        class length_error : public std::exception
        {
        public:
            virtual const char *what() const throw()
            {
                return "Size requested is greater than the maximum size !";
            }
        };

        /*----------------[ EXCEPTIONS ]----------------*/

        /*----------------[ CONSTRUCTORS ]----------------*/

        // Constructs an empty container, with no elements.
        explicit vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0) {}

        // Constructs a container with n elements. Each element is a copy of val.
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
        {
            this->_capacity = n;
            this->_size = n;
            this->_arr = this->_allocator.allocate(n);
            for (int i = 0; i < n; i++)
                _arr[i] = val;
        }

        /*----------------[ CONSTRUCTORS ]----------------*/

        /*----------------[ CAPACITY FUNCTIONS ]----------------*/

        // Returns the number of elements in the vector.
        size_type size() const { return this->_size; }

        // Returns the maximum number of elements that the vector can hold.
        size_type max_size() const { return (pow(2, 64) / sizeof(value_type) - 1); }

        // Resizes the container so that it contains n elements.
        void resize(size_type n, value_type val = value_type())
        {
            if (n < this->_size)
            {
                for (int i = n; i < this->_size; i++)
                    this->_arr[i].~value_type();
                this->_size = n;
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
                    for (int i = this->_size; i < n; i++)
                        this->_arr[i] = val;
                    this->_size = n;
                }
            }
        }

        // Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
        size_type capacity() const { return this->_capacity; }

        // Returns whether the vector is empty (i.e. whether its size is 0).
        bool empty() const
        {
            if (this->_size == 0)
                return true;
            else
                return false;
        }

        // Requests that the vector capacity be at least enough to contain n elements.
        void reserve(size_type n)
        {
            if (n > this->max_size())
                throw length_error();
            if (n > this->_capacity)
            {
                value_type *tmp = this->_allocator.allocate(n);
                for (int i = 0; i < this->_size; i++)
                    tmp[i] = this->_arr[i];
                this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = tmp;
                this->_capacity = n;
            }
        }

        /*----------------[ CAPACITY FUNCTIONS ]----------------*/

        /*----------------[ ELEMENT ACCESS ]----------------*/

        // Returns a reference to the element at position n in the vector container.
        value_type &operator[](size_type n)
        {
            if (n < this->_size)
                return this->_arr[n];
            else
                throw out_of_range();
        }

        // Returns a reference to the element at position n in the vector.
        value_type &at(size_type n)
        {
            if (n < this->_size)
                return this->_arr[n];
            else
                throw out_of_range();
        }

        // Returns a reference to the first element in the vector.
        value_type &front() { return this->_arr[0]; }

        // Returns a reference to the last element in the vector.
        value_type &back() { return this->_arr[this->_size - 1]; }

        /*----------------[ ELEMENT ACCESS ]----------------*/

    private:
        value_type *_arr;
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;
    };

}