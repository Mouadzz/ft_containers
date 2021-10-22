/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 11:01:38 by mlasrite          #+#    #+#             */
/*   Updated: 2021/10/22 15:34:16 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <math.h>
#include <iostream>
#include "iterator.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include <limits>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
        /*----------------[ MEMBER TYPES ]----------------*/

        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef Alloc allocator_type;
        typedef size_t size_type;
        typedef ft::m_iterator<T> iterator;
        typedef ft::m_iterator<const T> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        /*----------------[ END OF MEMBER TYPES ]----------------*/

        /*----------------[ CONSTRUCTORS ]----------------*/

        // Constructs an empty container, with no elements.
        explicit vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc)
        {
        }

        // Constructs a container with n elements. Each element is a copy of val.
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
        {
            this->_allocator = alloc;
            this->_capacity = n;
            this->_size = n;
            this->_arr = this->_allocator.allocate(n);
            for (size_t i = 0; i < n; i++)
                _arr[i] = val;
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
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

        vector(const vector &x) : _size(0), _capacity(0)
        {
            *this = x;
        }

        vector &operator=(const vector &x)
        {
            if (x.capacity() > this->_capacity)
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_arr[i].~value_type();

                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);

                this->_arr = this->_allocator.allocate(x.capacity());
                for (size_t i = 0; i < x.size(); i++)
                    this->_arr[i] = x[i];
                this->_capacity = x.capacity();
                this->_size = x.size();
            }
            else
            {
                for (size_t i = 0; i < this->_size; i++)
                    this->_arr[i].~value_type();
                for (size_t i = 0; i < x.size(); i++)
                    this->_arr[i] = x[i];
                this->_size = x.size();
            }
            return *this;
        }

        ~vector()
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

        // Returns an iterator pointing to the first element in the vector.
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

        // Returns an iterator referring to the past-the-end element in the vector container.
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

        //Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
        reverse_iterator rbegin()
        {
            return reverse_iterator(this->end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(this->end());
        }

        // Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
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

        // Returns the number of elements in the vector.
        size_type size() const { return this->_size; }

        // Returns the maximum number of elements that the vector can hold.
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
                        tmp[i] = this->_arr[i];

                    for (size_t i = 0; i < this->_size; i++)
                        this->_arr[i].~value_type();
                    if (this->_capacity > 0)
                        this->_allocator.deallocate(this->_arr, this->_capacity);

                    for (size_t i = this->_size; i < n; i++)
                        tmp[i] = val;

                    this->_capacity = n;
                    this->_size = n;
                    this->_arr = tmp;
                }
                else
                {
                    for (size_t i = this->_size; i < n; i++)
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
                throw std::length_error("Size requested is negative or  greater than the maximum size !");
            if (n > this->_capacity)
            {
                value_type *tmp = this->_allocator.allocate(n);
                for (size_t i = 0; i < this->_size; i++)
                    tmp[i] = this->_arr[i];
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = tmp;
                this->_capacity = n;
            }
        }

        /*----------------[ END OF CAPACITY FUNCTIONS ]----------------*/

        /*----------------[ ELEMENT ACCESS ]----------------*/

        // Returns a reference to the element at position n in the vector container.
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

        // Returns a reference to the element at position n in the vector.
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

        // Returns a reference to the first element in the vector.
        reference front() { return this->_arr[0]; }
        const_reference front() const { return this->_arr[0]; }

        // Returns a reference to the last element in the vector.
        reference back() { return this->_arr[this->_size - 1]; }
        const_reference back() const { return this->_arr[this->_size - 1]; }

        /*----------------[ END OF ELEMENT ACCESS ]----------------*/

        /*----------------[ MODIFIERS ]----------------*/
        // Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.

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
                    this->_arr[i] = val;
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
                        this->_arr[i] = val;
                    this->_size = n;
                }
                else
                {
                    for (size_t i = 0; i < n; i++)
                        this->_arr[i].~value_type();
                    for (size_t i = 0; i < n; i++)
                        this->_arr[i] = val;
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
                    for (InputIterator i = first; i != last; i++)
                        this->push_back(*i);
                    this->_capacity = range;
                }
                else
                {
                    if (range > this->_size)
                    {
                        for (size_t i = 0; i < this->_size; i++)
                            this->_arr[i].~value_type();
                        for (InputIterator i = first; i != last; i++)
                            this->push_back(*i);
                    }
                    else
                    {
                        for (size_t i = 0; i < range; i++)
                            this->_arr[i].~value_type();
                        for (InputIterator i = first; i != last; i++)
                            this->push_back(*i);
                    }
                }
            }
        }

        // Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
        void push_back(const value_type &val)
        {
            if (this->_size + 1 > this->_capacity)
            {
                reserve(this->_capacity + 1);
                this->_arr[this->_size] = val;
            }
            else
                this->_arr[this->_size] = val;
            this->_size += 1;
        }

        // Removes the last element in the vector, effectively reducing the container size by one.
        void pop_back()
        {
            this->_arr[this->_size - 1].~value_type();
            this->_size -= 1;
        }

        // The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
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
            int range = last - first;
            if (this->_size + range > this->_capacity)
            {
                size_t newCap = this->_capacity + range;
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
                    m_tmp[i] = *m_first;
                    i++;
                    m_first++;
                }
                iterator tmp(first);
                for (int j = 0; j < range; j++)
                {
                    m_tmp[i] = *tmp;
                    i++;
                    tmp++;
                }
                while (i < end)
                {
                    m_tmp[i] = *m_first;
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
                        iterator tmp(last - 1);
                        for (int i = 0; i < range; i++)
                        {
                            *m_tmp = *tmp;
                            m_tmp--;
                            tmp--;
                        }
                        break;
                    }
                    *m_tmp = *end;
                    end--;
                    m_tmp--;
                }
                if ((m_tmp == (position + (range - 1))) && (position == begin))
                {
                    iterator tmp(last - 1);
                    for (int i = 0; i < range; i++)
                    {
                        *m_tmp = *tmp;
                        m_tmp--;
                        tmp--;
                    }
                }
                this->_size += range;
            }
        }

        // Removes from the vector either a single element (position) or a range of elements ([first,last)).
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
                size_t newCap = this->_capacity - 1;
                value_type *tmp = this->_allocator.allocate(newCap);
                iterator first = this->begin();
                iterator last = this->end();
                size_t pos = position - first;
                size_t end = newCap;
                size_t i = 0;
                while (i < pos)
                {
                    tmp[i] = *first;
                    i++;
                    first++;
                }
                first++;
                iterator pointer(tmp, i);
                ret = pointer;
                while (i < end)
                {
                    tmp[i] = *first;
                    i++;
                    first++;
                }
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = tmp;
                this->_capacity = newCap;
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
                    tmp[i] = *m_first;
                    i++;
                    m_first++;
                }
                iterator pointer(tmp, i);
                ret = pointer;
                for (int i = 0; i < range; i++)
                    m_first++;
                while (i < newCap)
                {
                    tmp[i] = *m_first;
                    i++;
                    m_first++;
                }
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

        // Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
        void swap(vector &x)
        {

            value_type *tmp = this->_allocator.allocate(this->_capacity);
            for (int i = 0; i < this->_size; i++)
                tmp[i] = this->_arr[i];
            size_type tmpCap = this->_capacity;
            size_type tmpSize = this->_size;

            if (this->_capacity > 0)
                this->_allocator.deallocate(this->_arr, this->_capacity);

            this->_arr = this->_allocator.allocate(x._capacity);
            for (int i = 0; i < x._size; i++)
                this->_arr[i] = x[i];
            this->_size = x._size;
            this->_capacity = x._capacity;

            if (x._capacity > 0)
                x._allocator.deallocate(x._arr, x._capacity);
            x._arr = x._allocator.allocate(tmpCap);
            for (size_t i = 0; i < tmpSize; i++)
                x._arr[i] = tmp[i];
            x._size = tmpSize;
            x._capacity = tmpCap;
            if (tmpCap > 0)
                this->_allocator.deallocate(tmp, tmpCap);
        }

        // Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
        void clear()
        {
            for (int i = 0; i < this->_size; i++)
                this->_arr[i].~value_type();
            this->_size = 0;
        }

        /*----------------[ END OF  MODIFIERS ]----------------*/

        /*----------------[ ALLOCATOR ]----------------*/

        // Returns a copy of the allocator object associated with the vector.
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
                size_t newCap = this->_capacity + n;
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
                    tmp[i] = *first;
                    i++;
                    first++;
                }
                iterator pointer(tmp, i);
                ret = pointer;
                for (size_t j = 0; j < n; j++)
                {
                    tmp[i] = val;
                    i++;
                }
                while (i < end)
                {
                    tmp[i] = *first;
                    i++;
                    first++;
                }
                if (this->_capacity > 0)
                    this->_allocator.deallocate(this->_arr, this->_capacity);
                this->_arr = tmp;
                this->_capacity = newCap;
                this->_size += n;
            }
            else
            {
                iterator begin = this->begin();
                iterator end(this->_arr, this->_capacity - (n + 1));
                iterator tmp(this->_arr, this->_capacity - 1);
                while (tmp != begin)
                {
                    if (tmp == (position + (n - 1)))
                    {
                        for (size_t i = 0; i < n; i++)
                        {
                            *tmp = val;
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
                    for (size_t i = 0; i < n; i++)
                    {
                        *tmp = val;
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
    void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
    {
        x.swap(y);
    }

    //Performs the appropriate comparison operation between the vector containers lhs and rhs.
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {

        if (lhs.size() == rhs.size())
        {
            for (int i = 0; i < lhs.size(); i++)
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
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {

        if (lhs.size() == rhs.size())
        {
            for (int i = 0; i < lhs.size(); i++)
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
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {

        if (lhs == rhs)
            return false;
        else
        {
            for (int i = 0; i < ((lhs.size() < rhs.size()) ? lhs.size() : rhs.size()); i++)
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
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (lhs < rhs || lhs == rhs) ? true : false;
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {

        if (lhs == rhs)
            return false;
        else
        {
            for (int i = 0; i < ((lhs.size() < rhs.size()) ? lhs.size() : rhs.size()); i++)
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
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {

        return (lhs > rhs || lhs == rhs) ? true : false;
    }

    /*----------------[ END OF NON-MEMBER FUNCTION OVERLOADS ]----------------*/
}