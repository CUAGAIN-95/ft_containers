/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:08:58 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/06/29 14:39:51 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <string>

# include <memory>	// allocator의 header

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class list
	{
	public:
		/* MEMBER TYPES */
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;

		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;
	};	// class list
}	// namespace ft

#endif /* ************************************************************ LIST_H */