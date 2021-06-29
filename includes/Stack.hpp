/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:03:48 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/06/29 14:40:16 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <string>


// list, vector를 만들기 전에 default container로 사용
# include <deque>

namespace	ft
{
	template <class T, class Container = std::deque<T> >
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
	};	// class stack

	/* NON-MEMBER FUNCTION OVERLOADS */
	// Relational operators for stack (function)
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs == rhs); }

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs != rhs); }

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs < rhs); }

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs <= rhs); }

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs > rhs); }

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs >= rhs); }
}	// namespace ft
#endif /* *********************************************************** STACK_H */