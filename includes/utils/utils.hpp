/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:32:22 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/08 06:00:41 by yeonhlee         ###   ########.fr       */
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
	struct binary_function
	{
		typedef Arg		argument_type;
		typedef Result	result_type;
	};
}
#endif