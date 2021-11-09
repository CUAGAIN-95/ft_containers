/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhlee <yeonhlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:33:47 by yeonhlee          #+#    #+#             */
/*   Updated: 2021/11/09 01:48:33 by yeonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Stack.hpp"
// #include "Queue.hpp"

// #include "Vector.hpp"
#include <vector>
#include <iostream>
#include <string>

// # include "../ft_containers_jw/map/map.hpp"
// # include "../ft_containers_jw/map/pair.hpp"
// # include "../ft_containers_jw/utils/utils.hpp"
// # include "vector.hpp"
// # include "stack.hpp"
# include <map>

int		main(void)
{
	// std::map<int, char> m;

	// int		i = 0;
	// char	c = 'a';
	// for (int j = 0; j < 15; j++)
	// 	m.insert(std::map<int, char>::value_type(i++, c++));
	
	// for (int j = 0; j < 15; j++)
	// 	std::cout << j  << ' ' << m[j] << std::endl;

	// std::cout << std::endl;
	// std::map<int, char>::iterator it = m.begin();
	// while (it != m.end())
	// {
	// 	std::cout << it->second << std::endl;
	// 	it++;
	// }
	// std::cout << it->second << std::endl;


	std::map<int, int> m;

	m.insert(std::pair<int, int>(1, 1));
	m.insert(std::pair<int, int>(2, 2));
	m.insert(std::pair<int, int>(3, 3));
	m.insert(std::pair<int, int>(4, 4));
	m.insert(std::pair<int, int>(5, 5));
	m.insert(std::pair<int, int>(6, 6));

	std::map<int, int>::iterator it = m.begin();

	std::cout << it->second << std::endl;
	++it;
	std::cout << it->second << std::endl;
	++it;
	std::cout << it->second << std::endl;
	++it;
	std::cout << it->second << std::endl;
	++it;
	std::cout << it->second << std::endl;
	++it;
	std::cout << it->second << std::endl;
	++it;
	std::cout << it->first << ' ' << it->second << std::endl;


	return (0);
}