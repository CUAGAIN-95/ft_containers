/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:22:20 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/04 15:20:10 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory> // allocator 의 header

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		/* MEMBER TYPES */
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef std::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
	
		typedef Alloc									allocator_type;
		typedef allocator_type::reference
	};	//class map
}	// namespace ft

#endif