#ifndef TESTVECTOR_HPP
# define TESTVECTOR_HPP

# include "test.hpp"

template < typename T >
void	test_size(std::vector<T>& orig, ft::vector<T>& my)
{
	compare_ret("test_size", orig.size(), my.size());
}

template < typename T >
void	test_max_size(std::vector<T>& orig, ft::vector<T>& my)
{
	compare_ret("test_max_size", orig.max_size(), my.max_size());
}

template < typename T >
void	test_resize(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');

	orig.resize(3);
	my.resize(3);

	compare_two_container("test_resize", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_capacity(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	compare_ret("test_capacity", orig.capacity(), my.capacity());
	orig.clear();
	my.clear();
}

template < typename T >
void	test_empty(std::vector<T>& orig, ft::vector<T>& my)
{
	compare_ret("test_empty", orig.empty(), my.empty());
}

template < typename T >
void	test_reserve(std::vector<T>& orig, ft::vector<T>& my)
{
	orig.reserve(42);
	my.reserve(42);
	compare_ret("test_reserve", orig.capacity(), my.capacity());
}

template < typename T >
void	test_index_operator(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	compare_ret("operator []", orig[3], my[3]);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_at(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	compare_ret("test_at", orig.at(0), my.at(0));
	orig.clear();
	my.clear();
}

template < typename T >
void	test_front(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	compare_ret("test_front", orig.front(), my.front());
	orig.clear();
	my.clear();
}

template < typename T >
void	test_back(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	compare_ret("test_back", orig.back(), my.back());
	orig.clear();
	my.clear();
}

template < typename T >
void	test_assign_range(std::vector<T>& orig, ft::vector<T>& my)
{
	std::vector<char> vc;
	vc.push_back('f');
	vc.push_back('g');
	vc.push_back('h');
	vc.push_back('i');
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	orig.assign(vc.begin(), vc.end());
	my.assign(vc.begin(), vc.end());
	compare_two_container("test_assign_range", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_assign_n(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	orig.assign(10, 'z');
	my.assign(10, 'z');
	compare_two_container("test_assign_n", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_push_back(std::vector<T>& orig, ft::vector<T>& my)
{
	orig.push_back('a');
	orig.push_back('b');
	orig.push_back('c');
	orig.push_back('d');
	my.push_back('a');
	my.push_back('b');
	my.push_back('c');
	my.push_back('d');
	compare_two_container("test_push_back", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_pop_back(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	orig.pop_back();
	orig.pop_back();
	orig.pop_back();
	my.pop_back();
	my.pop_back();
	my.pop_back();
	compare_two_container("test_pop_back", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_insert_one(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');

	std::vector<char>::iterator it1 = orig.begin();
	ft::vector<char>::iterator it2 = my.begin();
	++it1;
	++it2;
	
	orig.insert(it1, 'z');
	my.insert(it2, 'z');
	compare_two_container("test_insert_one", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_insert_n(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');

	std::vector<char>::iterator it1 = orig.begin();
	ft::vector<char>::iterator it2 = my.begin();
	++it1; ++it1;
	++it2; ++it2;

	orig.insert(it1, 3, 'z');
	my.insert(it2, 3, 'z');
	compare_two_container("test_insert_n", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_insert_range(std::vector<T>& orig, ft::vector<T>& my)
{
	std::vector<int> vc(2, 30);
	
	orig.insert(orig.end(), vc.begin(), vc.end());
	my.insert(my.end(), vc.begin(), vc.end());
	compare_two_container("test_insert_range", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_erase_one(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');

	std::vector<char>::iterator it1 = orig.begin();
	ft::vector<char>::iterator it2 = my.begin();
	++it1; ++it1;
	++it2; ++it2;
	orig.erase(it1);
	my.erase(it2);
	compare_two_container("test_erase_one", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_erase_range(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');

	std::vector<char>::iterator it1 = orig.begin();
	ft::vector<char>::iterator it2 = my.begin();
	++it1; ++it1;
	++it2; ++it2;
	orig.erase(it1, orig.end());
	my.erase(it2, my.end());
	compare_two_container("test_erase_range", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_swap(std::vector<T>& orig, ft::vector<T>& my)
{
	std::vector<T> tmp1;
	ft::vector<T> tmp2;
	set_two_container(tmp1, tmp2, 5, 'a', 'b', 'c', 'd', 'e');

	orig.swap(tmp1);
	my.swap(tmp2);
	compare_two_container("test_swap", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_clear(std::vector<T>& orig, ft::vector<T>& my)
{
	orig.clear();
	my.clear();
	compare_two_container("test_swap", orig, my);
}

template < typename T >
void	test_operators(std::vector<T>& orig, ft::vector<T>& my)
{
	std::vector<T> tmp1;
	ft::vector<T> tmp2;
	set_two_container(tmp1, tmp2, 5, 'a', 'b', 'c', 'd', 'e');

	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	compare_ret("operator == ", orig == tmp1, my == tmp2);
	orig.clear();
	my.clear();
	set_two_container(orig, my, 3, 'a', 'j', 'i');
	compare_ret("operator != ", orig != tmp1, my != tmp2);
	compare_ret("operator < ", orig < tmp1, my < tmp2);
	compare_ret("operator > ", orig > tmp1, my > tmp2);
	compare_ret("operator <= ", orig <= tmp1, my <= tmp2);
	compare_ret("operator >= ", orig >= tmp1, my >= tmp2);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_nonmember_swap(std::vector<T>& orig, ft::vector<T>& my)
{
	std::vector<T> tmp1;
	ft::vector<T> tmp2;
	set_two_container(tmp1, tmp2, 5, 'a', 'b', 'c', 'd', 'e');
	set_two_container(orig, my, 3, 'a', 'j', 'i');
	swap(orig, tmp1);
	swap(my, tmp2);
	compare_two_container("test_nonmember_swap", orig, my);
	orig.clear();
	my.clear();
}

template < typename T >
void	test_reverse_iterator(std::vector<T>& orig, ft::vector<T>& my)
{
	set_two_container(orig, my, 5, 'a', 'b', 'c', 'd', 'e');
	std::cout.width(42);
	std::cout << "test_reverse_iterator" << " >> " << std::endl;
	std::cout.width(42);
	std::cout << "orig vector:\t";
	for (typename std::vector<T>::reverse_iterator rit = orig.rbegin(); rit != orig.rend(); ++rit)
		std::cout << *rit << ' ';
	std::cout << std::endl;
	std::cout.width(42);
		std::cout << "my vector:\t";
	for (typename ft::vector<T>::reverse_iterator rit = my.rbegin(); rit != my.rend(); ++rit)
		std::cout << *rit << ' ';
	std::cout << std::endl;
}

void	testvector()
{
	std::cout << "*******************************************" << std::endl;
	std::cout << "******          test vector          ******" << std::endl;
	std::cout << "*******************************************" << std::endl;
	std::vector<char> orig;
	ft::vector<char> my;

	test_size(orig, my);
	test_max_size(orig, my);
	test_resize(orig, my);
	test_capacity(orig, my);
	test_empty(orig, my);
	test_reserve(orig, my);
	test_index_operator(orig, my);
	test_at(orig, my);
	test_front(orig, my);
	test_back(orig, my);
	test_assign_range(orig, my);
	test_assign_n(orig, my);
	test_push_back(orig, my);
	test_pop_back(orig, my);
	test_insert_one(orig, my);
	test_insert_n(orig, my);
	test_insert_range(orig, my);
	test_erase_one(orig, my);
	test_erase_range(orig, my);
	test_swap(orig, my);
	test_clear(orig, my);

	test_operators(orig, my);
	test_nonmember_swap(orig, my);

	test_reverse_iterator(orig, my);
}

#endif