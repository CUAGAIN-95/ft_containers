/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:39:17 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/10/29 15:07:30 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

# include <memory>	// allocator의 header
# include <cstddef>
# include "./iterator/normal_iterator.hpp"
# include "./iterator/reverse_iterator.hpp"
# include "utils.hpp" // iterator, cpp_type_traits 포함

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		/* MEMBER TYPES */
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef value_type*									pointer;
		typedef const value_type*							const_pointer;
		typedef ft::normal_iterator<pointer, vector>		iterator;
		typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
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
			m_end_of_storage = m_start + n;
			m_finish = m_start;
			while (m_finish != m_end_of_storage)
			{
				m_alloc.construct(&*m_finish, _val);
				m_finish++;
			}
		}
		template < typename InputIterator >
		void	initialize_dispatch(InputIterator first, InputIterator last, __false_type)
		{
			const size_type n = ft::distance(first, last);
			m_start = m_alloc.allocate(n);
			m_end_of_storage = m_start + n;
			m_finish = m_start;
			for (; first != last; m_finish++, first++)
				m_alloc.construct(&*m_finish, *first);
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
						throw std::length_error("vector::insert_dispatch");
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
			for (; first != last; pos++, first++)
				pos = insert(pos, *first);
		}

		// result 위치에 first부터 last까지의 값 copy
		template < class _T >
		_T		uninitialized_copy_a(_T first, _T last, _T result)
		{
			pointer	cur = result;

			for (; first != last; first++, cur++)
				m_alloc.construct(cur, *first);
			return (cur);
		}

		template < class _T>
		void	uninitialized_fill_val(_T *first, _T *last, const _T& val)
		{
			for (; first != last; first++)
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
			for (; first != last; first++)
				*first = val;
		}
		template < class _Size, class _T >
		static _T	*initialized_fill_n_val(_T *first, _Size n, const _T& val)
		{
			initialized_fill_val(first, first + n, val);
			return (first + n);
		}

		template < typename BI1, typename BI2 >
		static BI2 copy_move_back(BI1 first, BI1 last, BI2 result)
		{
			while (first != last)
				*--result = *--last;
			return (result);
		}

		void		erase_at_end(pointer pos)
		{
			pointer	first = pos;

			for (; first != m_finish; first++)
				m_alloc.destroy(first);
			m_finish = pos;
		}

		void	range_check(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector::range_check");
		}

	public:
		/* MEMBER FUNCTIONS */
		// Construct vector (public member function)
		// default
		explicit vector (const allocator_type& alloc = allocator_type())
		:	m_alloc(alloc), m_start(0), m_finish(0), m_end_of_storage(0)
		{}

		// fill
		explicit vector (size_type n, const value_type& val = value_type(),
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
		vector (InputIterator first, InputIterator last, 
				const allocator_type& alloc = allocator_type())
		:	m_alloc(alloc), m_start(0), m_finish(0), m_end_of_storage(0)
		{
			typedef typename ft::__is_integer<InputIterator>::__type _Integral;
			initialize_dispatch(first, last, _Integral());
		}

		// copy
		vector (const vector& x)
		:	m_alloc(x.m_alloc)
		{ initialize_dispatch(x.begin(), x.end(), __false_type()); }

		// vector destructor (public member function)
		~vector()
		{
			clear();
			m_alloc.deallocate(m_start, capacity());
			m_start = 0;
			m_finish = 0;
			m_end_of_storage = 0;
		}

		// Assign content (public member function)
		// copy
		vector& operator= (const vector& x)
		{
			if (this != &x)
				assign(x.begin(), x.end());
			return (*this);
		}

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

		const_reverse_iterator rbegin() const
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
				erase_at_end(m_start + n);
		}

		// Return size of allocated storage capacity (public member function)
		size_type capacity() const
		{ return (size_type(m_end_of_storage - m_start)); }

		// Test whether vector is empty (public member function)
		bool empty() const
		{ return (m_start == m_finish); }

		// Request a change in capacity (public member function)
		void reserve (size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector::reserve");
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
				m_end_of_storage = tmp_end_of_storage;
			}
		}

		/* ELEMENT ACCESS */
		// Access element (public member function)
		reference operator[] (size_type n)
		{ return (*(m_start + n)); }

		const_reference operator[] (size_type n) const
		{ return (*(m_start + n)); }

		// Access element (public member function)
		reference at (size_type n)
		{
			range_check(n);
			return ((*this)[n]);
		}

		const_reference at (size_type n) const
		{
			range_check(n);
			return ((*this)[n]);
		}

		// Access first element (public member function)
		reference front()
		{ return (*begin()); }

		const_reference front() const
		{ return (*begin()); }

		// Access last element (public member function)
		reference back()
		{ return (*(end() - 1)); }

		const_reference back() const
		{ return (*(end() - 1)); }

		/* MODIFIERS */
		// Assign vector content (public member function)
		// range
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			this->clear();
			size_type	n = ft::distance(first, last);
			if (n > capacity())
			{
				m_alloc.deallocate(m_start, capacity());
				m_start = m_alloc.allocate(n);
				m_finish = m_start;
				m_end_of_storage = m_start + n;
			}
			for (; first != last; first++, m_finish++)
				m_alloc.construct(m_finish, *first);
		}

		// fill
		void assign (size_type n, const value_type& val)
		{
			if (n > capacity())
			{
				vector tmp(n, val, m_alloc);
				tmp.swap(*this);
			}
			else if (n > size())
			{
				initialized_fill_val(m_start, m_finish, val);
				m_finish = uninitialized_fill_n_val(m_finish, n - size(), val);
			}
			else
				erase_at_end(initialized_fill_n_val(m_start, n, val));
		}

		// Add element at the end (public member function)
		void push_back (const value_type& val)
		{
			if (m_finish == m_end_of_storage) // 충분한 공간 없음
			{
				size_type len = size() > 0 ? 2 * size() : 1;
				len = (len < size() || len > max_size()) ? max_size() : len;
				reserve(len);
			}
			m_alloc.construct(m_finish, val);
			m_finish++;
		}

		// Delete last element (public member function)
		void pop_back()
		{
			m_finish--;
			m_alloc.destroy(m_finish);
		}

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
		template < class InputIterator >
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			typedef typename ft::__is_integer<InputIterator>::__type	_Integral;
			insert_dispatch(position, first, last, _Integral());
		}

		// Erase elements (public member function)
		iterator erase (iterator position)
		{
			if (position + 1 != end())
			{
				iterator tmp = position;
				while (tmp != end() - 1)
				{
					*tmp = *(tmp + 1);
					tmp++;
				}
			}
			m_finish--;
			m_alloc.destroy(m_finish);
			return (position);
		}

		iterator erase (iterator first, iterator last)
		{
			if (first != last)
			{
				iterator begin = first;
				if (last != end())
				{
					iterator tmp = last;
					while (tmp != end())
					{
						*begin = *tmp;
						begin++;
						tmp++;
					}
				}
				erase_at_end(first.base() + (end() - last));
			}
			return (first);
		}

		// Swap content (public member function)
		void swap (vector& x)
		{
			if (this == &x)
				return ;
			ft::swap(m_alloc, x.m_alloc);
			ft::swap(m_start, x.m_start);
			ft::swap(m_finish, x.m_finish);
			ft::swap(m_end_of_storage, x.m_end_of_storage);
		}

		// Clear content (public member function)
		void clear()
		{ erase_at_end(m_start); }

		/* ALLOCATOR */
		// Get allocator (public member function)
		allocator_type get_allocator() const;
	};	// class vector

	/* NON-MEMBER FUNCTION OVERLOADS */
	// relational operators for vector (function template)
	template < class T, class Alloc >
	inline bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator tmp_lhs = lhs.begin();
		typename ft::vector<T>::const_iterator tmp_rhs = rhs.begin();
		while (tmp_lhs != lhs.end())
		{
			if (tmp_rhs == rhs.end() || *tmp_lhs != *tmp_rhs)
				return (false);
			++tmp_lhs;
			++tmp_rhs;
		}
		return (true);
	}

	template < class T, class Alloc >
	inline bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (!(lhs == rhs)); }
	
	template < class T, class Alloc >
	inline bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	}

	template < class T, class Alloc >
	inline bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (!(rhs < lhs)); }

	template < class T, class Alloc >
	inline bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (rhs < lhs); }
	
	template < class T, class Alloc >
	inline bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (!(lhs < rhs)); }
	
	// Exchange contents of vectors (function template)
	template < class T, class Alloc >
	inline void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }
}	// namespace ft

#endif /* ********************************************************** VECTOR_H */