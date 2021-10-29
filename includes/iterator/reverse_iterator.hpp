/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:43:48 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/10/29 15:04:16 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_base_types.hpp"

namespace ft
{
	template < class Iterator >
	class reverse_iterator
	:	public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator										current;
			typedef iterator_traits<Iterator>				traits_type;

		public:
			typedef Iterator	iterator_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;

			// default constructor
			reverse_iterator() : current() { }

			explicit
			reverse_iterator(iterator_type x) : current(x) { }

			// copy constructor
			reverse_iterator(const reverse_iterator& x) : current(x.current) { }

			template < class _Iter >
			reverse_iterator(const reverse_iterator<_Iter>& x)
			:	current(x.base()) { }

			iterator_type		base() const
			{ return (current); }

			reference			operator*() const
			{
				Iterator	tmp = current;
				return (*--tmp);
			}

			pointer				operator->() const
			{ return (&(operator*())); }

			reverse_iterator&	operator++()
			{
				--current;
				return (*this);
			}

			reverse_iterator&	operator++(int)
			{
				reverse_iterator	tmp = *this;
				--current;
				return (tmp);
			}

			reverse_iterator&	operator--()
			{
				++current;
				return (*this);
			}

			reverse_iterator&	operator--(int)
			{
				reverse_iterator	tmp = *this;
				++current;
				return (tmp);
			}

			reverse_iterator	operator+(difference_type n) const
			{ return (reverse_iterator(current - n)); }

			reverse_iterator&	operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			reverse_iterator	operator-(difference_type n) const
			{ return (reverse_iterator(current + n)); }

			reverse_iterator&	operator-=(difference_type n)
			{
				current +=	n;
				return (*this);
			}

			reference			operator[](difference_type n) const
			{ return *(*this + n); }
	}; // class reverse_iterator

	template < typename Iterator >
	inline bool		operator==(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (x.base() == y.base()); }

	template < typename Iterator >
	inline bool		operator<(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (y.base() < x.base()); }

	template < typename Iterator >
	inline bool		operator!=(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return !(x == y); }

	template < typename Iterator >
	inline bool		operator>(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (y < x); }

	template < typename Iterator >
	inline bool		operator<=(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return !(y < x); }

	template < typename Iterator >
	inline bool		operator>=(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return !(x < y); }

	template < typename Iterator >
	inline typename reverse_iterator<Iterator>::difference_type
					operator-(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (y.base() - x.base()); }

	template < typename Iterator >
	inline reverse_iterator<Iterator>
					operator+(typename reverse_iterator<Iterator>::difference_type n,
								const reverse_iterator<Iterator>& x)
	{ return (reverse_iterator<Iterator>(x.base() - n)); }

	template < typename IteratorL, typename IteratorR >
	inline bool		operator==(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (x.base() == y.base()); }

	template < typename IteratorL, typename IteratorR >
	inline bool		operator<(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (y.base() < x.base()); }

	template < typename IteratorL, typename IteratorR >
	inline bool		operator!=(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (!(x == y)); }

	template < typename IteratorL, typename IteratorR >
	inline bool		operator>(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (y < x); }

	template < typename IteratorL, typename IteratorR >
	inline bool		operator<=(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (!(y < x)); }

	template < typename IteratorL, typename IteratorR >
	inline bool		operator>=(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (!(x < y)); }

	template < typename IteratorL, typename IteratorR >
	inline typename reverse_iterator<IteratorL>::difference_type
					operator-(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (y.base() - x.base()); }
}; // namespace ft
#endif