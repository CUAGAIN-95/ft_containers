/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:03:48 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/21 19:54:28 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"

namespace	ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		/* MEMBER TYPES */
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
		
	protected:
		container_type		c;

	public:
		/* MEMBER FUNCTIONS */
		// Construct stack (public member function)
		explicit	stack(const container_type& ctnr = container_type())
		:	c(ctnr) {}

		// Test whether container is empty (public member function)
		bool		empty() const
		{ return (c.empty()); }

		// Return size (public member function)
		size_type	size() const
		{ return (c.size()); }

		// Access next element (public member function)
		value_type&	top()
		{ return (c.back()); }

		const value_type&	top() const
		{ return (c.back()); }

		// Insert element (public member function)
		void		push(const value_type& val)
		{ c.push_back(val); }

		// Remove top element (public member function)
		void		pop()
		{ c.pop_back(); }

		/* NON-MEMBER FUNCTION OVERLOADS */
		// Relational operators for stack (function)
		template <class _T, class _Container>
		friend bool operator == (const ft::stack<_T,_Container>& lhs, \
								const ft::stack<_T,_Container>& rhs)
		{ return (lhs.c == rhs.c); }

		template <class _T, class _Container>
		friend bool operator != (const ft::stack<_T,_Container>& lhs, \
								const ft::stack<_T,_Container>& rhs)
		{ return (!(lhs == rhs)); }

		template <class _T, class _Container>
		friend bool operator <  (const ft::stack<_T,_Container>& lhs, \
								const ft::stack<_T,_Container>& rhs)
		{ return (lhs.c < rhs.c); }

		template <class _T, class _Container>
		friend bool operator <= (const ft::stack<_T,_Container>& lhs, \
								const ft::stack<_T,_Container>& rhs)
		{ return (!(rhs < lhs)); }

		template <class _T, class _Container>
		friend bool operator >  (const ft::stack<_T,_Container>& lhs, \
								const ft::stack<_T,_Container>& rhs)
		{ return (rhs < lhs); }

		template <class _T, class _Container>
		friend bool operator >= (const ft::stack<_T,_Container>& lhs, \
								const ft::stack<_T,_Container>& rhs)
		{ return (!(lhs < rhs)); }
	};	// class stack
}	// namespace ft
#endif /* *********************************************************** STACK_H */