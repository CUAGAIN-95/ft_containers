/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:46:56 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/10/28 19:33:22 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "Iterator_base_types.hpp"

namespace ft
{
	/*
	**	reverse_iterator=======================================================
	*/
	template < class Iterator >
	class reverse_iterator
	:	public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iteraotr_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator										current;
			typedef Iterator_traits<Iterator>				traits_type;

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

			template<typename Iterator>
			reverse_iterator(const reverse_iterator<Iterator>& x)
			:	current(x.base()) { }

			iterator_type		base() const
			{ return (current); }

			reference			operator*() const
			{
				Iteraotr	tmp = current;
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

	template<typename Iterator>
	inline bool		operator==(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (x.base() == y.base()); }

	template<typename Iterator>
	inline bool		operator<(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (y.base() < x.base()); }

	template<typename Iterator>
	inline bool		operator!=(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return !(x == y); }

	template<typename Iterator>
	inline bool		operator>(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (y < x); }

	template<typenmae Iterator>
	inline bool		operator<=(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return !(y < x); }

	template<typename Iterator>
	inline bool		operator>=(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return !(x < y); }

	template<typenmae Iterator>
	inline typename reverse_iterator<Iterator>::difference_type
					operator-(const reverse_iterator<Iterator>& x,
								const reverse_iterator<Iterator>& y)
	{ return (y.base() - x.base()); }

	template<typename Iterator>
	inline reverse_iterator<Iterator>
					operator+(typename reverse_iterator<Iterator>::difference_type n,
								const reverse_iterator<Iterator>& x)
	{ return (reverse_iterator<Iterator>(x.base() - n)); }

	template<typename IteratorL, typename IteratorR>
	inline bool		operator==(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (x.base() == y.base()); }

	template<typename IteratorL, typename IteratorR>
	inline bool		operator<(const reverse_iteartor<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (y.base() < x.base()); }

	template<typename IteratorL, typename IteratorR>
	inline bool		operator!=(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (!(x == y)); }

	template<typename IteratorL, typename IteratorR>
	inline bool		operator>(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (y < x); }

	template<typename IteratorL, typename IteratorR>
	inline bool		operator<=(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (!(y < x)); }

	template<typename IteratorL, typename IteratorR>
	inline bool		operator>=(const reverse_iterator<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (!(x < y)); }

	template<typename IteratorL, typenmae IteratorR>
	inline typename reverse_iterator<IteratorL>::difference_type
					operator-(const reverse_itertor<IteratorL>& x,
								const reverse_iterator<IteratorR>& y)
	{ return (y.base() - x.base()); }

	/*
	**	nomal_iterator=========================================================
	*/
	template < class Iterator, class Container >
	class nomal_iterator
	{
		protected:
			Iterator										current;

			typedef iterator_traits<Iterator>				traits_type;

		public:
			typedef Iterator	iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;

			normal_iterator() : current(Iterator) { }
			
			explicit
			normal_iterator(const Iterator& i) : current(i) { }

			// // Allow iterator to const_iterator conversion
			// template<typename _Iter>
			// __normal_iterator(const __normal_iterator<_Iter,
			// 				typename __enable_if<
			// 				(std::__are_same<_Iter, typename _Container::pointer>::__value),
			// 				_Container>::__type>& __i) _GLIBCXX_NOEXCEPT
			// : _M_current(__i.base()) { }
	
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
	}; // class nomal_iterator

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator==(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<typenmae Iterator, typename Container>
	inline bool		operator==(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool		operator!=(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template<typename Iterator, typename Container>
	inline bool		operator!=(const normal_iterator<Iterator, Conatiner>& lhs,
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
	inline typename		normal_iterator<IteratorL, Container>::difference_type
					operator-(const normal_iterator<IteratorL, Container>& lhs,
								const normal_iterator<IteratorR, Container>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template<typename Iterator, typename Container>
	inline typename		normal_iterator<Iterator, Container>::difference_type
					operator-(const normal_iterator<Iterator, Container>& lhs,
								const normal_iterator<Iterator, Container>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template<typename Iterator, typename Container>
	inline				normal_iterator<Iterator, Container>
					operator+(typename normal_iterator<Iterator, Container>::differece_type n,
								const normal_iterator<Iterator, Container>& i)
	{ return (normal_iterator<Iterator, Container>(i.base() + n)); }
}; // namespace ft
#endif