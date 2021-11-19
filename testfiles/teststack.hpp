#ifndef TESTSTACK_HPP
# define TESTSTACK_HPP

# include "test.hpp"

template < typename T >
void	test_empty(std::stack<T>& orig, ft::stack<T>& my)
{
	compare_ret("test_empty", orig.empty(), my.empty());
}

template < typename T >
void	test_size(std::stack<T>& orig, ft::stack<T>& my)
{
	orig.push(1.1);
	orig.push(2.2);
	orig.push(3.3);

	my.push(1.1);
	my.push(2.2);
	my.push(3.3);

	compare_two_stack("test_size", orig, my);
}

template < typename T >
void	test_top(std::stack<T>& orig, ft::stack<T>& my)
{
	compare_ret("test_top", orig.top(), my.top());
}

template < typename T >
void	test_push(std::stack<T>& orig, ft::stack<T>& my)
{
	orig.push(4.4);
	my.push(4.4);

	compare_two_stack("test_push", orig, my);
}

template < typename T >
void	test_pop(std::stack<T>& orig, ft::stack<T>& my)
{
	orig.pop();
	my.pop();

	compare_two_stack("test_pop", orig, my);
}

template < typename T >
void	test_operators(std::stack<T>& orig, ft::stack<T>& my)
{
	std::stack<T> tmp1;
	ft::stack<T> tmp2;

	tmp1.push(1.1);
	tmp1.push(2.2);
	tmp1.push(3.3);

	tmp2.push(1.1);
	tmp2.push(2.2);
	tmp2.push(3.3);
	
	compare_ret("operator == ", orig == tmp1, my == tmp2);
	compare_ret("operator != ", orig != tmp1, my != tmp2);
	tmp1.pop();
	tmp2.pop();
	tmp1.push(-1.1);
	tmp2.push(-1.1);
	compare_ret("operator < ", orig < tmp1, my < tmp2);
	compare_ret("operator > ", orig > tmp1, my > tmp2);
	compare_ret("operator <= ", orig <= tmp1, my <= tmp2);
	compare_ret("operator >= ", orig >= tmp1, my >= tmp2);
}


void	teststack()
{
	std::cout << "*******************************************" << std::endl;
	std::cout << "******           test stack          ******" << std::endl;
	std::cout << "*******************************************" << std::endl;
	std::stack<double> orig;
	ft::stack<double> my;

	test_empty(orig, my);
	test_size(orig, my);
	test_top(orig, my);
	test_push(orig, my);
	test_pop(orig, my);
	test_operators(orig, my);
}

#endif