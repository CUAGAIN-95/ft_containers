/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:32:22 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/16 14:56:00 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "./cpp_type_traits.hpp"

namespace	ft
{
	template < class InputIterator >
	ptrdiff_t	distance(InputIterator first, InputIterator last)
	{
		ptrdiff_t n = 0;
		while (first != last)
		{
			n++;
			first++;
		}
		return (n);
	}

	template < class T >
	void	swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}


	template < class II1, class II2 >
	bool	equal(II1 first1, II1 last1, II2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != first2)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	// II = InputIterator
	template < class II1, class II2>
	bool	lexicographical_compare(II1 first1, II1 last1, II2 first2, II2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	/*
	**	=======================================================================
	*/

	template < class Arg, class Result >
	struct unary_function
	{
		typedef Arg		argument_type;
		typedef Result	result_type;
	};

	template < class Pair >
	struct Select1st: public unary_function<Pair, typename Pair::first_type >
	{
		typename Pair::first_type &operator()(Pair &x) const
		{ return (x.first); }

		const typename Pair::first_type &operator()(const Pair &x) const
		{ return (x.first); }
	};

	template < class Arg1, class Arg2, class Result >
	struct binary_function
	{
		typedef Arg1		first_argument_type;
		typedef Arg2		seconde_argument_type;
		typedef Result		result_type;
	};

	template < class T >
	struct less: public binary_function<T,T,bool>
	{
		bool operator() (const T &x, const T &y) const
		{ return (x < y); }
	};
}
#endif