/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:22:20 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/15 02:28:09 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory> // allocator 의 header
# include "./pair.hpp"

namespace ft
{
	template < typename Key, typename Val, typename KeyOfVal, typename Compare, typename Alloc >
	class Rb_tree;
	template < class T >
	struct Rb_tree_iterator;
	template < class T >
	struct Rb_tree_const_iterator;
	
	template < class Key, class T, class Compare = ft::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		/* MEMBER TYPES */
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		
		class value_compare
		: public ft::binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare, Alloc>;

			protected:
				Compare		comp;
				value_compare(Compare c)
				: comp(c) {}

			public:
				bool operator() (const value_type &x, const value_type &y) const
				{ return (comp(x.first, y.first)); }
		};	// class value_compare

	private:
		// This turns a red-black tree into a [multi]map.
		typedef typename Alloc::template rebind<value_type>::other	Pair_alloc_type;
		typedef Rb_tree<key_type, value_type, Sellect1st<value_type>, key_compare, Pair_alloc_type>	Rep_type;
		Rep_type	_tree;

	public:
		typedef typename Pair_alloc_type::pointer			pointer;
		typedef typename Pair_alloc_type::const_pointer		const_pointer;
		typedef typename Pair_alloc_type::reference			reference;
		typedef typename Pair_alloc_type::const_reference	const_reference;
		typedef typename Rep_type::iterator					iterator;
		typedef typename Rep_type::const_iterator			const_iterator;
		typedef typename Rep_type::reverse_iterator			reverse_iterator;
		typedef typename Rep_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename Rep_type::size_type				size_type;
		typedef typename Rep_type::difference_type			difference_type;

	public:
		/* MEMBER FUNCTIONS */
		// Construct map
		// empty
		explicit map(const key_compare &comp = key_compare(), \
					const allocator_type& alloc = allocator_type())
		: _tree(comp, alloc) {}

		// range
		template < class InputIterator >
		map(InputIterator first, InputIterator last, \
			const key_compare &comp = key_compare(), \
			const allocator_type &alloc = allocator_type())
		: _tree(comp, alloc)
		{ _tree.insert_unique(first, last); }

		// copy
		map (const map &x)
		: _tree(x.tree) {}

		// Map destructor
		~map() {}

		// Copy container content
		// copy
		map&	operator= (const map &x)
		{
			if (this != &x)
				_tree = x._tree;
			return (*this);
		}

		/* ITERATORS */
		// Return iterator to beginning
		iterator				begin()
		{ return (_tree.begin()); }

		const_iterator			begin() const
		{ return (_tree.begin()); }

		// Return iterator to end
		iterator				end()
		{ return (_tree.end()); }

		const_iterator			end() const
		{ return (_tree.end()); }

		// Return reverse iterator to reverse beginning
		reverse_iterator		rbegin()
		{ return (_tree.rbegin()); }

		const_reverse_iterator	rbegin() const
		{ return (_tree.rbegin()); }

		// Return reverse iterator to reverse end
		reverse_iterator		rend()
		{ return (_tree.rend()); }

		const_reverse_iterator	rend() const
		{ return (_tree.rend()); }

		/* CAPACITY */
		// Test whether container is empty
		bool					empty() const
		{ return (_tree.empty()); }

		// Return container size
		size_type				size() const
		{ return (_tree.size()); }

		// Return maximum size
		size_type				max_size() const
		{ return (_tree.max_size()); }

		/* ELEMENT ACCESS */
		// Access element
		mapped_type&			operator[] (const key_type &k)
		{
			iterator	i = lower_bound(k);
			if (i == end() || key_compare()(k, (*i).first))
				i = insert(i, value_type(k, mapped_type()));
			return ((*i).second);
		}

		/* MODIFIERS */
		// Insert elements
		// single element
		pair<iterator,bool>		insert(const value_type &val)
		{ return (_tree.insert_unique(val)); }

		// with hint
		iterator				insert(iterator position, const value_type &val)
		{ return (_tree.insert_unique(position, val)); }

		// range
		template < class InputIterator>
		void					insert(InputIterator first, InputIterator last)
		{ _tree.insert_unique(first, last); }

		// Erase elements
		void					erase(iterator position)
		{ _tree.erase(k); }

		size_type				erase(const key_type &k)
		{ return (_tree.erase(k)); }

		void					erase(iterator first, iterator last)
		{ _tree.erase(first, last); }

		// Swap content
		void					swap(map &x)
		{ _tree.swap(x._tree); }

		// Clear content
		void					clear()
		{ _tree.clear(); }

		/* OBSERVERS */
		// Return key comparison object
		key_compare				key_comp() const
		{ return (_tree.key_comp()); }

		// Return value comparison object
		value_compare			value_comp() const
		{ return (value_compare(_tree.key_comp())); }

		/* OPERATIONS */
		// Get iterator to element
		iterator				find(const key_type &k)
		{ return (_tree.find(k)); }

		const_iterator			find(const key_type &k) const
		{ return (_tree.find(k)); }

		// Count elements with a specific key
		size_type				count(const key_type &k) const
		{ return (_tree.find(k) == _tree.end() ? 0 : 1); }

		// Return iterator to lower bound
		iterator				lower_bound(const key_type &k)
		{ return (_tree.lower_bound(k)); }

		const_iterator			lower_bound(const key_type &k) const
		{ return (_tree.lower_bound(k)); }

		// Return iterator to upper bound
		iterator				upper_bound(const key_type &k)
		{ return (_tree.upper_bound(k)); }

		const_iterator			upper_bound(const key_type &k) const
		{ return (_tree.upper_bound(k)); }

		// Get range of equal elements
		ft::pair<const_iterator,const_iterator>	equal_range(const key_type &k) const
		{ return (ft::make_pair(_tree.lower_bound(k), _tree.upper_bound(k))); }

		ft::pair<iterator,iterator>				equal_rage(const key_type &k)
		{ return (ft::make_pair(_tree.lower_bound(k), _tree.upper_bound(k))); }
	};	//class map

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	inline bool		operator== (const map<_Key, _T, _Compare, _Alloc> &x, \
								const map<_Key, _T, _Compare, _Alloc> &y)
	{ return (x._tree == y._tree); }

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	inline bool		operator!= (const map<_Key, _T, _Compare, _Alloc> &x, \
								const map<_Key, _T, _Compare, _Alloc> &y)
	{ return (!(x == y)); }

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	inline bool		operator< (const map<_Key, _T, _Compare, _Alloc> &x, \
								const map<_Key, _T, _Compare, _Alloc> &y)
	{ return (x._tree < y._tree); }

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	inline bool		operator> (const map<_Key, _T, _Compare, _Alloc> &x, \
								const map<_Key, _T, _Compare, _Alloc> &y)
	{ return (y < x)); }

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	inline bool		operator<= (const map<_Key, _T, _Compare, _Alloc> &x, \
								const map<_Key, _T, _Compare, _Alloc> &y)
	{ return (!(y < x)); }

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	inline bool		operator>= (const map<_Key, _T, _Compare, _Alloc> &x, \
								const map<_Key, _T, _Compare, _Alloc> &y)
	{ return (!(x < y)); }

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	inline void		swap(const map<_Key, _T, _Compare, _Alloc> &x, \
						const map<_Key, _T, _Compare, _Alloc> &y)
	{ x.swap(y); }
}	// namespace ft

#endif