/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:11:55 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/21 18:19:27 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include "../utils/utils.hpp"

namespace ft
{
	template < class T1, class T2 >
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;
		
		T1			first;
		T2			second;

		pair()
		: first(), second() {}

		pair(const T1 &a, const T2 &b)
		: first(a), second(b) {}

		template < class U1, class U2 >
		pair(const pair<U1, U2> &p)
		: first(p.first), second(p.second) {}

		pair(const pair &p)
		: first(p.first), second(p.second) {}

		~pair() {}

		template < class U1, class U2 >
		pair& operator= (pair<U1, U2> &p)
		{
			first = p.first;
			second = p.second;
			return (*this);
		}

		void	swap(pair &p)
		{
			swap(first, p.first);
			swap(second, p.second);
		}
	};	// struct pair

	template < class T1, class T2 >
	bool	operator== (const pair<T1, T2> &x, const pair<T1, T2> &y)
	{ return (x.first == y.first && x.second == y.second); }

	template < class T1, class T2 >
	bool	operator<  (const pair<T1, T2> &x, const pair<T1, T2> &y)
	{ return (x.first < y.first || (y.first <= x.first && x.second < y.second)); }

	template < class T1, class T2 >
	bool	operator!= (const pair<T1, T2> &x, const pair<T1, T2> &y)
	{ return (!(x == y)); }

	template < class T1, class T2 >
	bool	operator>  (const pair<T1, T2> &x, const pair<T1, T2> &y)
	{ return (y < x); }

	template < class T1, class T2 >
	bool	operator<= (const pair<T1, T2> &x, const pair<T1, T2> &y)
	{ return (!(y < x)); }

	template < class T1, class T2 >
	bool	operator>= (const pair<T1, T2> &x, const pair<T1, T2> &y)
	{ return (!(x < y)); }

	template < class T1, class T2 >
	void	swap(pair<T1, T2> &x, pair<T1, T2> &y)
	{ x.swap(y); }

	template < class T1, class T2 >
	pair<T1, T2>	make_pair(T1 x, T2 y)
	{ return (pair<T1, T2>(x, y)); }
}	// namespace ft

#endif