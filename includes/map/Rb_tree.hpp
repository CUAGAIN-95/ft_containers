/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:20:16 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/14 13:15:44 by yeonhlee         ###   ########.fr       */
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

	template < class Val >
	void	Rb_tree_insert_and_rebalance(const bool insert_left, \
										Rb_tree_node<Val> *x, Rb_tree_node<Val> *p, \
										Rb_tree_node<Val> &_header)
	{
		Rb_tree_node<Val> *&root = _header._parent;
		x->_parent = p;
		x->_left = 0;
		x->_right = 0;
		x->_color = red;
		// insert
		if (insert_left)
		{
			p->_left = x;
			if (p == &_header)
			{
				_header._parent = x;
				_header._right = x;
			}
			else if (p == _header._left)
				_header._left = x;
		}
		else
		{
			p->_right = x;
			if (p == _header._right)
				_header._right = x;
		}
		// rebalance
		while (x != root && x->_parent->color == red)
		{
			Rb_tree_node<Val>* const xpp = x->_parent->_parent;
			if (x->_parent == xpp->_left)
			{
				Rb_tree_node<Val>* const y = xpp->_right;
				if (y && y->_color == red)
				{
					x->_parent->color = black;
					y->_color = black;
					xpp->_color = red;
					x = xpp;
				}
				else
				{
					if (x == x->_parent->_right)
					{
						x = x->_parent;
						local_Rb_tree_rotate_left(x, root);
					}
					x->_parent->_color = black;
					xpp->_color = red;
					local_Rb_tree_rotate_right(x, root);
				}
			}
			else
			{
				Rb_tree_node<Val>* const y = xpp->_left;
				if (y && y->color == red)
				{
					x->_parent->_color = black;
					y->_color = black;
					xpp->_color = red;
					x = xpp;
				}
				else
				{
					if (x == x->_parent->_left)
					{
						x = x->_parent;
						local_Rb_tree_rotate_right(x, root);
					}
					x->_parent->_color = black;
					xpp->_color = red;
					local_Rb_tree_rotate_left(xpp, root);
				}
			}
		}
		root->_color = black;
	}

	template < class Val >
	Rb_tree_node<Val>	*Rb_tree_rebalance_for_erase(Rb_tree_node<Val> *z, \
													Rb_tree_node<Val> &_header)
	{
		Rb_tree_node<Val>	*&root = _header._parent;
		Rb_tree_node<Val>	*&leftmost = _header._left;
		Rb_tree_node<Val>	*&rightmost = _header._right;
		Rb_tree_node<Val>	*y = z;
		Rb_tree_node<Val>	*x = 0;
		Rb_tree_node<Val>	*x_parent = 0;

		if (y->_left == 0)			// z has at most one non-null child y == z
			x = y->_right;			// x might be null
		else if (y->_right == 0)	// z has exactly one non-null child y == z
			x = y->_left;			// x is not null
		else						// z has two non-null children
		{
			y = y->_right;			// z's successor. x might be null
			while (y->_left != 0)
				y = y->_left;
			x = y->_right;
		}

		if (y != z)					// relink y in place of z. y is z's successor
		{
			z->_left->_parent = y;
			y->_left = z->_left;
			if (y != z->_right)
			{
				x_parent = y->_parent;
				if (x)
					x->_parent = y->_parent;
				y->_parent->_left = x;	// y must be a child of _left
				y->_right = z->_right;
				z->_right->_parent = y;
			}
			else
				x_parent = y;
			if (root == z)
				root = y;
			else if (z->_parent->_left == z)
				z->_parent->_left = y;
			else
				z->_parent->_right = y;
			y->_parent = z->_parent;
			ft::swap(y->_color, z->_color);
			y = z;
			// y now points to node to be actually deleted
		}
		else						// y == z
		{
			x_parent = y->_parent;
			if (x)
				x->_parent = y->_parent;
			if (root == z)
				root = x;
			else if (z->_parent->_left == z)
				z->_parent->_left = x;
			else
				z->_parent->_right = x;
			if (leftmost == 0)
			{
				if (z->_right == 0)	// z->_left must be null also
					leftmost = z->_parent;
				// makes leftmost == _header if z == root
				else
					leftmost = Rb_tree_node<Val>::minimum(x);	// minimum
			}
			if (rigtmost == 0)
			{
				if (z->_left == 0)	// z->_right must be null also
					rightmost = z->_parent;
				// makes rightmost == _header if z == root
				else				// x == z->_left
					rightmost = Rb_tree_node<Val>::maximum(x);
			}
		}
		if (y->_color != red)
		{
			while (x != root && (x == 0 || x->_color == black))
			{
				if (x == x_parent->_left)
				{
					Rb_tree_node<Val>	*w = x_parent->_right;
					if (w->_color == red)
					{
						w->_color = black;
						x_parent->_color = red;
						local_Rb_tree_rotate_left(x_parent, root);
						w = x_parent->_right;
					}
					if ((w->_left == 0 || w->_left->_color == black) && \
						(w->_right == 0 || w->_right->_color == black))
					{
						w->_color = red;
						x = x_parent;
						x_parent = x_parent->_parent;
					}
					else
					{
						if (w->_right == 0 || w->right->_color == black)
						{
							w->_left->_color = black;
							w->_color = red;
							local_Rb_tree_rotate_right(w, root);
							w = x_parent->_right;
						}
						w->_color = x_parent->_color;
						x_parent->_color = black;
						if (w->_right)
							w->_right->_color = black;
						local_Rb_tree_rotate_left(x_parent, root);
						break ;
					}
				}
				else
				{
					// same as above, with _right <-> _left
					Rb_tree_node<Val>	*w = x_parent->_left;
					if (w->_color == red)
					{
						w->_color = black;
						x_parent->_color = red;
						local_Rb_tree_rotate_right(x_parent, root);
						w = x_parent->_left;
					}
					if ((w->_right == 0 || w->_right->_color == black) && \
						(w->_left == 0 || w->_left->_color == black))
					{
						w->_color = red;
						x = x_parent;
						x_parent = x_parent->_parent;
					}
					else
					{
						if (w->_left == 0 || w->_left->_color == black)
						{
							w->_right->_color = black;
							w->_color = red;
							local_Rb_tree_rotate_left(w, root);
							w = x_parent->_left;
						}
						w->_color = x_parent->_color;
						x_parent->_color = black;
						if (w->_left)
							w->_left->_color = black;
						local_Rb_tree_rotate_right(x_parent, root);
						break ;
					}
				}
			}
			if (x)
				x->_color = black;
		}
		return y;
	}

	template < typename Key, typename Val, typename KeyOfVal, typename Compare, typename Alloc = std::allocator<Val> >
	class Rb_tree
	{
		typedef typename Alloc::template rebind<Rb_tree_node<Val> >::other	Node_allocator;
		public:
			typedef Key										key_type;
			typedef Val										value_type;
			typedef value_type								*pointer;
			typedef const value_type						*const_pointer;
			typedef value_type								&reference;
			typedef const value_type						&const_reference;
			typedef Rb_tree_node<Val>						*Link_type;
			typedef const Rb_tree_node<Val>					*Const_Link_type;
			typedef size_t									size_type;
			typedef ptrdiff_t								difference_type;
			typedef Alloc									allocator_type;

			typedef ft::Rb_tree_iterator<value_type>		iterator;
			typedef ft::Rb_tree_const_iterator<value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		protected:
			Compare				_key_compare;
			allocator_type		_alloc;
			Node_allocator		_node_alloc;
			Rb_tree_node<Val>	_header;
			size_type			_node_count;		//keeps track of size of tree

			Link_type			create_node(const value_type &x)
			{
				Link_type	tmp = _node_alloc.allocate(1);
				_alloc.construct(&(tmp->_value_field), x);
				return (tmp);
			}

			Link_type			clone_node(Const_Link_type x)
			{
				Link_type	tmp = create_node(x->_value_field);
				tmp->_color = x->_color;
				tmp->_parent = 0;
				tmp->_left = 0;
				tmp->_right = 0;
				return (tmp);
			}

			Link_type				&root()
			{ return (_header._parent); }

			Const_Link_type			root() const
			{ return (_header._parent); }

			Link_type				&leftmost()
			{ return (_header._left); }

			Const_Link_type			leftmost() const
			{ return (_header._left); }

			Link_type				&rightmost()
			{ return (_header._right); }

			Const_Link_type			rightmost() const
			{ return (_header._right); }

			Link_type				M_begin()
			{ return (_header._parent); }

			Const_Link_type			M_begin() const
			{ return (_header._parent); }

			Link_type				M_end()
			{ return (&_header); }

			Const_Link_type			M_end() const
			{ return (&_header); }

			static const_reference	value(Const_Link_type x)
			{ return (x->_value_field); }

			static const Key		&key(Const_Link_type x)
			{ return (KeyOfVal()(value(x))); }

			static Link_type		left(Link_type x)
			{ return (x->_left); }

			static Const_Link_type	left(Const_Link_type x)
			{ return (x->_left); }

			static Link_type		right(Link_type x)
			{ return (x->_right); }

			static Const_Link_type	right(Const_Link_type x)
			{ return (x->_right); }

			static Link_type		minimum(Link_type x)
			{ return (Rb_tree_node<Val>::minimum(x)); }

			static Const_Link_type	minimum(Const_Link_type x)
			{ return (Rb_tree_node<Val>::minimum(x)); }

			static Link_type		maximum(Link_type x)
			{ return (Rb_tree_node<Val>::maximum(x)); }

			static Const_Link_type	maximum(Const_Link_type x)
			{ return (Rb_tree_node<Val>::maximum(x)); }

		private:
			void	initialize()
			{
				_header._color = red;
				_header._parent = 0;
				_header._left = &_header;
				_header._right = &_header;
			}
	};	// class Rb_tree
}	// namespace ft
#endif