/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:39:17 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/10/12 04:27:57 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

# include <memory>	// allocator의 header
# include <cstddef>
# include "./iterator/Iterator.hpp"	// iterator/Iterator.hpp

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
	public:
		/* MEMBER TYPES */
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef value_type*									pointer;
		typedef const value_type*							const_pointer;
		typedef ft::normal_iterator<pointer, Vector>		iterator;
		typedef ft::normal_iterator<const_pointer, Vector>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

	protected:
		allocator_type	m_alloc;
		pointer			m_start;
		pointer			m_finish;
		pointer			m_end_of_storage;

		// allocate와 동시에 초기화하는 함수
		template < typename Integer >
		void	initialize_dispatch(Integer _n, Integer _val, __true_type)
		{
			size_type	n = static_cast<size_type>(_n);
			m_start = m_alloc.allocate(n);
		}
		// 해당 position에 값을 insert하는 함수
		template < typename Size, typename Val >
		void	insert_dispatch(iterator position, Size _n, Val _val, __true_type)
		{
			size_type n = static_cast<size_type>(_n);
			value_type val = static_cast<value_type>(_val);
			if (n != 0)
			{
				if (size_type(m_end_of_storage - m_finish) >= n) // 기존 메모리 자리가 있는가
				{
					const size_type elems_after = end() - position; // 뒤로 미뤄야하는 데이터 개수
					pointer old_finish(m_finish);
					if (elems_after > n)
					{
						m_finish = uninitialized_copy_a(m_finish - n, m_finish, m_finish);
						copy_move_back(position.base(), old_finish - n, old_finish);
						initialized_fill_n_val(position.base(), n, val);
					}
					else
					{
						m_finish = uninitialized_fill_n_val(m_finish, n - elems_after, val);
						m_finish = uninitialized_copy_a(position.base(), old_finish, m_finish);
						initialized_fill_n_val(position.base(), elems_after, val);
					}
				}
				else // 자리 부족
				{
					if (max_size() - size() < n)
						throw std::length_error("Vector::insert_dispatch");
					size_type	len = size() + (size() > n ? size() : n); // 2배 또는 n
					len = (len < size() || len > max_size()) ? max_size() : len;
					pointer		new_start = m_alloc.allocate(len);
					pointer		new_finish = new_start;
					
					// position 이전 값들 copy
					new_finish = uninitialized_copy_a(m_start, position.base(), new_start);
					// insert
					new_finish = uninitialized_fill_n_val(new_finish, n, val);
					// position 이후 값들 copy
					new_finish = uninitialized_copy_a(position.bace(), m_finish, new_finish);
					clear();
					m_alloc.deallocate(m_start, capacity());
					m_start = new_start;
					m_finish = new_finish;
					m_end_of_storage = new_start + len;
				}
			}
		}

		template < typename InputIterator >
		void	insert_dispatch(iterator pos, InputIterator first, InputIterator last, __false_type)
		{
			for (; first != last; ++pos, ++first)
				pos = insert(pos, *first);
		}

		// result 위치에 first부터 last까지의 값 copy
		template < class _T >
		_T		uninitialized_copy_a(_T first, _T last, _T result)
		{
			pointer	cur = result;

			for (; first != last; ++first, ++cur)
				m_alloc.construct(cur, *first);
			return (cur);
		}

		template < class _T>
		void	uninitialized_fill_val(_T *first, _T *last, const _T& val)
		{
			for (; first != last; ++first)
				m_alloc.construct(first, val);
		}
		template < class _Size, class _T >
		_T		*uninitialized_fill_n_val(_T *first, _Size n, const _T& val)
		{
			uninitialized_fill_val(first, first + n, val);
			return (first + n);
		}

		template < class _T >
		static void	initialized_fill_val(_T *first, _T *last, const _T& val)
		{
			for (; first != last; ++first)
				*first = val;
		}
		template < class _Size, class _T >
		static _T	*initialized_fill_n_val(_T *first, _Size n, const _T& val)
		{
			initialized_fill_val(first, first + n, val);
			return (first + n);
		}
		
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
				const allocator_type& alloc = allocator_type())
		:	m_alloc(alloc), m_start(0), m_finish(0), m_end_of_storage(0)
		{
			typedef typename ft::__is_interger<InputIterator>::__type _Integral;
			initialize_dispatch(first, last, _Integral());
		}

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

		/* ITERATORS */
		// Return iterator to beginning (public member function)
		iterator begin()
		{ return (iterator(m_start)); }

		const_iterator begin() const
		{ return (const_iterator(m_start)); }

		// Return iterator to end (public member function)
		iterator end()
		{ return (iterator(m_finish)); }

		const_iterator end() const
		{ return (const_iterator(m_finish)); }

		// Return reverse iterator to reverse beginning (public member function)
		reverse_iterator rbegin()
		{ return (reverse_iterator(end())); }

		const_reverse_iteratotr rbegin() const
		{ return (const_reverse_iterator(end())); }

		// Return reverse iterator to reverse end (public member function)
		reverse_iterator rend()
		{ return (reverse_iterator(begin())); }

		const_reverse_iterator rend() const
		{ return (const_reverse_iterator(begin())); }

		/* CAPACITY */
		// Return size (public member function)
		size_type size() const
		{ return (size_type(m_finish - m_start)); }

		// Return maximum size (public member function)
		size_type max_size() const
		{ return (m_alloc.max_size()); }

		// Change size (public member function)
		void resize (size_type n, value_type val = value_type())
		{
			// 에러 처리 (n이 max_size보다 클 때)
			if (n > max_size())
				throw std::length_error("vector::resize");
			// 기본 사이즈보다 새로운 사이즈가 클 때
			if (n > size())
				insert(this->end(), n - size(), val);
			// 기본 사이즈보다 새로운 사이즈가 작을 때
			else if (n < size())
			{
				while (size() > n)
				{
					--m_finish;
					m_alloc.destroy(m_finish);
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
			if (n > max_size())
				throw std::length_error("Vector::reserve");
			if (n > capacity())
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
				clear();
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

		// Insert elements (public member function)
		// single element
		iterator insert (iterator position, const value_type& val)
		{
			const size_type	n = position - begin();
			// position이 빈 공간일때
			if (m_finish != m_end_of_storage && position == end())
			{
				m_alloc.construct(m_finish, val);
				++m_finish;
			}
			// position에 데이터가 있거나 메모리 할당이 안되어있을때
			else
				insert_dispatch(position, 1, val, __true_type());
			return (iterator(m_start + n));
		}
	
		// fill
		void insert (iterator position, size_type n, const value_type& val)
		{ m_fill_insert(position, n, val); }

		// range
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			typedef typename ft::__is_integer<InputIterator>::__type	_Integral;
			insert_dispatch(position, first, last, _Integral());
		}

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