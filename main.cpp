/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:33:47 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/10/29 14:35:13 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Stack.hpp"
// #include "Queue.hpp"

// #include "Vector.hpp"
#include <vector>
#include <iostream>
#include <string>

# include "vector.hpp"

int		main(void)
{
	// ft::stack<int>	s;

	// std::cout << s.empty() << std::endl;
	// std::cout << s.size() << std::endl;

	// s.push(10);

	// std::cout << s.empty() << std::endl;
	// std::cout << s.size() << std::endl;
	// std::cout << s.top() << std::endl;

	// ft::queue<char>	c;

	// std::cout << c.empty() << std::endl;
	// std::cout << c.size() << std::endl;

	// c.push('a');

	// std::cout << c.empty() << std::endl;
	// std::cout << c.size() << std::endl;
	// std::cout << c.front() << std::endl;

	std::vector<int>				a(10, 1);

	std::cout << "capacity : \t" << a.capacity() << std::endl;
	std::cout << "size : \t\t" << a.size() << std::endl;
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
	a.resize(7);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
	std::cout << "capacity : \t"<< a.capacity() << std::endl;
	std::cout << "size : \t\t" << a.size() << std::endl;
	return (0);
}