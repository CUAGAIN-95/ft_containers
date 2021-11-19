/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:38:54 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/19 16:48:56 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

# include "map/map.hpp"
# include "map/Rb_tree.hpp"
# include "iterator_base_types.hpp"

namespace ft
{
	template < class Val >
	struct Rb_tree_node;

	template < class T >
	struct Rb_tree_iterator
	{
		typedef T								value_type;
		typedef T								&reference;
		typedef T								*pointer;

		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef Rb_tree_iterator<T>				Self;
		typedef Rb_tree_node<T>					*Link_type;

		Link_type	_node;

		Rb_tree_iterator()
		: _node() {}

		explicit Rb_tree_iterator(Link_type x)
		: _node(x) {}

		reference operator*() const
		{ return (_node->_value_field); }

		pointer operator->() const
		{ return (&(_node->_value_field)); }

		Self&	operator++()
		{
			_node = Rb_tree_increment(_node);
			return (*this);
		}

		Self	operator++(int)
		{
			Self	tmp = *this;
			_node = Rb_tree_increment(_node);
			return (tmp);
		}

		Self&	operator--()
		{
			_node = Rb_tree_decrement(_node);
			return (*this);
		}

		Self	operator--(int)
		{
			Self	tmp = *this;
			_node = Rb_tree_decrement(_node);
			return (tmp);
		}

		bool	operator==(const Self &x) const
		{ return (_node == x._node); }

		bool	operator!=(const Self &x) const
		{ return (_node != x._node); }
	}; // struct Rb_tree_iterator

	template < class T >
	struct Rb_tree_const_iterator
	{
		typedef T								value_type;
		typedef const T							&reference;
		typedef const T							*pointer;

		typedef Rb_tree_iterator<T>				iterator;

		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t						difference_type;

		typedef Rb_tree_const_iterator<T>		Self;
		typedef Rb_tree_node<T>					*Link_type;

		Link_type	_node;

		Rb_tree_const_iterator()
		: _node() {}

		explicit Rb_tree_const_iterator(Link_type x)
		: _node(x) {}

		Rb_tree_const_iterator(const iterator &it)
		: _node(it._node) {}

		reference operator*() const
		{ return (_node->_value_field); }

		pointer operator->() const
		{ return (&(_node->_value_field)); }

		Self&	operator++()
		{
			_node = Rb_tree_increment(_node);
			return (*this);
		}

		Self	operator++(int)
		{
			Self	tmp = *this;
			_node = Rb_tree_increment(_node);
			return (tmp);
		}

		Self&	operator--()
		{
			_node = Rb_tree_decrement(_node);
			return (*this);
		}

		Self	operator--(int)
		{
			Self	tmp = *this;
			_node = Rb_tree_decrement(_node);
			return (tmp);
		}

		bool	operator==(const Self &x) const
		{ return (_node == x._node); }

		bool	operator!=(const Self &x) const
		{ return (_node != x._node); }
	}; // struct Rb_tree_const_iterator

	template < class Val >
	inline bool		operator==(const Rb_tree_iterator<Val> &x,
								const Rb_tree_const_iterator<Val> &y)
	{ return (x._node == y._node); }

	template < class Val >
	inline bool		operator!=(const Rb_tree_iterator<Val> &x,
								const Rb_tree_const_iterator<Val> &y)
	{ return (x._node != y._node); }
} // namespace ft

#endif