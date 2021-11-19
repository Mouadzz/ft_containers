/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 11:01:38 by mlasrite          #+#    #+#             */
/*   Updated: 2021/11/19 16:51:33 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <math.h>
#include <iostream>
#include "random_access_iterator.hpp"
#include "../utils/utils.hpp"
#include "../utils/reverse_iterator.hpp"
#include <limits>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class Vector
    {
    public:
        /*----------------[ MEMBER TYPES ]----------------*/

        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef Alloc allocator_type;
        typedef size_t size_type;
        typedef ft::vector_iterator<T> iterator;
        typedef ft::vector_iterator<const T> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        /*----------------[ END OF MEMBER TYPES ]----------------*/

        /*----------------[ CONSTRUCTORS ]----------------*/

        // Constructs an empty container, with no elements.
        explicit Vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc)
        {
        }

        // Constructs a container with n elements. Each element is a copy of val.
        explicit Vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
        {
            this->_allocator = alloc;
            this->_capacity = n;
            this->_size = n;
            this->_arr = this->_allocator.allocate(n);
            for (size_t i = 0; i < n; i++)
                this->_allocator.construct(_arr + i, val);
        }

        template <class InputIterator>
        Vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
        {
            this->_allocator = alloc;
            int range = last - first;
            if (range < 0)
                throw std::length_error("Size requested is negative or  greater than the maximum size !");
            else
            {
                this->_capacity = range;
                this->_size = 0;
                this->_arr = this->_allocator.allocate(range);
                for (InputIterator i = first; i != last; i++)
                    this->push_back(*i);
            }
        }

        Vector(const Vector &x) : _size(0), _capacity(0)
        {
            *this = x;
        }

        Vector &operator=(const Vector &x)
        {
            if (x.capacity() > this->_capacity)
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_arr[i].~value_type();

                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);

                this->_arr = this->_allocator.allocate(x.capacity());
                for (size_t i = 0; i < x.size(); i++)
                    this->_allocator.construct(_arr + i, x[i]);
                this->_capacity = x.capacity();
                this->_size = x.size();
            }
            else
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_arr[i].~value_type();
                for (size_t i = 0; i < x.size(); i++)
                    this->_allocator.construct(_arr + i, x[i]);
                this->_size = x.size();
            }
            return *this;
        }

        ~Vector()
        {
            if (this->_capacity > 0)
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_arr[i].~value_type();
                this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_size = 0;
                this->_capacity = 0;
            }
        }
        /*----------------[ END OF CONSTRUCTORS ]----------------*/

        /*----------------[ ITERATOR FUNCTIONS ]----------------*/

        // Returns an iterator pointing to the first element in the Vector.
        iterator begin()
        {
            iterator it(this->_arr, 0);
            return it;
        }

        const_iterator begin() const
        {
            const_iterator it(this->_arr, 0);
            return it;
        }

        // Returns an iterator referring to the past-the-end element in the Vector container.
        iterator end()
        {
            iterator it(this->_arr, this->_size);
            return it;
        }

        const_iterator end() const
        {
            const_iterator it(this->_arr, this->_size);
            return it;
        }

        //Returns a reverse iterator pointing to the last element in the Vector (i.e., its reverse beginning).
        reverse_iterator rbegin()
        {
            return reverse_iterator(this->end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(this->end());
        }

        // Returns a reverse iterator pointing to the theoretical element preceding the first element in the Vector (which is considered its reverse end).
        reverse_iterator rend()
        {
            return reverse_iterator(this->begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(this->begin());
        }

        /*----------------[ END OF ITERATOR FUNCTIONS ]----------------*/

        /*----------------[ CAPACITY FUNCTIONS ]----------------*/

        // Returns the number of elements in the Vector.
        size_type size() const { return this->_size; }

        // Returns the maximum number of elements that the Vector can hold.
        size_type max_size() const
        {
            size_t maxvalue = std::numeric_limits<size_t>::max();
            size_type res = maxvalue / sizeof(value_type);
            return res;
        }

        // Resizes the container so that it contains n elements.
        void resize(size_type n, value_type val = value_type())
        {
            if (n < this->_size)
            {
                for (size_t i = n; i < this->_size; i++)
                    this->_arr[i].~value_type();
                this->_size = n;
            }
            else if (n > this->_size)
            {
                if (n > this->_capacity)
                {
                    value_type *tmp = this->_allocator.allocate(n);
                    for (size_t i = 0; i < this->_size; i++)
                        this->_allocator.construct(tmp + i, this->_arr[i]);

                    for (size_t i = 0; i < this->_size; i++)
                        this->_arr[i].~value_type();
                    if (this->_capacity > 0)
                        this->_allocator.deallocate(this->_arr, this->_capacity);

                    for (size_t i = this->_size; i < n; i++)
                        this->_allocator.construct(tmp + i, val);

                    this->_capacity = n;
                    this->_size = n;
                    this->_arr = tmp;
                }
                else
                {
                    for (size_t i = this->_size; i < n; i++)
                        this->_allocator.construct(_arr + i, val);
                    this->_size = n;
                }
            }
        }

        // Returns the size of the storage space currently allocated for the Vector, expressed in terms of elements.
        size_type capacity() const { return this->_capacity; }

        // Returns whether the Vector is empty (i.e. whether its size is 0).
        bool empty() const
        {
            if (this->_size == 0)
                return true;
            else
                return false;
        }

        // Requests that the Vector capacity be at least enough to contain n elements.
        void reserve(size_type n)
        {
            if (n > this->max_size())
                throw std::length_error("Size requested is negative or  greater than the maximum size !");
            if (n > this->_capacity)
            {
                value_type *tmp = this->_allocator.allocate(n);
                for (size_t i = 0; i < this->_size; i++)
                    this->_allocator.construct(tmp + i, this->_arr[i]);
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = tmp;
                this->_capacity = n;
            }
        }

        /*----------------[ END OF CAPACITY FUNCTIONS ]----------------*/

        /*----------------[ ELEMENT ACCESS ]----------------*/

        // Returns a reference to the element at position n in the Vector container.
        reference operator[](size_type n)
        {
            if (n < this->_size)
                return this->_arr[n];
            else
                throw std::out_of_range("Index out of range !");
        }

        const_reference operator[](size_type n) const
        {
            if (n < this->_size)
                return this->_arr[n];
            else
                throw std::out_of_range("Index out of range !");
        }

        // Returns a reference to the element at position n in the Vector.
        reference at(size_type n)
        {
            if (n < this->_size)
                return this->_arr[n];
            else
                throw std::out_of_range("Index out of range !");
        }

        const_reference at(size_type n) const
        {
            if (n < this->_size)
                return this->_arr[n];
            else
                throw std::out_of_range("Index out of range !");
        }

        // Returns a reference to the first element in the Vector.
        reference front() { return this->_arr[0]; }
        const_reference front() const { return this->_arr[0]; }

        // Returns a reference to the last element in the Vector.
        reference back() { return this->_arr[this->_size - 1]; }
        const_reference back() const { return this->_arr[this->_size - 1]; }

        /*----------------[ END OF ELEMENT ACCESS ]----------------*/

        /*----------------[ MODIFIERS ]----------------*/
        // Assigns new contents to the Vector, replacing its current contents, and modifying its size accordingly.

        void assign(size_type n, const value_type &val)
        {
            if (n > this->_capacity)
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_arr[i].~value_type();
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = this->_allocator.allocate(n);
                for (size_t i = 0; i < n; i++)
                    this->_allocator.construct(_arr + i, val);

                this->_capacity = n;
                this->_size = n;
            }
            else
            {
                if (n > this->_size)
                {
                    for (size_t i = 0; i < this->_size; i++)
                        this->_arr[i].~value_type();
                    for (size_t i = 0; i < n; i++)
                        this->_allocator.construct(_arr + i, val);
                    this->_size = n;
                }
                else
                {
                    for (size_t i = 0; i < n; i++)
                        this->_arr[i].~value_type();
                    for (size_t i = 0; i < n; i++)
                        this->_allocator.construct(_arr + i, val);
                    this->_size = n;
                }
            }
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
        {
            size_t range = last - first;
            if (range > 0)
            {
                if (range > this->_capacity)
                {
                    for (size_t i = 0; i < this->_size; i++)
                        this->_arr[i].~value_type();
                    if (this->_capacity > 0)
                        this->_allocator.deallocate(this->_arr, this->_capacity);
                    this->_arr = this->_allocator.allocate(range);
                    int j = 0;
                    for (InputIterator i = first; i != last; i++)
                    {
                        this->_allocator.construct(_arr + j, *i);
                        j += 1;
                    }
                    this->_capacity = range;
                    this->_size = j;
                }
                else
                {
                    if (range > this->_size)
                    {
                        for (size_t i = 0; i < this->_size; i++)
                            this->_arr[i].~value_type();
                        int j = 0;
                        for (InputIterator i = first; i != last; i++)
                        {
                            this->_allocator.construct(_arr + j, *i);
                            j += 1;
                        }
                        this->_size = j;
                    }
                    else
                    {
                        for (size_t i = 0; i < range; i++)
                            this->_arr[i].~value_type();
                        int j = 0;
                        for (InputIterator i = first; i != last; i++)
                        {
                            this->_allocator.construct(_arr + j, *i);
                            j += 1;
                        }
                        this->_size = j;
                    }
                }
            }
        }

        // Adds a new element at the end of the Vector, after its current last element. The content of val is copied (or moved) to the new element.
        void push_back(const value_type &val)
        {
            if (this->_size + 1 > this->_capacity)
            {
                reserve((this->_capacity == 0) ? 1 : (this->_capacity * 2));
                this->_allocator.construct(_arr + this->_size, val);
            }
            else
                this->_allocator.construct(_arr + this->_size, val);
            this->_size += 1;
        }

        // Removes the last element in the Vector, effectively reducing the container size by one.
        void pop_back()
        {
            this->_arr[this->_size - 1].~value_type();
            this->_size -= 1;
        }

        // The Vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
        iterator insert(iterator position, const value_type &val)
        {
            iterator ret = this->m_insert(position, val, 1);
            return ret;
        }

        void insert(iterator position, size_type n, const value_type &val)
        {
            this->m_insert(position, val, n);
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
        {
            size_t range = last - first;
            if (this->_size + range > this->_capacity)
            {
                size_t newCap;
                if (this->_capacity == 0)
                    newCap = range;
                else if (this->_size >= range)
                    newCap = this->_size * 2;
                else
                    newCap = this->_size + range;
                if (newCap > this->max_size())
                    throw std::length_error("Size requested is negative or  greater than the maximum size !");
                value_type *m_tmp = this->_allocator.allocate(newCap);
                iterator m_first = this->begin();
                iterator m_last = this->end();
                size_t pos = position - m_first;
                size_t end = (m_last + range) - m_first;
                size_t i = 0;
                while (i < pos)
                {
                    this->_allocator.construct(m_tmp + i, *m_first);
                    i++;
                    m_first++;
                }
                for (size_t j = 0; j < range; j++)
                {
                    this->_allocator.construct(m_tmp + i, *first);

                    i++;
                    first++;
                }
                while (i < end)
                {
                    this->_allocator.construct(m_tmp + i, *m_first);
                    i++;
                    m_first++;
                }
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = m_tmp;
                this->_capacity = newCap;
                this->_size += range;
            }
            else
            {
                iterator begin = this->begin();
                iterator end(this->_arr, this->_capacity - (range + 1));
                iterator m_tmp(this->_arr, this->_capacity - 1);
                while (m_tmp != begin)
                {
                    if (m_tmp == (position + (range - 1)))
                    {
                        last--;
                        for (size_t i = 0; i < range; i++)
                        {
                            this->_allocator.construct(&*m_tmp, *last);
                            m_tmp--;
                            last--;
                        }
                        break;
                    }
                    *m_tmp = *end;
                    end--;
                    m_tmp--;
                }
                if ((m_tmp == (position + (range - 1))) && (position == begin))
                {
                    last--;
                    for (size_t i = 0; i < range; i++)
                    {
                        this->_allocator.construct(&*m_tmp, *last);
                        m_tmp--;
                        last--;
                    }
                }
                this->_size += range;
            }
        }

        // Removes from the Vector either a single element (position) or a range of elements ([first,last)).
        iterator erase(iterator position)
        {
            iterator end = this->end() - 1;
            iterator ret;
            if (position == end)
            {
                this->pop_back();
                ret = this->end();
            }
            else
            {
                iterator first = this->begin();
                iterator last = this->end() - 1;
                size_t pos = position - first;
                size_t i = 0;
                while (i < pos)
                    i++;
                this->_arr[i].~value_type();
                iterator pointer(this->_arr, i);
                ret = pointer;
                while (i + 1 < this->_size)
                {
                    this->_allocator.construct(this->_arr + i, this->_arr[i + 1]);
                    i += 1;
                }
                this->_size -= 1;
            }
            return ret;
        }

        iterator erase(iterator first, iterator last)
        {
            iterator ret;
            if (last > first)
            {
                int range = last - first;
                size_t newCap = this->_capacity - range;
                value_type *tmp = this->_allocator.allocate(newCap);
                iterator m_first = this->begin();
                iterator m_last = this->end();
                size_t i = 0;
                while (m_first != first)
                {
                    this->_allocator.construct(tmp + i, *m_first);
                    i++;
                    m_first++;
                }
                iterator pointer(tmp, i);
                ret = pointer;
                for (int i = 0; i < range; i++)
                    m_first++;
                while (i < newCap)
                {
                    this->_allocator.construct(tmp + i, *m_first);
                    i++;
                    m_first++;
                }
                for (size_t j = 0; j < this->_size; j++)
                    this->_arr[j].~value_type();
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = tmp;
                this->_capacity = newCap;
                this->_size -= range;
            }
            else
                ret = this->begin();
            return ret;
        }

        // Exchanges the content of the container by the content of x, which is another Vector object of the same type. Sizes may differ.
        void swap(Vector &x)
        {
            Alloc tmp = this->_allocator;
            this->_allocator = x._allocator;
            x._allocator = tmp;

            size_t tmp1 = this->_capacity;
            this->_capacity = x._capacity;
            x._capacity = tmp1;

            size_t tmp2 = this->_size;
            this->_size = x._size;
            x._size = tmp2;

            T *tmp3 = this->_arr;
            this->_arr = x._arr;
            x._arr = tmp3;
        }

        // Removes all elements from the Vector (which are destroyed), leaving the container with a size of 0.
        void clear()
        {
            for (size_t i = 0; i < this->_size; i++)
                this->_arr[i].~value_type();
            this->_size = 0;
        }

        /*----------------[ END OF  MODIFIERS ]----------------*/

        /*----------------[ ALLOCATOR ]----------------*/

        // Returns a copy of the allocator object associated with the Vector.
        allocator_type get_allocator() const { return this->_allocator; }

        /*----------------[ END OF ALLOCATOR ]----------------*/

    private:
        value_type *_arr;
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;

        iterator m_insert(iterator position, const value_type &val, size_type n)
        {
            iterator ret = position;
            if (this->_size + n > this->_capacity)
            {
                size_t newCap;
                if (this->_capacity == 0)
                    newCap = n;
                else if (this->_size >= n)
                    newCap = this->_size * 2;
                else
                    newCap = this->_size + n;
                if (newCap > this->max_size())
                    throw std::length_error("Size requested is negative or  greater than the maximum size !");
                value_type *tmp = this->_allocator.allocate(newCap);
                iterator first = this->begin();
                iterator last = this->end();
                size_t pos = position - first;
                size_t end = (last + n) - first;
                size_t i = 0;
                while (i < pos)
                {
                    this->_allocator.construct(tmp + i, *first);
                    i++;
                    first++;
                }
                iterator pointer(tmp, i);
                ret = pointer;
                for (size_t j = 0; j < n; j++)
                {
                    this->_allocator.construct(tmp + i, val);
                    i++;
                }
                while (i < end)
                {
                    this->_allocator.construct(tmp + i, *first);
                    i++;
                    first++;
                }
                for (size_t i = 0; i < this->_size; i++)
                    this->_arr[i].~value_type();
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = tmp;
                this->_capacity = newCap;
                this->_size += n;
            }
            else
            {
                iterator begin = this->begin();
                iterator end(this->_arr, this->_size - 1);
                iterator tmp(this->_arr, this->_size + (n - 1));
                while (tmp != begin)
                {
                    if (tmp == (position + (n - 1)))
                    {
                        ret = tmp;
                        for (size_t i = 0; i < n; i++)
                        {
                            this->_allocator.construct(&*tmp, val);
                            tmp--;
                        }
                        break;
                    }
                    *tmp = *end;
                    end--;
                    tmp--;
                }
                if ((tmp == (position + (n - 1))) && (position == begin))
                {
                    ret = tmp;
                    for (size_t i = 0; i < n; i++)
                    {
                        this->_allocator.construct(&*tmp, val);
                        tmp--;
                    }
                }
                this->_size += n;
            }
            return ret;
        }
    };

    /*----------------[ NON-MEMBER FUNCTION OVERLOADS ]----------------*/

    // The contents of container x are exchanged with those of y. Both container objects must be of the same type (same template parameters), although sizes may differ.
    template <class T, class Alloc>
    void swap(Vector<T, Alloc> &x, Vector<T, Alloc> &y)
    {
        x.swap(y);
    }

    //Performs the appropriate comparison operation between the Vector containers lhs and rhs.
    template <class T, class Alloc>
    bool operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
    {

        if (lhs.size() == rhs.size())
        {
            for (size_t i = 0; i < lhs.size(); i++)
            {
                if (lhs[i] != rhs[i])
                    return false;
            }
        }
        else
            return false;
        return true;
    }

    template <class T, class Alloc>
    bool operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
    {

        if (lhs.size() == rhs.size())
        {
            for (size_t i = 0; i < lhs.size(); i++)
            {
                if (lhs[i] != rhs[i])
                    return true;
            }
        }
        else
            return true;
        return false;
    }

    template <class T, class Alloc>
    bool operator<(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
    {

        if (lhs == rhs)
            return false;
        else
        {
            for (size_t i = 0; i < ((lhs.size() < rhs.size()) ? lhs.size() : rhs.size()); i++)
            {
                if (lhs[i] > rhs[i])
                    return false;
                else if (lhs[i] < rhs[i])
                    return true;
            }
            return (lhs.size() < rhs.size()) ? true : false;
        }
        return false;
    }

    template <class T, class Alloc>
    bool operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
    {
        return (lhs < rhs || lhs == rhs) ? true : false;
    }

    template <class T, class Alloc>
    bool operator>(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
    {

        if (lhs == rhs)
            return false;
        else
        {
            for (size_t i = 0; i < ((lhs.size() < rhs.size()) ? lhs.size() : rhs.size()); i++)
            {
                if (lhs[i] < rhs[i])
                    return false;
                else if (lhs[i] > rhs[i])
                    return true;
            }
            return (lhs.size() > rhs.size()) ? true : false;
        }
        return false;
    }

    template <class T, class Alloc>
    bool operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs)
    {

        return (lhs > rhs || lhs == rhs) ? true : false;
    }

    /*----------------[ END OF NON-MEMBER FUNCTION OVERLOADS ]----------------*/
}