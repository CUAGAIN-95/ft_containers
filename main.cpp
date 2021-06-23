/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:33:47 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/06/24 06:12:09 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"
#include "Queue.hpp"

int		main(void)
{
	ft::stack<int>	s;

	std::cout << s.empty() << std::endl;
	std::cout << s.size() << std::endl;

	s.push(10);

	std::cout << s.empty() << std::endl;
	std::cout << s.size() << std::endl;
	std::cout << s.top() << std::endl;

	ft::queue<char>	c;
	std::cout << c.empty() << std::endl;
	std::cout << c.size() << std::endl;

	c.push('a');

	std::cout << c.empty() << std::endl;
	std::cout << c.size() << std::endl;
	std::cout << c.front() << std::endl;
	return (0);
}