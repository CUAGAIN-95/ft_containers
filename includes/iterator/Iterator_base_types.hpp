/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_base_types.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:03:54 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/09/03 17:17:33 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_BASE_TYPES_HPP
# define ITERATOR_BASE_TYPES_HPP

#include <cstddef>

namespace ft
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <typename Category, typename T, typename Distance = ptrdiff_t, \
				typename Pointer = T*, typename Reference = T&>
	struct Iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	}; // struct Iterator

	template<typename Iterator>
	struct Iterator_traits
	{
		typedef typename	Iterator::iterator_category	iterator_category;
		typedef typename	Iterator::value_type		value_type;
		typedef typename	Iterator::difference_type	difference_type;
		typedef typename	Iterator::pointer			pointer;
		typedef typename	Iterator::reference			reference;
	}; // struct Iterator_traits

	template<typename T>
	struct Iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	}; // struct Iterator_traits<T*>

	template<typename T>
	struct Iterator_traits<const T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	}; // struct iterator_traits<const T*>

	template <typename Iterator, bool HasBase>
	struct Iter_base
	{
		typedef Iterator		iterator_type;
		static iterator_type	S_base(Iterator __it)
		{ return (__it); }
	}; // struct Iter_base

	template <typename _Iterator>
	struct Iter_base<_Iterator, true> 
	{
		typedef typename Iterator::iterator_type	iterator_type;
		static iterator_type S_base(Iterator __it)
		{ return (__it.base()); }
	}; // struct Iter_base
} // namespace ft
#endif