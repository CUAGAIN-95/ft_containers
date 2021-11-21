/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:27:48 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/21 15:59:38 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_ITERATOR_HPP
# define NORMAL_ITERATOR_HPP

# include "iterator_base_types.hpp"

namespace ft
{
	template < class Iterator, class Container >
	class normal_iterator
	{
		protected:
			Iterator										current;
		public:
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::pointer				pointer;

			normal_iterator()
			: current(Iterator()) {}
			
			explicit
			normal_iterator(const Iterator& i)
			: current(i) {}

			template < class _Iter, class _Cont>
			normal_iterator(const normal_iterator<_Iter, _Cont> &x)
			: current(x.base()) {}

			reference			operator*() const
			{ return (*current); }

			pointer				operator->() const
			{ return (current); }

			normal_iterator&	operator++()
			{
				++current;
				return (*this);
			}

			normal_iterator		operator++(int)
			{ return (normal_iterator(current++)); }

			// bidirectional iterator requirements
			normal_iterator&	operator--()
			{
				--current;
				return (*this);
			}

			normal_iterator		operator--(int)
			{ return (normal_iterator(current--)); }

			// random access iterator requirements
			reference			operator[](difference_type n) const
			{ return (current[n]); }

			normal_iterator&	operator+=(difference_type n)
			{
				current += n;
				return (*this);
			}

			normal_iterator		operator+(difference_type n) const
			{ return (normal_iterator(current + n)); }

			normal_iterator&	operator-=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			normal_iterator		operator-(difference_type n) const
			{ return (normal_iterator(current - n)); }

			const Iterator&		base() const
			{ return (current); }
	}; // class normal_iterator

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator==(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<typename Iterator, typename Container>
	inline bool		operator==(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator!=(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template<typename Iterator, typename Container>
	inline bool		operator!=(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator<(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template<typename Iterator, typename Container>
	inline bool		operator<(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator>(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template<typename Iterator, typename Container>
	inline bool		operator>(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator<=(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template<typename Iterator, typename Container>
	inline bool		operator<=(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator>=(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template<typename Iterator, typename Container>
	inline bool		operator>=(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template<typename IteratorL, typename IteratorR, typename Container>
	typename		normal_iterator<IteratorL, Container>::difference_type
					operator-(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template<typename Iterator, typename Container>
	typename		normal_iterator<Iterator, Container>::difference_type
					operator-(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template<typename Iterator, typename Container>
	normal_iterator<Iterator, Container>
	operator+(typename normal_iterator<Iterator, Container>::differece_type n,
								const normal_iterator<Iterator, Container>& i)
	{ return (normal_iterator<Iterator, Container>(i.base() + n)); }
}; // namespace ft
#endif