/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:39:17 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/06/29 17:57:16 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

# include <memory>	// allocator의 header

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		/* MEMBER TYPES */
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		
		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;

	public:
		/* MEMBER FUNCTIONS */
		// Construct vector (public member function)
		// default
		explicit vector (const allocator_type& alloc = allocator_type());

		// fill
		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());

		// range
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, 
				const allocator_type& alloc = allocator_type());

		// copy
		vector (const vector& x);

		// Vector destructor (public member function)
		~vector();

		// Assign content (public member function)
		// copy
		vector& operator= (const vector& x);

		/* ITERATORS */
		// Return iterator to beginning (public member function)
		iterator begin();

		const_iterator begin() const;

		// Return iterator to end (public member function)
		iterator end();

		const_iterator end() const;

		// Return reverse iterator to reverse beginning (public member function)
		reverse_iterator rbegin();

		const_reverse_iteratotr rbegin() const;

		// Return reverse iterator to reverse end (public member function)
		reverse_iterator rend();

		const_reverse_iterator rend() const;

		/* CAPACITY */
		// Return size (public member function)
		size_type size() const;

		// Return maximum size (public member function)
		size_type max_size() const;

		// Change size (public member function)
		void resize (size_type n, value_type val = value_type());

		// Return size of allocated storage capacity (public member function)
		size_type capacity() const;

		// Test whether vector is empty (public member function)
		bool empty() const;

		// Request a change in capacity (public member function)
		void reserve (size_type n);

		/* ELEMENT ACCESS */
		// Access element (public member function)
		reference operator[] (size_type n);

		const_reference operator[] (size_type n) const;

		// Access element (public member function)
		reference at (size_type n);

		const_reference at (size_type n) const;

		// Access first element (public member function)
		reference front();

		const_reference front() const;

		// Access last element (public member function)
		reference back();

		const_reference back() const;

		/* MODIFIERS */
		// Assign vector content (public member function)
		// range
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);

		// fill
		void assign (size_type n, const value_type& val);

		// Add element at the end (public member function)
		void push_back (const value_type& val);

		// Delete last element (public member function)
		void pop_back();

		// Insert elements (public member function)
		// single element
		iterator insert (iterator position, const value_type& val);

		// fill
		void insert (iterator position, size_type n, const value_type& val);

		// range
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);

		// Erase elements (public member function)
		iterator erase (iterator position);

		iterator erase (iteraotr first, iterator last);

		// Swap content (public member function)
		void swap (vector& x);

		// Clear content (public member function)
		void clear();

		/* ALLOCATOR */
		// Get allocator (public member function)
		allocator_type get_allocator() const;
	};	// class vector

	/* NON-MEMBER FUNCTION OVERLOADS */
	// relational operators for vector (function template)
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// Exchange contents of vectors (function template)
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}	// namespace ft

#endif /* ********************************************************** VECTOR_H */