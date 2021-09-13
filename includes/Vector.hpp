/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:39:17 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/08/19 23:19:38 by yeonhlee         ###   ########.fr       */
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
	class Vector
	{
	public:
		/* MEMBER TYPES */
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;

		/*
		**	/////
		*/
		// iterator;
		// const_iterator;
		// reverse_iterator;
		// const_reverse_interator;
		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;

	protected:
		allocator_type	m_alloc;

		pointer			m_start;
		pointer			m_finish;
		pointer			m_end_of_storage;

	public:
		/* MEMBER FUNCTIONS */
		// Construct Vector (public member function)
		// default
		explicit Vector (const allocator_type& alloc = allocator_type())
		:	m_alloc(alloc), m_start(0), m_finish(0), m_end_of_storage(0)
		{}

		// fill
		explicit Vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
		:	m_alloc(alloc)
		{
			m_start = m_alloc.allocate(n);
			m_finish = m_start;
			m_end_of_storage = m_start + n;
			while (m_finish != m_end_of_storage)
			{
				m_alloc.construct(m_finish, val);
				m_finish++;
			}
		}

		// range
		template <class InputIterator>
		Vector (InputIterator first, InputIterator last, 
				const allocator_type& alloc = allocator_type());
		/*
		**	/////
		*/

		// copy
		Vector (const Vector& x);
		/*
		**	/////
		*/

		// Vector destructor (public member function)
		~Vector();
		/*
		**	/////
		*/

		// Assign content (public member function)
		// copy
		Vector& operator= (const Vector& x);

		// /* ITERATORS */
		// // Return iterator to beginning (public member function)
		// iterator begin();

		// const_iterator begin() const;

		// // Return iterator to end (public member function)
		// iterator end();

		// const_iterator end() const;

		// // Return reverse iterator to reverse beginning (public member function)
		// reverse_iterator rbegin();

		// const_reverse_iteratotr rbegin() const;

		// // Return reverse iterator to reverse end (public member function)
		// reverse_iterator rend();

		// const_reverse_iterator rend() const;

		/* CAPACITY */
		// Return size (public member function)
		size_type size() const
		{ return (size_type(m_finish - m_start)); }

		// Return maximum size (public member function)
		size_type max_size() const
		{ return (m_alloc.max_size()); }

		// Change size (public member function)
		void resize (size_type n, value_type val = value_type());
		{
			// 에러 처리 (n이 max_size보다 클 때)
			if (n > max_size())
				throw (std::length_error("vector::resize"));
			// 기본 사이즈보다 새로운 사이즈가 클 때
			if (n > size())
				insert(this->end(), n - size(), val);
			// 기본 사이즈보다 새로운 사이즈가 작을 때
			else if (n < size())
			{
				while (size() > n)
				{
					m_end_of_storage--;
					m_alloc.destroy(m_end_of_storage);
				}
			}
		}

		// Return size of allocated storage capacity (public member function)
		size_type capacity() const
		{ return (size_type(m_end_of_storage - m_start)); }

		// Test whether Vector is empty (public member function)
		bool empty() const
		{ return (m_start == m_finish); }

		// Request a change in capacity (public member function)
		void reserve (size_type n)
		{
			if (n > this->max_size())
				std::_throw_length_error("Vector::reserve");
			if (n > this->capacity())
			{
				const size_type	old_size = size();
				pointer			tmp_start = m_alloc.allocate(n);
				pointer			tmp_finish = tmp_start;
				pointer			tmp_end_of_storage = tmp_start + n;
				size_type		i;

				// 새로운 주소값에 데이터 옮기기
				i = 0;
				while (i < old_size)
				{
					m_alloc.construct(tmp_finish, m_start[i]);
					i++;
					tmp_finish++;
				}
				// 원래 주소의 데이터 없애기 destroy() 사용
				clear(m_start);
				// 원래 주소의 소멸
				m_alloc.deallocate(m_start, capacity());
				// 새로운 주소로 저장
				m_start = tmp_start;
				m_finish = tmp_finish;
				m_end_of_storage = temp_end_of_storage;
			}
		}

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
		// Assign Vector content (public member function)
		// range
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);

		// fill
		void assign (size_type n, const value_type& val);

		// Add element at the end (public member function)
		void push_back (const value_type& val);

		// Delete last element (public member function)
		void pop_back();

		// // Insert elements (public member function)
		// // single element
		// iterator insert (iterator position, const value_type& val);

		// // fill
		// void insert (iterator position, size_type n, const value_type& val);

		// // range
		// template <class InputIterator>
		// void insert (iterator position, InputIterator first, InputIterator last);

		// // Erase elements (public member function)
		// iterator erase (iterator position);

		// iterator erase (iteraotr first, iterator last);

		// Swap content (public member function)
		void swap (Vector& x);

		// Clear content (public member function)
		void clear()
		{
			size_type	i = 0;

			while (m_start[i] != m_finish)
			{
				m_alloc.destroy(m_start[i]);
				i++;
			}
			m_finish = m_start;
		}

		/* ALLOCATOR */
		// Get allocator (public member function)
		allocator_type get_allocator() const;

	};	// class Vector

	/* NON-MEMBER FUNCTION OVERLOADS */
	// relational operators for Vector (function template)
	template <class T, class Alloc>
	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

	// Exchange contents of Vectors (function template)
	template <class T, class Alloc>
	void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y);
}	// namespace ft

#endif /* ********************************************************** VECTOR_H */