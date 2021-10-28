/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_type_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:58:59 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/10/28 22:35:21 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPP_TYPE_TRAITS_HPP
# define CPP_TYPE_TRAITS_HPP

namespace ft
{
	struct __true_type {};
	struct __false_type {};

	template < typename _Tp >
	struct __is_integer
	{
		enum { __value = 0 };
		typedef __false_type	__type;
	};

	template <>
	struct __is_integer<bool>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<char>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<signed char>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<unsigned char>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<short>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<unsigned short>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<int>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<unsigned int>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<long>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<unsigned long>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<long long>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};

	template <>
	struct __is_integer<unsigned long long>
	{
		enum { __value = 1 };
		typedef __true_type		__type;
	};
} // namespace ft

#endif