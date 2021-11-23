/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:20:16 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/23 22:25:25 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "../map/pair.hpp"
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
		typedef const Rb_tree_node<Val>*		Const_Node_ptr;

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
			return (x);
		}

		static Const_Node_ptr	minimum(Const_Node_ptr x)
		{
			while (x->_left != 0)
				x = x->_left;
			return (x);
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
		else if (x->_left != 0)
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
		else if (x->_left != 0)
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
		while (x != root && x->_parent->_color == red)
		{
			Rb_tree_node<Val>* const xpp = x->_parent->_parent;
			if (x->_parent == xpp->_left)
			{
				Rb_tree_node<Val>* const y = xpp->_right;
				if (y && y->_color == red)
				{
					x->_parent->_color = black;
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
				if (y && y->_color == red)
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
			if (leftmost == z)
			{
				if (z->_right == 0)	// z->_left must be null also
					leftmost = z->_parent;
				// makes leftmost == _header if z == root
				else
					leftmost = Rb_tree_node<Val>::minimum(x);	// minimum
			}
			if (rightmost == z)
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
						if (w->_right == 0 || w->_right->_color == black)
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

			// M_copy
			Link_type	clone_tree(Const_Link_type x, Link_type p)
			{
				Link_type	top = clone_node(x);
				top->_parent = p;
				if (x->_right)
					top->_right = clone_tree(right(x), top);
				p = top;
				x = left(x);
				while (x != 0)
				{
					Link_type y = clone_node(x);
					p->_left = y;
					y->_parent = p;
					if (x->_right)
						y->_right = clone_tree(right(x), y);
					p = y;
					x = left(x);
				}
				return (top);
			}

			// M_erase
			void		erase_sub_tree(Link_type x)
			{
				while (x != 0)
				{
					erase_sub_tree(right(x));
					Link_type y = left(x);
					_alloc.destroy(&(x->_value_field));
					_node_alloc.deallocate(x, 1);
					x = y;
				}
			}

			iterator		M_lower_bound(Link_type x, Link_type y, const Key &k)
			{
				while (x != 0)
				{
					if (!_key_compare(key(x), k)) // key(x) >= k x의 키값이 k 보다 크다
					{
						y = x;
						x = left(x);
					}
					else
						x = right(x);
				}
				return (iterator(y));
			}

			const_iterator	M_lower_bound(Const_Link_type x, Const_Link_type y, const Key &k) const
			{
				while (x != 0)
				{
					if (!_key_compare(key(x), k)) // key(x) >= k
					{
						y = x;
						x = left(x);
					}
					else
						x = right(x);
				}
				return (const_iterator(y));
			}

			iterator		M_upper_bound(Link_type x, Link_type y, const Key &k)
			{
				while (x != 0)
				{
					if (_key_compare(k, key(x)))
					{
						y = x;
						x = left(x);
					}
					else
						x = right(x);
				}
				return (iterator(y));
			}

			const_iterator	M_upper_bound(Const_Link_type x, Const_Link_type y, const Key &k) const
			{
				while (x != 0)
				{
					if (_key_compare(k, key(x)))
					{
						y = x;
						x = left(x);
					}
					else
						x = right(x);
				}
				return (const_iterator(y));
			}

			iterator		M_insert(Const_Link_type x, Const_Link_type p, const Val &v)
			{
				bool		insert_left = (x != 0 || p == M_end() || \
										_key_compare(KeyOfVal()(v), key(p)));

				Link_type	z = create_node(v);
				Rb_tree_insert_and_rebalance(insert_left, z, const_cast<Link_type>(p), _header);
				++_node_count;
				return (iterator(z));
			}

		public:
			Rb_tree(const Compare &comp = Compare(), const allocator_type &a = allocator_type())
			: _key_compare(comp), _alloc(a), _node_alloc(Node_allocator(a)), _header(), _node_count(0)
			{ initialize(); }

			Rb_tree(const Rb_tree &x)
			: _key_compare(x._key_compare), _alloc(x._alloc), _node_alloc(Node_allocator(x._alloc)), _header(), _node_count(0)
			{
				initialize();
				if (x.root() != 0) // x 가 빈 tree가 아님
				{
					root() = clone_tree(x.M_begin(), M_end());
					leftmost() = Rb_tree::minimum(root());
					rightmost() = Rb_tree::maximum(root());
					_node_count = x._node_count;
				}
			}

			~Rb_tree()
			{ erase_sub_tree(M_begin()); }

			Rb_tree	&operator=(const Rb_tree &x)
			{
				if (this != &x)
				{
					clear();
					_key_compare = x._key_compare;
					if (x.root() != 0)
					{
						root() = clone_tree(x.M_begin(), M_end());
						leftmost() = Rb_tree::minimum(root());
						rightmost() = Rb_tree::maximum(root());
						_node_count = x._node_count;
					}
				}
				return (*this);
			}

			Compare					key_comp() const
			{ return (_key_compare); }

			iterator				begin()
			{ return (iterator(_header._left)); }

			const_iterator			begin() const
			{ return (const_iterator(_header._left)); }

			iterator				end()
			{ return (iterator(&_header)); }

			const_iterator			end() const
			{ return (const_iterator(&_header)); }

			reverse_iterator		rbegin()
			{ return (reverse_iterator(end())); }

			const_reverse_iterator	rbegin() const
			{ return (const_reverse_iterator(end())); }

			reverse_iterator		rend()
			{ return (reverse_iterator(begin())); }

			const_reverse_iterator	rend() const
			{ return (const_reverse_iterator(begin())); }

			bool					empty() const
			{ return (_node_count == 0); }

			size_type				size() const
			{ return (_node_count); }

			size_type				max_size() const
			{
				const size_type diffmax = std::numeric_limits<difference_type>::max();
				const size_type allocmax = Node_allocator().max_size();
				return (diffmax > allocmax) ? allocmax : diffmax;
			}

			void	swap(Rb_tree &t)
			{
				if (root() == 0) // 현재 tree는 비어있고 t는 비어있지 않음
				{
					if (t.root() != 0)
					{
						root() = t.root();
						leftmost() = t.leftmost();
						rightmost() = t.rightmost();
						root()->_parent = M_end();

						t.root() = 0;
						t.leftmost() = t.M_end();
						t.rightmost() = t.M_end();
					}
				}
				else if (t.root() == 0) // 현재 tree는 비어있지 않고 t는 비어있음
				{
					t.root() = root();
					t.leftmost() = leftmost();
					t.rightmost() = rightmost();
					t.root()->_parent = t.M_end();
					
					root() = 0;
					leftmost() = M_end();
					rightmost() = M_end();
				}
				else // 둘 다 비어있지 않음
				{
					ft::swap(root(), t.root());
					ft::swap(leftmost(), t.leftmost());
					ft::swap(rightmost(), t.rightmost());

					root()->_parent = M_end();
					t.root()->_parent = t.M_end();
				}
				ft::swap(_node_count, t._node_count);
				ft::swap(_key_compare, t._key_compare);
				ft::swap(_alloc, t._alloc);
			}

			pair<iterator,bool>	insert_unique(const value_type &v)
			{
				Link_type	x = M_begin();	// root
				Link_type	y = M_end();	// header
				bool		comp = true;

				while (x != 0)
				{
					y = x;
					comp = _key_compare(KeyOfVal()(v), key(x));	// key(v) < key(x)
					x = comp ? left(x) : right(x);
				}
				iterator	j = iterator(y);	// y : x->_parent
				if (comp)	// x = left(x)
				{
					if (j == begin())
						return (pair<iterator,bool>(M_insert(x, y, v), true));	// y 왼쪽에 insert
					else
						--j;	// decrement
				}
				if (_key_compare(key(j._node), KeyOfVal()(v)))
					return (pair<iterator,bool>(M_insert(x, y, v), true));
				return (pair<iterator,bool>(j, false));
			}

			iterator			insert_unique(const_iterator position, const value_type &v)
			{
				if (position._node == M_end()) // position == header
				{
					if (size() > 0 && _key_compare(key(rightmost()), KeyOfVal()(v)))
						return (M_insert(0, rightmost(), v));
					else
						return (insert_unique(v).first);
				}
				else if (_key_compare(KeyOfVal()(v), key(position._node)))
				{
					const_iterator	before = position;
					if (position._node == leftmost())
						return (M_insert(leftmost(), leftmost(), v));
					else if (_key_compare(key((--before)._node), KeyOfVal()(v)))
					{
						if (right(before._node) == 0)
							return (M_insert(0, before._node, v));
						else
							return (M_insert(position._node, position._node, v));
					}
					else
						return (insert_unique(v).first);
				}
				else if (_key_compare(key(position._node), KeyOfVal()(v)))
				{
					const_iterator	after = position;
					if (position._node == rightmost())
						return (M_insert(0, rightmost(), v));
					else if (_key_compare(KeyOfVal()(v), key((++after)._node)))
					{
						if (right(position._node) == 0)
							return (M_insert(0, position._node, v));
						else
							return (M_insert(after._node, after._node, v));
					}
					else
						return (insert_unique(v).first);
				}
				else
					return (iterator(const_cast<typename iterator::Link_type>(position._node)));
			}

			template < class InputIterator >
			void		insert_unique(InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
					insert_unique(end(), *first);
			}

			size_type	erase(const key_type &x)
			{
				iterator	equal = find(x);
				if (equal == end())
					return (0);
				erase(equal);
				return (1);
			}

			void		erase(iterator position)
			{
				Link_type y = Rb_tree_rebalance_for_erase(position._node, _header);
				_alloc.destroy(&(y->_value_field));
				_node_alloc.deallocate(y, 1);
				--_node_count;
			}

			void		erase(iterator first, iterator last)
			{
				if (first == begin() && last == end())
					clear();
				else
				{
					while (first != last)
						erase(first++);
				}
			}

			void		clear()
			{
				erase_sub_tree(M_begin());
				leftmost() = M_end();
				root() = 0;
				rightmost() = M_end();
				_node_count = 0;
			}

			iterator		find(const key_type &k)
			{
				iterator	j = M_lower_bound(M_begin(), M_end(), k);
				return ((j == end() || _key_compare(k, key(j._node))) ? end() : j);
			}

			const_iterator	find(const key_type &k) const
			{
				const_iterator	j = M_lower_bound(M_begin(), M_end(), k);
				return ((j == end() || _key_compare(k, key(j._node))) ? end() : j);
			}

			iterator		lower_bound(const key_type &k)
			{ return (M_lower_bound(M_begin(), M_end(), k)); }

			const_iterator	lower_bound(const key_type &k) const
			{ return (M_lower_bound(M_begin(), M_end(), k)); }

			iterator		upper_bound(const key_type &k)
			{ return (M_upper_bound(M_begin(), M_end(), k)); }

			const_iterator	upper_bound(const key_type &k) const
			{ return (M_upper_bound(M_begin(), M_end(), k)); }

			template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
			friend bool		operator==(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &x, \
										const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &y)
			{
				if (x.size() != y.size())
					return false;
				const_iterator it1 = x.begin();
				const_iterator it2 = y.begin();
				while (it1 != x.end())
				{
					if (*it1 != *it2)
						return false;
					++it1;
					++it2;
				}
				return true;
			}

			template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
			friend bool		operator< (const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &x, \
										const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &y)
			{ return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end())); }

			template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
			friend bool		operator!=(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &x, \
										const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &y)
			{ return (!(x == y)); }

			template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
			friend bool		operator>(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &x, \
										const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &y)
			{ return (y < x); }

			template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
			friend bool		operator<=(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &x, \
										const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &y)
			{ return (!(y < x)); }

			template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
			friend bool		operator>=(const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &x, \
										const Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &y)
			{ return (!(x < y)); }
	};	// class Rb_tree
}	// namespace ft
#endif