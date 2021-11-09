/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:22:20 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/08 20:18:07 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory> // allocator 의 header
# include "./pair.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		/* MEMBER TYPES */
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef std::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		
		class value_compare
		: public ft::binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare, Alloc>;
			protected:
				bool operator() (const value_type &x, const value_type &y) const
				{ return (comp(x.first, y.first)); }
		};	// class value_compare

	private:
		// This turns a red-black tree into a [multi]map.
		typedef typename Alloc::template rebind<value_type>::other	Pair_alloc_type;
		typedef Rb_tree<key_type, value_type, Sellect1st<value_type>, key_compare, Pair_alloc_type>	Rep_type;
		Rep_tree	_tree;
	};	//class map
}	// namespace ft

#endif