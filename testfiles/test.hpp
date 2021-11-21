#ifndef TEST_HPP
# define TEST_HPP

# include <stdarg.h>
# include <iostream>

# include <vector>
# include <map>
# include <stack>
# include "../includes/vector/vector.hpp"
# include "../includes/map/map.hpp"
# include "../includes/stack/stack.hpp"

template < typename Orig, typename My >
void	set_two_container(Orig &tmp1, My &tmp2, int num, ...)
{
	va_list ap;
	va_start(ap, num);
	for (int i = 0; i < num; ++i)
	{
		int arg = va_arg(ap, int);
		tmp1.push_back(arg);
		tmp2.push_back(arg);
	}
	va_end(ap);
}

template < class Ret >
void	compare_ret(const std::string func_name, const Ret orig, const Ret my)
{
	std::cout.width(42);
	std::cout << func_name << " >> ";
	std::cout << ((orig == my) ? "same" : "diff") << std::endl;
}

template < typename Orig, typename My >
void	compare_two_container(const std::string func_name, Orig& orig, My& my)
{
	std::cout.width(42);
	std::cout << func_name << " >> ";
	if (orig.size() != my.size())
		std::cout << "diff" << std::endl;
	else
	{
		typename Orig::iterator it1 = orig.begin();
		typename My::iterator it2 = my.begin();
		while (it1 != orig.end())
		{
			if (*it1 != *it2)
			{
				std::cout << "diff" << std::endl;
				return ;
			}
			++it1;
			++it2;
		}
		std::cout << "same" << std::endl;
	}
}

template < typename Orig, typename My >
void	compare_two_map(const std::string func_name, Orig& orig, My& my)
{
	std::cout.width(42);
	std::cout << func_name << " >> ";
	if (orig.size() != my.size())
		std::cout << "diff" << std::endl;
	else
	{
		typename Orig::iterator it1 = orig.begin();
		typename My::iterator it2 = my.begin();
		while (it1 != orig.end())
		{
			if (it1->first != it2->first || it1->second != it2->second)
			{
				std::cout << "diff" << std::endl;
				return ;
			}
			++it1;
			++it2;
		}
		std::cout << "same" << std::endl;
	}
}

template < typename Orig, typename My >
void	compare_two_stack(const std::string func_name, Orig& orig, My& my)
{
	std::cout.width(42);
	std::cout << func_name << " >> ";
	if (orig.size() != my.size())
		std::cout << "diff" << std::endl;
	else
	{
		Orig tmp1 = orig;
		My tmp2 = my;
		while (!tmp1.empty())
		{
			if (tmp1.top() != tmp2.top())
			{
				std::cout << "diff" << std::endl;
				return ;
			}
			tmp1.pop();
			tmp2.pop();
		}
		std::cout << "same" << std::endl;
	}
}

template < typename Orig, typename My >
void	compare_two_queue(const std::string func_name, Orig& orig, My& my)
{
	std::cout.width(42);
	std::cout << func_name << " >> ";
	if (orig.size() != my.size())
		std::cout << "diff" << std::endl;
	else
	{
		Orig tmp1 = orig;
		My tmp2 = my;
		while (!tmp1.empty())
		{
			if (tmp1.front() != tmp2.front())
			{
				std::cout << "diff" << std::endl;
				return ;
			}
			tmp1.pop();
			tmp2.pop();
		}
		std::cout << "same" << std::endl;
	}
}

#endif