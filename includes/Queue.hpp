/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:10:45 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/06/24 06:10:22 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <iostream>
# include <string>


// list, vector를 만들기 전에 default container로 사용
# include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class queue
	{
		private:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type		c;

		public:
			/* MEMBER FUNCTIONS */
			// Construct queue (public member function)
			explicit	queue(const container_type& ctnr = container_type())
			:	c(ctnr) {}

			// Test whether container is empty (public member function)
			bool		empty() const
			{ return (c.empty()); }

			// Return size (public member function)
			size_type	size() const
			{ return (c.size()); }

			// Access next element (public member function)
			value_type&	front()
			{ return (c.front()); }

			const value_type&	front() const
			{ return (c.front()); }

			// Access last elemet (public member function)
			value_type& back()
			{ return (c.back()); }

			const value_type&	back() const
			{ return (c.back()); }

			// Insert element (public member function)
			void		push(const value_type& val)
			{ c.push_back(val); }

			// Remove next element (public member function)
			void		pop()
			{ c.pop_front(); }
	};

	/* NON-MEMBER FUNCTION OVERLOADS */
	// Relational operators for queue (function)
	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{ return (lhs == rhs); }

	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{ return (lhs != rhs); }

	template <class T, class Container>
	bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{ return (lhs < rhs); }

	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{ return (lhs <= rhs); }

	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{ return (lhs > rhs); }

	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{ return (lhs >= rhs); }
}

#endif /* *********************************************************** QUEUE_H */