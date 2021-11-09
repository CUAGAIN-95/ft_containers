/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:20:16 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/09 23:47:25 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>
# include "./pair.hpp"
# include "../iterator/Rb_tree_iterator.hpp"
# include "../iterator/reverse_iterator.hpp"

namespace ft
{
	template < class T >
	struct Rb_tree_iterator;
	template < class T >
	struct Rb_tree_const_iterator;

	enum Rb_tree_color { red = false, black = true };

	template < class Val >
	struct Rb_tree_node
	{
		typedef Rb_tree_node<Val>*				Node_ptr;
		typedef const Rb_tree_node<Val>*	Const_Node_ptr;

		Rb_tree_color	_color;
		Node_ptr		_parent;
		Node_ptr		_left;
		Node_ptr		_right;
		Val				_value_field;

		Rb_tree_node(const Val &x = Val())
		: _color(red), _parent(0), _left(0), _right(0), _value_field(x) {}

		static Node_ptr			minimum(Node_ptr x)
		{
			while (x->_left != 0)
				x = x->_left;
			return (x)
		}

		static Const_Node_ptr	minimum(Const_Node_ptr x)
		{
			while (x->_left != 0)
				x = x->_left;
			return (x)
		}

		static Node_ptr			maximum(Node_ptr x)
		{
			while (x->_right != 0)
				x = x->_right;
			return (x);
		}

		static Const_Node_ptr	maximum(Const_Node_ptr x)
		{
			while (x->_right != 0)
				x = x->_right;
			return (x);
		}
	}; // struct Rb_tree_node

	template < class Val >
	Rb_tree_node<Val>	*Rb_tree_increment(Rb_tree_node<Val> *x)
	{
		if (x->_right)
			return (Rb_tree_node<Val>::minimum(x->_right));
		else
		{
			Rb_tree_node<Val>	*y = x->_parent;
			while (x == y->_right)
			{
				x = y;
				y = y->_parent;
			}
			if (x->_right != y)
				x = y;
		}
		return (x);
	}

	template < class Val >
	const Rb_tree_node<Val>	*Rb_tree_increment(const Rb_tree_node<Val> *x)
	{
		if (x->_right)
			return (Rb_tree_node<Val>::minimum(x->_right));
		else
		{
			Rb_tree_node<Val>	*y = x->_parent;
			while (x == y->_right)
			{
				x = y;
				y = y->_parent;
			}
			if (x->_right != y)
				x = y;
		}
		return (x);
	}

	template < class Val >
	Rb_tree_node<Val>	*Rb_tree_decrement(Rb_tree_node<Val> *x)
	{
		if (x->_color == red && x->_parent->_parent == x)
			x = x->_right;
		else if (x->left != 0)
			return (Rb_tree_node<Val>::maximum(x->_left));
		else
		{
			Rb_tree_node<Val>	*y = x->_parent;
			while (x == y->_left)
			{
				x = y;
				y = y->_parent;
			}
			x = y;
		}
		return (x);
	}

	template < class Val >
	const Rb_tree_node<Val>	*Rb_tree_decrement(const Rb_tree_node<Val> *x)
	{
		if (x->_color == red && x->_parent->_parent == x)
			x = x->_right;
		else if (x->left != 0)
			return (Rb_tree_node<Val>::maximum(x->_left));
		else
		{
			Rb_tree_node<Val>	*y = x->_parent;
			while (x == y->_left)
			{
				x = y;
				y = y->_parent;
			}
			x = y;
		}
		return (x);
	}

	template < class Val >
	void	local_Rb_tree_rotate_left(Rb_tree_node<Val>* const x, \
										Rb_tree_node<Val>*& root)
	{
		Rb_tree_node<Val>* const y = x->_right;
		x->_right = y->_left;
		if (y->_left != 0)
			y->_left->_parent = x;
		y->_parent = x->_parent;

		if (x == root)
			root = y;
		else if (x == x->_parent->_left)
			x->_parent->_left = y;
		else
			x->_parent->_right = y;
		y->_left = x;
		x->_parent = y;
	}

	template < class Val >
	void	local_Rb_tree_rotate_right(Rb_tree_node<Val>* const x, \
										Rb_tree_node<Val>*& root)
	{
		Rb_tree_node<Val>* const y = x->_left;
		x->_left = y->_right;
		if (y->_right != 0)
			y->_right->_parent = x;
		y->_parent = x->_parent;

		if (x == root)
			root = y;
		else if (x == x->_parent->_right)
			x->_parent->_right = y;
		else
			x->_parent->_left = y;
		y->_right = x;
		x->_parent = y;
	}
}	// namespace ft
#endif